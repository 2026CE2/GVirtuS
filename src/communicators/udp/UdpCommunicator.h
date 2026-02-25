/**
 * @file   UdpCommunicator.h
 * @author Vasco Afonso, Sven Suneson, Casper Bramm, Kristian Brixx
 * @date   25/02/26
 *
 * @brief
 *
 *
 */

#pragma once

#ifdef _WIN32
#include <fstream>
#else
#include <ext/stdio_filebuf.h>
#endif

#include "gvirtus/communicators/Communicator.h"

namespace gvirtus::communicators {
/**
 * UdpCommunicator implements a Communicator for the TCP/IP socket.
 */
class UdpCommunicator : public Communicator {
   public:
    UdpCommunicator() = default;
    UdpCommunicator(const std::string &communicator);
    UdpCommunicator(const char *hostname, unsigned short port);
    UdpCommunicator(int fd, const char *hostname);
    virtual ~UdpCommunicator();
    void Serve();
    const Communicator *const Accept() const;
    void Connect();
    size_t Read(char *buffer, size_t size);
    size_t Write(const char *buffer, size_t size);
    void Sync();
    void Close();

    std::string to_string() override { return "UdpCommunicator"; }

   private:
    void InitializeStream();
    std::istream *mpInput;
    std::ostream *mpOutput;
    std::string mHostname;
    char *mInAddr;
    int mInAddrSize;
    unsigned short mPort;
    int mSocketFd;
#ifdef _WIN32
    std::filebuf *mpInputBuf;
    std::filebuf *mpOutputBuf;
#else
    __gnu_cxx::stdio_filebuf<char> *mpInputBuf;
    __gnu_cxx::stdio_filebuf<char> *mpOutputBuf;
#endif
};
}  // namespace gvirtus::communicators
