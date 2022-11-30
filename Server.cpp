#include <iostream>
#include <cstdlib>
#include "Server.h"

Server::Server() : workServer(true)
{
    std::cout << "Создание учетной записи администратора" << std::endl;
    std::cout << "Логин: ";
    std::cin >> adminLogin;
    std::cout << "Пароль: ";
    std::cin >> adminPassword;
}

Server::~Server(){}

void Server::serverWork()
{
    std::string choice;
    while(workServer)
    {
        std::cout << "1 - Регистрация" << std::endl;
        std::cout << "2 - Вход" << std::endl;
        std::cout << "Ввод: ";
        std::cin >> choice;
        system("clear");
        if (choice == "1")
        {
            registration();
        }
        else if (choice == "2")
        {
            size_t userIndex = authorization();
            if (userIndex == -1)
            {
                std::cout << "Неверный логин или пароль" << std::endl;
            }
            else if (userIndex == -2)
            {
               administratorWork();
               system("clear");
            }
            else
            {
                userWork(userIndex);
            }
        }
    }
}

void Server::registration()
{
    std::string login;
    std::string password;
    std::string name;
    std::cout << "Создание новой учетной записи:" << std::endl;
    std::cout << "Логин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;
    std::cout << "Имя: ";
    std::cin >> name;
    size_t size = _users.size();
    bool flag = false;
    for (size_t i = 0; i < size; i++)
    {
        if (login == _logins[i])
        {
            flag = true;
            break;
        }
    }
    if (flag == false)
    {
        _users.push_back(User(name, size));
        _logins.push_back(login);
        _passwords.push_back(password);
    }
    else
    {
        std::cout << "Пользователь с таким логином уже зарегистрирован" << std::endl;
        std::cout << "Ввод: ";
        std::cin >> login;
    }
    system("clear");
}

size_t Server::authorization()
{
    size_t index = -1;
    std::string login;
    std::string password;
    std::cout << "Логин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;
    if (login == adminLogin)
    {
        if (password == adminPassword)
        {
            index = -2;
        }
    }
    else
    {
        size_t size = _users.size();
        for (size_t i = 0; i < size; i++)
        {
            if (_logins[i] == login)
            {
                if (_passwords[i] == password)
                {
                    index = i;
                    break;
                }
            }
        }
    }
    system("clear");
    return index;
}

void Server::userWork(size_t userIndex)
{
    bool flag(true);
    std::string choice;
    while (flag)
    {
        std::cout << "1 - Список контактов" << std::endl;
        std::cout << "2 - Добавить контакт" << std::endl;
        std::cout << "3 - Написать всем" << std::endl;
        std::cout << "4 - Завершить сеанс" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice;
        system("clear");
        if (choice == "1")
        {
            showContactList(userIndex);
            std::cout << "Выбор: ";
            std::cin >> choice;
            size_t chatIndex = checkChatIndex(choice, _users[userIndex]);
            if (chatIndex != -1)
            {
                showChat(_chats[chatIndex]);
                std::cout << "Написать сообщение?" << std::endl;
                std::cout << "1 - Да" << std::endl;
                std::cout << "2 - Нет" << std::endl;
                std::cout << "Ввод: ";
                std::cin >> choice;
                if (choice == "1")
                {
                    textInput(choice);
                    createMessage(chatIndex, userIndex, choice);
                }
            }
        }
        else if (choice == "2")
        {
            size_t contactIndex = findContact();
            if (contactIndex != -1)
            {
                if (checkContact(contactIndex, _users[userIndex]) == false)
                {
                    _chats.push_back(Chat());
                    size_t chatIndex = _chats.size() - 1;
                    _users[userIndex].getChats().push_back(chatIndex);
                    _users[contactIndex].getChats().push_back(chatIndex);
                    _users[userIndex].getContacts().push_back(contactIndex);
                    _users[contactIndex].getContacts().push_back(userIndex);
                    textInput(choice);
                    createMessage(chatIndex, userIndex, choice);
                }
            }
        }
        else if (choice == "3")
        {
            std::vector<size_t> & contacts = _users[userIndex].getContacts();
            size_t size = contacts.size();
            if (size == 0)
            {
                std::cout << "У вас еще нет контактов" << std::endl;
                std::cout << "Ввод: ";
                std::cin >> choice; 
            }
            else
            {
                textInput(choice);
                for (size_t i = 0; i < size; i++)
                {
                    size_t chatIndex = _users[userIndex].getChats()[contacts[i]];
                    _chats[chatIndex].getMessageBox().push_back(Message(_users[userIndex].getName(), choice));
                }
            }
        }
        else if (choice == "4")
        {
            flag = false;
        }
        system("clear");
    }
}

