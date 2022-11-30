#include "User.h"

User::User(std::string name, size_t number) : _name(name), number(number) {}

User::~User(){}

std::vector<size_t> & User::getChats()
{
    return _chats;
}

std::vector<size_t> & User::getContacts()
{
    return _contacts;
}

const std::string & User::getName() const
{
    return _name;
}

size_t User::getNumber()
{
    return number;
}