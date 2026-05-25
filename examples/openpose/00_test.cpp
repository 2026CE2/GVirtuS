#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>

#define OPENPOSE_FLAGS_DISABLE_POSE
#include <openpose/flags.hpp>
#include <openpose/headers.hpp>

// Defaults point to the bind-mounted folder inside the container
DEFINE_string(image_path, "/opt/openpose/examples/media/COCO_val2014_000000000589.jpg",
              "Input image path.");
DEFINE_string(output_dir, "/opt/openpose/examples/media",
              "Where the rendered image will be saved.");
DEFINE_string(output_name, "",
              "Optional output filename prefix; if empty, uses <input>_pose_run<N>.png.");
DEFINE_bool(no_display, true, "Disable visual display.");
DEFINE_int32(num_runs, 10, "Number of times to run the test.");
DEFINE_string(csv_output, "/opt/openpose/examples/media/results.csv",
              "Path for the CSV results file.");
DEFINE_string(net_resolution, "368x-1",
              "OpenPose network input resolution (WxH, -1 scales proportionally). "
              "Reduce to lower GPU memory usage (e.g. 368x-1 vs default 656x368).");

static std::string deriveOutputPath(const std::string& inputPath,
                                    const std::string& outDir,
                                    const std::string& outName,
                                    int runNum)
{
    namespace fs = std::filesystem;
    fs::path dir(outDir);
    if (!fs::exists(dir)) fs::create_directories(dir);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << runNum;
    const std::string runTag = "_run" + oss.str();

    if (!outName.empty()) {
        fs::path p(outName);
        const std::string stem = p.has_stem() ? p.stem().string() : "output";
        const std::string ext  = p.has_extension() ? p.extension().string() : ".png";
        return (dir / (stem + runTag + ext)).string();
    }

    fs::path in(inputPath);
    const std::string stem = in.has_stem() ? in.stem().string() : "output";
    return (dir / (stem + "_pose" + runTag + ".png")).string();
}

void saveOutput(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr,
                int runNum)
{
    try {
        if (datumsPtr && !datumsPtr->empty()) {
            const cv::Mat cvMat = OP_OP2CVCONSTMAT(datumsPtr->at(0)->cvOutputData);
            if (!cvMat.empty()) {
                const auto outPath = deriveOutputPath(
                    FLAGS_image_path, FLAGS_output_dir, FLAGS_output_name, runNum);
                if (!cv::imwrite(outPath, cvMat))
                    op::opLog("Failed to write image to: " + outPath, op::Priority::High);
                else
                    op::opLog("Saved rendered pose image to: " + outPath, op::Priority::High);
            } else {
                op::opLog("Empty cv::Mat as output.", op::Priority::High);
            }
        } else {
            op::opLog("Nullptr or empty datumsPtr found.", op::Priority::High);
        }
    } catch (const std::exception& e) {
        op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
    }
}

void printKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr)
{
    try {
        if (datumsPtr && !datumsPtr->empty())
            op::opLog("Body keypoints: " + datumsPtr->at(0)->poseKeypoints.toString(),
                      op::Priority::High);
        else
            op::opLog("Nullptr or empty datumsPtr found.", op::Priority::High);
    } catch (const std::exception& e) {
        op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
    }
}

// Returns {passed, elapsed_seconds}
// opWrapper is created once and shared across runs to avoid re-establishing
// the QUIC connection on every iteration (QUIC does not reconnect cleanly).
std::pair<bool, double> runOnce(op::Wrapper& opWrapper, int runNum)
{
    const auto wallStart = std::chrono::steady_clock::now();
    auto elapsed = [&]() {
        return std::chrono::duration<double>(
            std::chrono::steady_clock::now() - wallStart).count();
    };

    try {
        op::opLog("=== Run " + std::to_string(runNum) + " starting ===",
                  op::Priority::High);

        const cv::Mat cvImageToProcess = cv::imread(FLAGS_image_path);
        if (cvImageToProcess.empty()) {
            op::opLog("Could not read input image: " + FLAGS_image_path, op::Priority::High);
            return {false, elapsed()};
        }

        const op::Matrix imageToProcess = OP_CV2OPCONSTMAT(cvImageToProcess);
        auto datumProcessed = opWrapper.emplaceAndPop(imageToProcess);
        if (!datumProcessed) {
            op::opLog("Image could not be processed.", op::Priority::High);
            return {false, elapsed()};
        }

        printKeypoints(datumProcessed);
        saveOutput(datumProcessed, runNum);

        const double t = elapsed();
        op::opLog("=== Run " + std::to_string(runNum) + " finished. Time: " +
                  std::to_string(t) + " s ===", op::Priority::High);
        return {true, t};
    } catch (const std::exception& e) {
        op::opLog("Run " + std::to_string(runNum) + " threw exception: " + e.what(),
                  op::Priority::High);
        return {false, elapsed()};
    }
}

int main(int argc, char* argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    const int numRuns = FLAGS_num_runs;
    const std::string csvPath = FLAGS_csv_output;

    // Create and start the wrapper once — keeps the QUIC connection alive
    // for all runs instead of tearing it down and re-connecting each time.
    op::Wrapper opWrapper{op::ThreadManagerMode::Asynchronous};
    if (FLAGS_disable_multi_thread) opWrapper.disableMultiThreading();
    opWrapper.start();

    std::ofstream csv(csvPath);
    csv << "run,elapsed_seconds,result\n";

    int passed = 0;
    for (int i = 1; i <= numRuns; ++i) {
        auto [ok, t] = runOnce(opWrapper, i);
        csv << i << ","
            << std::fixed << std::setprecision(4) << t << ","
            << (ok ? "PASS" : "FAIL") << "\n";
        csv.flush();
        if (ok) ++passed;
    }

    op::opLog("=== Summary: " + std::to_string(passed) + "/" +
              std::to_string(numRuns) + " passed. CSV: " + csvPath + " ===",
              op::Priority::High);

    return (passed == numRuns) ? 0 : 1;
}
