#ifndef CHAT_H
#define CHAT_H
#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"
#include "User.h"


#endif // CHAT_H

//using namespace std;

/*-----Исключение-----*/
/*
struct UserLoginExp : public exception
{
    const char* what() const noexcept override { return "error: user login is busy"; }
};

struct UserNameExp : public exception
{
    const char* what() const noexcept override { return "error: user name is busy"; }
};
*/

class Chat {
    bool isChatWork_ = false; /// Флаг для выхода из меню
    std::vector<User> users_; /// Динамический массив (вектор) текущих пользователей
    std::vector<Message> messages_; /// Динамический массив (вектор) сообщений
    std::shared_ptr<User> currentUser_ = nullptr; /// показывает текущего пользователя

    void login();/// Авторизация в чат по уже созданному логину и паролю
    void signUp(); /// Регистрация пользователя в чате
    void showChat() const; // показывает отправленные сообщения, конкретному пользователю или всем
    void showAllUsersName() const; /// Показывает  список пользователей чата
    void addMessage(); //Формирования сообщения
    std::vector<User>& getAllUsers() { return users_; }
    std::vector<Message>& getAllMessage() { return messages_; }
    std::shared_ptr<User> getUserByLogin(const std::string& login) const;
    std::shared_ptr<User> getUserByName(const std::string& name) const;

public:
    void start();/// запуск чата
    bool isChatWork() const { return isChatWork_; } /// проверка, работает чат или нет (если true - чат работает, если false - нет)
    std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
    void showLoginMenu(); /// Отображение стартового меню программы - Меню верхнего уровня
    void showUserMenu(); // отображает внутреннее меню чата, после авторизации пользователя
};

