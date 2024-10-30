#include "Message.h"

Message::operator bool() const
{
    return valid;
}

Message decodeMessage(std::string str)
{
    Message result;
    
    if(str.empty()) {
	return result;
    }

    if(str[0] == '@') {
	result.client = true;
	str = str.substr(1, str.size());
    }

    auto pos = str.find(',');

    if(pos == std::string::npos) {
	return result;
    }
    
    result.sender = str.substr(0, pos);

    if(result.sender.empty()) {
	return result;
    }

    result.content = str.substr(pos+1, str.size());
    result.valid = true;
    return result;
}
