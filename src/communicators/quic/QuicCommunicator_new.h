#pragma once

#include "gvirtus/communicators/Communicator.h"
#include "QuicSettings.h"
#include "msquic.h"

#include <thread>
#include <mutex>
#include <map>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <vector>
#include <unordered_set>
#include <poll.h>

namespace gvirtus::communicators {

const uint32_t SendBufferLength = 4*1024*1024;

typedef struct QUIC_CREDENTIAL_CONFIG_HELPER {
    QUIC_CREDENTIAL_CONFIG CredConfig;
    union {
        QUIC_CERTIFICATE_HASH CertHash;
        QUIC_CERTIFICATE_HASH_STORE CertHashStore;
        QUIC_CERTIFICATE_FILE CertFile;
        QUIC_CERTIFICATE_FILE_PROTECTED CertFileProtected;
    };
} QUIC_CREDENTIAL_CONFIG_HELPER;


const QUIC_BUFFER Alpn = { sizeof("gvirtus") - 1, (uint8_t*)"gvirtus" };

struct Pipes {
    int read;
    int write;
};

using cuda_stream_ptr = void*; // Placeholder for actual CUDA stream type
class QuicCommunicator : public gvirtus::communicators::Communicator {
public:
    QuicCommunicator(const QuicCommunicator &);
    QuicCommunicator(const std::string &communicator);
    virtual ~QuicCommunicator();

    void Serve();
    const Communicator *const Accept() const;
    void Connect();
    
    size_t Read(char *buffer, size_t size);
    size_t Read_Async(char * buffer, size_t size, cuda_stream_ptr stream);
    
    size_t Write(const char *buffer, size_t size);
    size_t Write_Async(const char * buffer, size_t size, cuda_stream_ptr stream);

    void Start_Stream(cuda_stream_ptr stream);
    
    void Sync();
    void Close();
    
    std::string to_string() override { return "quiccommunicator"; }

    // Callbacks - Must be public due to Wrapper calling object callbacks
    QUIC_STATUS ServerListenerCallback(HQUIC Listener, void* Context, QUIC_LISTENER_EVENT* Event);
    static QUIC_STATUS ServerListenerCallbackWrapper(HQUIC Listener, void* Context, QUIC_LISTENER_EVENT* Event);
    QUIC_STATUS ServerConnectionCallback(HQUIC Connection, void* Context, QUIC_CONNECTION_EVENT* Event);
    static QUIC_STATUS ServerConnectionCallbackWrapper(HQUIC Connection, void* Context, QUIC_CONNECTION_EVENT* Event);
    QUIC_STATUS ServerStreamCallback(HQUIC Stream, void* Context, QUIC_STREAM_EVENT* Event);
    static QUIC_STATUS ServerStreamCallbackWrapper(HQUIC Stream, void* Context, QUIC_STREAM_EVENT* Event);
    
    QUIC_STATUS ClientConnectionCallback(HQUIC Connection, void* Context, QUIC_CONNECTION_EVENT* Event);
    static QUIC_STATUS ClientConnectionCallbackWrapper(HQUIC Connection, void* Context, QUIC_CONNECTION_EVENT* Event);
    QUIC_STATUS ClientStreamCallback(HQUIC Stream, void* Context, QUIC_STREAM_EVENT* Event);
    static QUIC_STATUS ClientStreamCallbackWrapper(HQUIC Stream, void* Context, QUIC_STREAM_EVENT* Event);
protected:


private:
    void InitializeQuic();
    Pipes InitializePipes();
    bool ServerLoadConfiguration(int argc, const char* argv[] );
    bool ClientLoadConfiguration(bool unsecure);
    bool LoadQuicSettingsFromJson(QUIC_SETTINGS& Settings);

    // Multi-stream helpers
    void SendChunk(HQUIC stream, uint64_t msg_id, uint32_t total_chunks,
                   uint32_t chunk_idx, const char* data, size_t data_size);
    void StartReassemblyThread();
    void ReassemblyLoop();
    bool ReadExactFromPipe(int fd, char* buf, size_t size) const;


    // !! Mutables are needed because Accept is a const function. (Should find a better solution)
    // Maybe do most changes in other functions?

    // Listener objects
    HQUIC Listener;
    mutable HQUIC receivedConnection;
    mutable std::condition_variable cv;
    mutable std::mutex listenerMutex;
    mutable bool connectionEventOcurred = false;
    mutable bool listenerStarted = false;

    // Connection objects
    HQUIC Connection = nullptr;
    static inline const QUIC_API_TABLE* MsQuic = nullptr;
    HQUIC Registration;
    HQUIC Configuration;
    HQUIC DefaultStream{nullptr};
    QUIC_SETTINGS Settings = {0};

    // map of streams and their corresponding pipes. The key is the stream id, which is a 62 bit unsigned integer.
    std::map<HQUIC, Pipes> multiStreams;
    std::map<HQUIC, bool> streamStarted;
    std::mutex multiStreamMutex;

    // map of cudaStreams to quicStreams
    std::map<cuda_stream_ptr, HQUIC> cudaStreamMap;
    std::mutex cudaStreamMapMutex;

    // ============================
    // Multi-stream data transport
    // ============================

    // Wire-level frame header prepended to every chunk
    struct FrameHeader {
        uint64_t message_id;   // unique per Write() call
        uint32_t total_chunks; // 1 for small messages
        uint32_t chunk_index;  // 0-based index of this chunk
        uint32_t data_size;    // bytes of chunk data that follow
    };

    // Reassembly accumulator for split messages
    struct PendingMessage {
        uint32_t total_chunks = 0;
        std::map<uint32_t, std::vector<uint8_t>> chunks;
    };

    static constexpr size_t MULTISTREAM_THRESHOLD = 10000;

    uint32_t numDataStreams = 1;            // configurable via JSON
    std::vector<HQUIC> dataStreams;         // opened data streams (client side)
    std::unordered_set<HQUIC> dataStreamSet; // which streams are data streams (both sides)
    std::atomic<uint32_t> streamRoundRobin{0};  // round-robin counter for stream selection
    std::atomic<uint64_t> messageIdCounter{0};  // monotonically increasing message ID

    // Reassembly state
    mutable std::map<uint64_t, PendingMessage> pendingMessages;
    mutable std::mutex pendingMsgMutex;
    mutable Pipes outputPipe{-1, -1};       // Read() reads from here

    // Reassembly thread
    mutable std::thread reassemblyThread;
    mutable std::atomic<bool> reassemblyRunning{false};

    // Server-side counter: how many data streams have been registered so far
    mutable uint32_t numDataStreamsRegistered = 0;

    std::string mHostname;
    uint16_t mPort;
    const QUIC_REGISTRATION_CONFIG RegConfig = { "GvirtuS", QUIC_EXECUTION_PROFILE_LOW_LATENCY };


};

}; // namespace gvirtus::communicators