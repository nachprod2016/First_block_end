#include "Chat.h"

Chat::Chat(){}
Chat::~Chat(){}
std::vector<Message> & Chat::getMessageBox()
{
    return _mBox;
}