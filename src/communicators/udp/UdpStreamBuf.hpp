#pragma once
// udp_streambuf.hpp
// A custom std::streambuf that wraps a UDP socket,
// allowing istream/ostream to read/write over UDP.

#include <streambuf>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>

// POSIX socket headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

static constexpr std::size_t UDP_BUF_SIZE = 65507; // max UDP payload

class UdpStreamBuf : public std::streambuf {
public:
    explicit UdpStreamBuf(int fd)
        : fd_(fd)
        , outBuf_(UDP_BUF_SIZE)
        , inBuf_(UDP_BUF_SIZE)
    {
        // Set up put area (write buffer)
        setp(outBuf_.data(), outBuf_.data() + outBuf_.size());
        // Get area starts empty; underflow() will fill it.
        setg(inBuf_.data(), inBuf_.data() + inBuf_.size(), inBuf_.data() + inBuf_.size());
    }

protected:
    // -----------------------------------------------------------------------
    // Output (put area)
    // -----------------------------------------------------------------------

    // Called when the put buffer is full, or on explicit flush.
    int overflow(int c) override {
        if (flush_put_area() == -1) return traits_type::eof();
        if (c != traits_type::eof()) {
            *pptr() = traits_type::to_char_type(c);
            pbump(1);
        }
        return traits_type::not_eof(c);
    }

    // Called by ostream::flush() / endl / sync.
    int sync() override {
        return flush_put_area();
    }

    // -----------------------------------------------------------------------
    // Input (get area)
    // -----------------------------------------------------------------------

    // Called when the get buffer is exhausted.
    int underflow() override {
        // socklen_t addrLen = sizeof(lastPeer_);
        ssize_t n = ::recv(fd_,
                               inBuf_.data(), inBuf_.size(),
                               0);
        if (n <= 0) return traits_type::eof();

        // Reset get area to the freshly received data.
        setg(inBuf_.data(), inBuf_.data(), inBuf_.data() + n);
        return traits_type::to_int_type(*gptr());
    }

private:
    int flush_put_area() {
        std::ptrdiff_t n = pptr() - pbase();
        if (n == 0) return 0;
        // if (!hasPeer_) return -1; // nowhere to send

        ssize_t sent = ::send(fd_,
                                pbase(), static_cast<std::size_t>(n),
                                0);
        // Reset put area regardless of result.
        setp(outBuf_.data(), outBuf_.data() + outBuf_.size());
        return (sent == n) ? 0 : -1;
    }

    int               fd_;
    std::vector<char> outBuf_;
    std::vector<char> inBuf_;
};