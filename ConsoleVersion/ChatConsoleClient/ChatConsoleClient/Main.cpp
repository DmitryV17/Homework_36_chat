﻿#include <iostream>
#include "Chat.h"
#include "mysql.h"


using namespace std;

int main()
{
	//setlocale(LC_ALL, ""); // Для кириллицы в консоли. 

	MYSQL mysql; // Дескриптор соединения c MySql
	MYSQL_RES* res;
	MYSQL_ROW row;
	int i = 0;

	mysql_init(&mysql);

	if (&mysql == NULL) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	//Подключаемся к серверу, на котором должна быть создана база данных "Console_chat" root root это имя и пароль пользователя сервера
	if (!mysql_real_connect(&mysql, "localhost", "root", "IlovemySQL666!", "Console_chat", 0, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	else {
		// Если соединение успешно установлено выводим фразу — "Success!"
		cout << "Success! Database connection established." << endl;
	}

	cout << "Welcome to console chat!" << endl;
	cout << "To continue select one of the following options.." << endl;
	cout << "=================================================================================================" << endl;

	Chat chat; //Объявляем чат

	chat.start(); //Запускаем

	while (chat.isChatWork()) { //Внешний цикл работы чата, когда он закончится состоится выход из программы 

		chat.showLoginMenu(); //Меню регистрации

		while (chat.getCurrentUser()) {
			chat.showUserMenu(); //Меню пользователя

		}

	}
	system("Pause");
	return 0;
}



