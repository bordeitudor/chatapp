#ifndef CLIENT_H
#define CLIENT_H

#include "WS2.h"

struct Client
{
    SOCKET      socket = INVALID_SOCKET;
    std::string username = "";

    operator bool() const;
};

#endif // CLIENT_H
