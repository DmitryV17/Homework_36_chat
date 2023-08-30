#ifndef USER_H
#define USER_H

#endif // USER_H
#pragma once
#include <string>
//using namespace std;

class User
{
private:
    const std::string login_; // логин пользователя
    std::string password_;  // пароль
    std::string name_; // имя пользователя
    std::string email_; // почтовый ящик пользователя

public:
    User(const std::string& login, const std::string& password, const std::string& name, const std::string& email)
        :login_(login), password_(password), name_(name), email_(email) {}

    const std::string& getUserLogin() const noexcept { return this->login_; } /// прочитать логин пользователя

    const std::string& getUserPassword() const { return this->password_; } /// прочитать пароль пользователя
    void setUserPassword(const std::string& password) { this->password_ = password; } /// изменит пароль пользователя

    const std::string& getUserName() const { return this->name_; } /// прочитать имя пользователя
    void setUserName(const std::string& name) { this->name_ = name; } /// изменить имя пользователя

    const std::string& getUserEmail() const { return this->email_; } /// прочитать почтовый ящик  пользователя
    void setUserEmail(const std::string& email) { this->email_ = email; } /// изменить почтовый ящик пользователя
};
