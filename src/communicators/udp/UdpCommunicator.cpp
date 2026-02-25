/**
 * @file   UdpCommunicator.cpp
 * @author Vasco Afonso, Sven Suneson, Casper Bramm, Kristian Brixx
 * @date   25/02/26
 *
 * @brief
 *
 *
 */
// #define DEBUG

#include "UdpCommunicator.h"

#ifndef _WIN32

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#else
#include <WinSock2.h>
static bool initialized = false;
#endif

#include <gvirtus/communicators/Endpoint.h>
#include <gvirtus/communicators/Endpoint_Tcp.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;
using gvirtus::communicators::UdpCommunicator;

UdpCommunicator::UdpCommunicator(const std::string &communicator) {
#ifdef _WIN32
    if (!initialized) {
        WSADATA data;
        if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
            throw runtime_error("Cannot initialized WinSock.");
        initialized = true;
    }
#endif

    // ?????????????????????????????

    // const char *valueptr = strstr(communicator.c_str(), "://") + 3;
    // const char *portptr = strchr(valueptr, ':');
    // if (portptr == NULL) throw runtime_error("Port not specified.");
    // mPort = (short)strtol(portptr + 1, NULL, 10);
    
    const size_t valueptr = communicator.find("://") + 3;
    const size_t portptr = communicator.find(":");
    if (portptr == NULL) throw runtime_error("Port not specified.");
    mPort = static_cast<unsigned short>(std::stoi(communicator.substr(portptr +1)));


    mHostname = communicator.substr(valueptr, portptr - valueptr);
    struct hostent *ent = gethostbyname(mHostname.c_str());

    if (ent == NULL)
        throw runtime_error("UdpCommunicator: Can't resolve hostname '" + mHostname + "'.");
    mInAddrSize = ent->h_length;
    mInAddr = new char[mInAddrSize];
    memcpy(mInAddr, *ent->h_addr_list, mInAddrSize);
}

UdpCommunicator::UdpCommunicator(const char *hostname, unsigned short port) {
    mHostname = string(hostname);
    struct hostent *ent = gethostbyname(hostname);
    if (ent == NULL)
        throw runtime_error("UdpCommunicator: Can't resolve hostname '" + mHostname + "'.");
    mInAddrSize = ent->h_length;
    mInAddr = new char[mInAddrSize];
    memcpy(mInAddr, *ent->h_addr_list, mInAddrSize);
    mPort = port;
}

UdpCommunicator::UdpCommunicator(int fd, const char *hostname) {
    mSocketFd = fd;
    InitializeStream();
}

UdpCommunicator::~UdpCommunicator() {
    //    close(mSocketFd);
    delete[] mInAddr;
}

