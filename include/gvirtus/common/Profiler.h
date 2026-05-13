/*
 * gVirtuS -- A GPGPU transparent virtualization component.
 *
 * Copyright (C) 2009-2010  The University of Napoli Parthenope at Naples.
 *
 * This file is part of gVirtuS.
 *
 * gVirtuS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * gVirtuS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gVirtuS; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#pragma once

#include <cstdint>
#include <fstream>
#include <mutex>
#include <string>
#include <sys/types.h>

namespace gvirtus::common {

/**
 * @brief Per-thread CSV profiler for GVirtuS frontend and backend.
 *
 * Records per-call timing and packet-size data to separate CSV files so that
 * frontend and backend measurements can be loaded and joined offline to
 * pinpoint bottlenecks.
 *
 * ### Activation
 * Set the environment variable `GVIRTUS_PROFILE=on` (also accepts `1` or
 * `true`).  When the variable is absent or set to any other value the profiler
 * is a no-op and imposes zero overhead.
 *
 * ### Output location
 * Set `GVIRTUS_PROFILE_DIR` to the desired directory (defaults to the current
 * working directory).  One CSV file is created per process/thread:
 * - **Frontend**: `gvirtus_frontend_<pid>_<tid>.csv`
 * - **Backend**:  `gvirtus_backend_<pid>_<tid>.csv`
 *
 * ### CSV columns
 * **Frontend file**
 * ```
 * timestamp_ns, call_seq, pid, tid, routine,
 * input_bytes, output_bytes,
 * send_sec, server_exec_sec, recv_sec, total_sec
 * ```
 *
 * **Backend file**
 * ```
 * timestamp_ns, call_seq, pid, tid, routine,
 * input_bytes, output_bytes, handler_exec_sec
 * ```
 *
 * ### Correlation
 * Because GVirtuS executes CUDA calls synchronously one-at-a-time per
 * frontend thread / backend connection thread, the `call_seq` counter is
 * identical on both sides for corresponding calls.  Join the two CSV files on
 * `(call_seq, routine)` — or on `(call_seq)` alone when a single application
 * thread is active — to combine frontend and backend measurements.
 */
class Profiler {
   public:
    /**
     * @param role  Either @c "frontend" or @c "backend".
     * @param pid   Process id of the calling process.
     * @param tid   Thread id of the calling thread.
     */
    Profiler(const std::string& role, pid_t pid, pid_t tid);
    ~Profiler();

    Profiler(const Profiler&) = delete;
    Profiler& operator=(const Profiler&) = delete;

    /// Returns @c true when GVIRTUS_PROFILE=on and the output file is open.
    bool enabled() const { return _enabled; }

    /**
     * Record one completed call on the **frontend** side.
     *
     * @param routine          CUDA routine name (e.g. "cudaMemcpy")
     * @param call_seq         Monotonic ordinal — 1 for the first call on this
     *                         thread, incremented by 1 for every subsequent
     *                         call.
     * @param input_bytes      Serialised input-buffer size sent to the backend.
     * @param output_bytes     Serialised output-buffer size received from the
     *                         backend.
     * @param send_sec         Wall time to serialise and send the request
     *                         (seconds).
     * @param server_exec_sec  Real GPU execution time reported by the backend
     *                         (seconds).
     * @param recv_sec         Wall time to receive the full response (seconds).
     * @param total_sec        Total round-trip wall time (seconds).
     */
    void record_frontend(const std::string& routine,
                         uint64_t call_seq,
                         size_t input_bytes,
                         size_t output_bytes,
                         double send_sec,
                         double server_exec_sec,
                         double recv_sec,
                         double total_sec);

    /**
     * Record one completed call on the **backend** side.
     *
     * @param routine          CUDA routine name (e.g. "cudaMemcpy")
     * @param call_seq         Monotonic ordinal — 1 for the first call on this
     *                         connection thread.
     * @param input_bytes      Deserialised input-buffer size received from the
     *                         frontend.
     * @param output_bytes     Serialised output-buffer size sent back.
     * @param handler_exec_sec Wall time spent inside the plugin handler,
     *                         including the real CUDA API call (seconds).
     */
    void record_backend(const std::string& routine,
                        uint64_t call_seq,
                        size_t input_bytes,
                        size_t output_bytes,
                        double handler_exec_sec);

   private:
    bool _enabled;
    pid_t _pid;
    pid_t _tid;
    std::ofstream _file;
    std::mutex _mutex;
};

}  // namespace gvirtus::common
