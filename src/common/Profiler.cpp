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

#include <gvirtus/common/Profiler.h>

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <sstream>
#include <sys/syscall.h>
#include <unistd.h>

namespace fs = std::filesystem;

namespace gvirtus::common {

// ---------------------------------------------------------------------------
// helpers (file-local)
// ---------------------------------------------------------------------------

static bool is_profile_enabled() {
    const char *env = std::getenv("GVIRTUS_PROFILE");
    if (!env) return false;
    return (strcasecmp(env, "on") == 0 || strcasecmp(env, "true") == 0 ||
            strcmp(env, "1") == 0);
}

static std::string profile_dir() {
    const char *dir = std::getenv("GVIRTUS_PROFILE_DIR");
    return dir ? std::string(dir) : ".";
}

static int64_t now_ns() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

// ---------------------------------------------------------------------------
// Profiler
// ---------------------------------------------------------------------------

Profiler::Profiler(const std::string &role, pid_t pid, pid_t tid)
    : _enabled(is_profile_enabled()), _pid(pid), _tid(tid) {
    if (!_enabled) return;

    std::string dir = profile_dir();
    std::error_code ec;
    fs::create_directories(dir, ec);  // best-effort; ignore error

    std::ostringstream fname;
    fname << dir << "/gvirtus_" << role << "_" << pid << "_" << tid << ".csv";

    // Open in append mode so repeated runs accumulate data in the same file.
    _file.open(fname.str(), std::ios::out | std::ios::app);
    if (!_file.is_open()) {
        _enabled = false;
        return;
    }

    // Write the CSV header only when the file is new (empty).
    if (_file.tellp() == 0) {
        if (role == "frontend") {
            _file << "timestamp_ns,call_seq,pid,tid,routine,"
                     "input_bytes,output_bytes,"
                     "send_sec,server_exec_sec,recv_sec,total_sec\n";
        } else {
            _file << "timestamp_ns,call_seq,pid,tid,routine,"
                     "input_bytes,output_bytes,handler_exec_sec\n";
        }
    }
}

Profiler::~Profiler() {
    if (_file.is_open()) {
        _file.flush();
        _file.close();
    }
}

void Profiler::record_frontend(const std::string &routine,
                                uint64_t call_seq,
                                size_t input_bytes,
                                size_t output_bytes,
                                double send_sec,
                                double server_exec_sec,
                                double recv_sec,
                                double total_sec) {
    if (!_enabled) return;
    int64_t ts = now_ns();
    std::lock_guard<std::mutex> lk(_mutex);
    _file << ts << ',' << call_seq << ','
          << _pid << ',' << _tid << ','
          << routine << ','
          << input_bytes << ',' << output_bytes << ','
          << send_sec << ',' << server_exec_sec << ','
          << recv_sec << ',' << total_sec << '\n';
    _file.flush();
}

void Profiler::record_backend(const std::string &routine,
                               uint64_t call_seq,
                               size_t input_bytes,
                               size_t output_bytes,
                               double handler_exec_sec) {
    if (!_enabled) return;
    int64_t ts = now_ns();
    std::lock_guard<std::mutex> lk(_mutex);
    _file << ts << ',' << call_seq << ','
          << _pid << ',' << _tid << ','
          << routine << ','
          << input_bytes << ',' << output_bytes << ','
          << handler_exec_sec << '\n';
    _file.flush();
}

}  // namespace gvirtus::common
