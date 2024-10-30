#include "Client.h"

Client::operator bool() const
{
    return socket != INVALID_SOCKET;
}
