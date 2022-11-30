#pragma once
#include <string>

class Message
{
private:
    const std::string _author;
    const std::string _message;
public:
    Message(const std::string & author, const std::string & message);
    ~Message();
    const std::string & getAuthor() const;
    const std::string & getMessage() const;
};