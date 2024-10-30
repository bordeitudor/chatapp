#ifndef WS2_H
#define WS2_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <cassert>
#include <memory>
#include <mutex>
#include <thread>
#include <list>
#include <vector>
#include <sstream>

#define DEFAULT_PORT "27015"
#define MSGBUF_LEN 8192
#define USERNAME_MAXLEN 16

namespace ws2 {

int error();
std::string strError(const int error = ws2::error());
void startup(WSADATA& wsaData);
void getAddressInfo(const char *name, const char *service, addrinfo& hints, addrinfo** result);
SOCKET createSocket(const int family, const int type, const int protocol);
int connect(const SOCKET socket, const sockaddr *addr, const size_t len);
void bind(const SOCKET socket, const sockaddr *addr, const size_t len);
void listen(const SOCKET socket, const int maxConnections = SOMAXCONN);


} // namespace ws2

#endif // WS2_H