void UdpCommunicator::Serve() {
#ifdef DEBUG
    printf("UdpCommunicator::Serve() called\n");
#endif

    struct sockaddr_in socket_addr;

    if ((mSocketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw runtime_error("UdpCommunicator: Can't create socket: " + string(strerror(errno)) +
                            ".");

    memset((char *)&socket_addr, 0, sizeof(struct sockaddr_in));

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(mPort);
    socket_addr.sin_addr.s_addr = INADDR_ANY;

    char on = 1;
    setsockopt(mSocketFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    int bindResult = bind(mSocketFd, (struct sockaddr *)&socket_addr, sizeof(struct sockaddr_in));
    if (bindResult != 0)
        throw runtime_error("UdpCommunicator: Can't bind socket: " + string(strerror(errno)) + ".");

    int listenResult = listen(mSocketFd, 5);
    if (listenResult != 0)
        throw runtime_error(
            "UdpCommunicator: Can't listen from socket: " + string(strerror(errno)) + ".");

#ifdef DEBUG
    cout << "UdpCommunicator::Serve() returned" << endl;
#endif
}

const gvirtus::communicators::Communicator *const UdpCommunicator::Accept() const {
#ifdef DEBUG
    cout << "UdpCommunicator::Accept() called" << endl;
#endif

    unsigned client_socket_fd;
    struct sockaddr_in client_socket_addr;
#ifndef _WIN32
    unsigned client_socket_addr_size;
#else
    int client_socket_addr_size;
#endif

    client_socket_addr_size = sizeof(struct sockaddr_in);
    if ((client_socket_fd =
             accept(mSocketFd, (sockaddr *)&client_socket_addr, &client_socket_addr_size)) == 0 ||
        errno == EINTR) {
        return nullptr;
    }

#ifdef DEBUG
    cout << "UdpCommunicator::Accept() client_socket_fd: " << client_socket_fd << endl;
#endif
    return new UdpCommunicator(client_socket_fd, inet_ntoa(client_socket_addr.sin_addr));
}

void UdpCommunicator::Connect() {
#ifdef DEBUG
    cout << "UdpCommunicator::Connect() called " < < < < endl;
#endif

    struct sockaddr_in remote;

    if ((mSocketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw runtime_error("UdpCommunicator: Can't create socket: " + string(strerror(errno)) +
                            ".");

    remote.sin_family = AF_INET;
    remote.sin_port = htons(mPort);
    memcpy(&remote.sin_addr, mInAddr, mInAddrSize);

    if (connect(mSocketFd, (struct sockaddr *)&remote, sizeof(struct sockaddr_in)) != 0)
        throw runtime_error("UdpCommunicator: Can't connect to socket: " + string(strerror(errno)) +
                            ".");

    InitializeStream();

#ifdef DEBUG
    cout << "UdpCommunicator::Connect() returned" << endl;
#endif
}

void UdpCommunicator::Close() {}

size_t UdpCommunicator::Read(char *buffer, size_t size) {
#ifdef DEBUG
    cout << "UdpCommunicator::Read() size: " << size << endl;
#endif

    mpInput->read(buffer, size);

#ifdef DEBUG
    for (unsigned int i = 0; i < size; i++) printf("%d LETTO %02X\n", i, buffer[i]);
#endif

    size_t ret_value;
    if (mpInput->bad() || mpInput->eof())
        ret_value = 0;
    else
        ret_value = size;

#ifdef DEBUG
    cout << "UdpCommunicator::Read() returned " << ret_value << endl;
#endif

    return ret_value;
}

size_t UdpCommunicator::Write(const char *buffer, size_t size) {
#ifdef DEBUG
    cout << "UdpCommunicator::Write() called" << endl;
#endif

    mpOutput->write(buffer, size);

#ifdef DEBUG
    for (unsigned int i = 0; i < size; i++) printf("%d SCRITTO %02X \n", i, buffer[i]);
#endif

#ifdef DEBUG
    cout << "UdpCommunicator::Write() returned" << size << endl;
#endif

    return size;
}

void UdpCommunicator::Sync() { mpOutput->flush(); }

void UdpCommunicator::InitializeStream() {
#ifdef _WIN32
    FILE *i = _fdopen(mSocketFd, "r");
    FILE *o = _fdopen(mSocketFd, "w");
    mpInputBuf = new filebuf(i);
    mpOutputBuf = new filebuf(o);
#else
    mpInputBuf = new __gnu_cxx::stdio_filebuf<char>(mSocketFd, ios_base::in);
    mpOutputBuf = new __gnu_cxx::stdio_filebuf<char>(mSocketFd, ios_base::out);
#endif

    mpInput = new istream(mpInputBuf);
    mpOutput = new ostream(mpOutputBuf);
}

extern "C" std::shared_ptr<UdpCommunicator> create_communicator(
    std::shared_ptr<gvirtus::communicators::Endpoint> end) {
    std::string arg =
        "udp://" + std::dynamic_pointer_cast<gvirtus::communicators::Endpoint_Tcp>(end)->address() +
        ":" +
        std::to_string(
            std::dynamic_pointer_cast<gvirtus::communicators::Endpoint_Tcp>(end)->port());
    return std::make_shared<UdpCommunicator>(arg);
}
