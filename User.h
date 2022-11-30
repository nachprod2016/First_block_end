#pragma once
#include <vector>
#include "Chat.h"

class User
{
private:
    size_t number;
    const std::string _name;
    std::vector<size_t> _contacts;
    std::vector<size_t> _chats;
public:
    User(std::string name, size_t number);
    ~User();
    std::vector<size_t> & getChats();
    std::vector<size_t> & getContacts();
    const std::string & getName() const;
    size_t  getNumber();
};