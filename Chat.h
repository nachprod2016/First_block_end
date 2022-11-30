#pragma once
#include <vector>
#include "Message.h"

class Chat
{
private:
    std::vector<Message> _mBox;
public:
    Chat();
    ~Chat();
    std::vector<Message> & getMessageBox();
};
