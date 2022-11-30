#pragma once
#include "User.h"

class Server
{
private:
    std::string adminLogin;
    std::string adminPassword;
    std::vector<std::string> _passwords;
    std::vector<std::string> _logins;
    std::vector<User> _users;
    std::vector<Chat> _chats;
    bool workServer;
public:
    Server();
    ~Server();
    void serverWork();
    void registration();
    size_t authorization();
    void userWork(size_t userIndex);
    void showContactList(size_t userIndex);
    size_t checkChatIndex(std::string & choice, User & user);
    void showChat(Chat & chat);
    void createMessage(size_t chatIndex, size_t userIndex, std::string & message);
    size_t findContact();
    bool checkContact(size_t contact, User & user);
    void administratorWork();
    std::string textInput(std::string & message);
};