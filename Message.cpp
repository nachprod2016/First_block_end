#include "Message.h"

Message::Message(const std::string & author, const std::string & message) : _author(author), _message(message){}

Message::~Message(){};

const std::string & Message::getAuthor() const
{
    return _author;
}

const std::string & Message::getMessage() const
{
    return _message;
}