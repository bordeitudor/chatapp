#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

struct Message
{
    bool        valid = false;
    bool        client = false;
    std::string sender = "";
    std::string content = "";

    operator bool() const;
    
    Message() = default;
};

Message decodeMessage(std::string str);

#endif // MESSAGE_H