void Server::showContactList(size_t userIndex)
{
    User & user = _users[userIndex];
    size_t size = user.getContacts().size();
    std::vector<size_t> contacts = user.getContacts();
    for (size_t i = 0; i < size; i++)
    {
        std::cout << i + 1 << " - " << _users[contacts[i]].getName() << std::endl;
    }
}

size_t Server::checkChatIndex(std::string & choice, User & user)
{
    size_t index = -1;
    if (choice != "0")
    {
        if (choice.size() < 9)
        {
            size_t check = atoi(&choice[0]);
            if (check > 0 && check <= user.getChats().size())
            {
                index = check - 1;
                return user.getChats()[index];
            }
            return index;
        }
    }
    return index;
}

void Server::showChat(Chat & chat)
{
    system("clear");
    std::vector<Message> & mBox = chat.getMessageBox();
    size_t size = mBox.size();
    for (size_t i = 0; i < size; i++)
    {
        std::cout << mBox[i].getAuthor() << ": ";
        std::cout << mBox[i].getMessage() << std::endl;
    }
}

void Server::createMessage(size_t chatIndex, size_t userIndex, std::string & message)
{
    _chats[chatIndex].getMessageBox().push_back(Message(_users[userIndex].getName(), message));
    system("clear");
}

std::string  Server::textInput(std::string & message)
{
    std::cout << "Сообщение: ";
    std::getline(std::cin, message);//очистка потока ввода
    std::getline(std::cin, message);//ввод сообщения
    return message;
}

size_t Server::findContact()
{
    size_t contact = -1;
    std::string name;
    std::cout << "Имя нового контакта: ";
    std::cin >> name;
    size_t size = _users.size();
    for (size_t i = 0; i < size; i++)
    {
        if (_users[i].getName() == name)
        {
            contact = i;
            break;
        }
    }
    return contact;
}

bool Server::checkContact(size_t contact, User & user)
{
    bool flag = false;
    std::vector<size_t> contacts = user.getContacts();
    size_t size = contacts.size();
    if (contact == user.getNumber())
    {
        flag = true;
        std::cout << "Введен собственный логин" << std::endl;
    }
    else
    {
        for (size_t i = 0; i < size; i++)
        {
            if (contact == contacts[i])
            {
                std::cout << "Пользователь уже в списке контактов" << std::endl;
                flag = true;
                break;
            }
        }
    }
    return flag;
}

void Server::administratorWork()
{
    bool flag = true;
    while (flag)
    {
        std::string choice;
        std::cout << "1 - Показать пользователей чата" << std::endl;
        std::cout << "2 - Остановить работу чата" << std::endl;
        std::cout << "3 - Завершить сеанс" << std::endl;
        std::cout << "Ввод: ";
        std::cin >> choice;
        system("clear");
        if (choice == "1")
        {
            while (true)
            {
                size_t size = _users.size();
                for (size_t i = 0; i < size; i++)
                {
                    std::cout << i + 1 << " - " << _users[i].getName() << std::endl;
                }
                std::cout << "0 - Для выхода из списка пользователей: ";
                std::cin >> choice;
                system("clear");
                if (choice == "0")
                {
                    break;
                }
            }
        }
        else if (choice == "2")
        {
            workServer = false;
            flag = false;
        }
        else if (choice == "3")
        {
            flag = false;
        }
    }
}