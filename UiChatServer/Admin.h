#ifndef ADMIN_H
#define ADMIN_H

#endif // ADMIN_H
#pragma once
#include <iostream>
#include "mysql.h"


using namespace std;


class Admin {

public:
    void start();/// запуск чата для админа

    void showUserList(); // Показать список всех пользователей
    void showMessageList(); // Показать все сообщения в чате
    void Banhammer(); // Забанить пользователя
    void DeleteUser();  // Удалить пользователя

};
