#include <iostream>
#include "mysql.h"
#include "Admin.h"

using namespace std;



void Admin::start() 

{
	bool isChatWork = true; /// Флаг для выхода из меню
	char operation;

	cout << "Hello, Admin" << endl;

	while (isChatWork)
	{
		cout << "(1)Show user list | (2)Show message list| (3)Ban user  (4)Delete User (5)Developer (0)Exit ";

		cout << endl
			<< ">> ";
		cin >> operation;

		switch (operation)
		{
		case '1':
			showUserList();
			break;
		case '2':
			showMessageList();
			break;
		case '3':
			Banhammer();
			break;
		case '4':
			DeleteUser();
			break;
		case '5':
			cout << "The project was made by:" << endl;
			cout << "Dmitry Vorobiev" << endl;
			cout << "My page on Github - https://github.com/DmitryV17" << endl;
			cout << "To continue select one of the following options.." << endl;
			break;
		case '0':
			isChatWork = false;
			break;
		default:
			cout << "Make a choice, press a number.." << endl;
			break;
		}

	}
}

void Admin::showUserList()
{
	
	MYSQL mysql; // Дескриптор соединения c MySql
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
		cout << "Success! connecting is on." << endl;
	}


	MYSQL_RES* res;
	MYSQL_ROW row;
	int i = 0;

	string messagelist = "SELECT * FROM user ;";
	const char* showmessagelist = messagelist.c_str();

	cout << "========================================================" << endl;
	cout << "User list: " << endl;
	cout << "|| User ID    || User login    || User password  ||  Username   ||  User email  " << endl;


	mysql_query(&mysql, showmessagelist);
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			for (i = 0; i < mysql_num_fields(res); i++) {
				cout << row[i] << "  ";
			}
			cout << endl;
		}
		mysql_free_result(res);
	}
	else
		cout << "MySQL error 4  " << mysql_error(&mysql) << endl;;


	cout << "- - - - - - - - -" << endl;

}
void Admin::showMessageList()
{
	
	MYSQL mysql; // Дескриптор соединения c MySql
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
		cout << "Success! connecting is on." << endl;
	}

	MYSQL_RES* res;
	MYSQL_ROW row;
	int i = 0;

	string messagelist = "SELECT id_message, j1.name_user Sender, j2.name_user Recipient, text_message, time_message FROM message JOIN user j1 on message.sender = j1.id_user JOIN user j2 on message.recipient = j2.id_user;";
	const char* showmessagelist = messagelist.c_str();

	cout << "========================================================" << endl;
	cout << "Message list: " << endl;
	cout << "|| id message || sender || recipient || text message  || time message " << endl;

	mysql_query(&mysql, showmessagelist);
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			for (i = 0; i < mysql_num_fields(res); i++) {
				cout << row[i] << "  ";
			}
			cout << endl;
		}
		mysql_free_result(res);
	}
	else
		cout << "MySQL error 4  " << mysql_error(&mysql) << endl;;

	cout << "- - - - - - - - -" << endl;

}
void Admin::Banhammer()
{
		
	MYSQL mysql; // Дескриптор соединения c MySql
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
		cout << "Success! connecting is on." << endl;
	}

	string userID;

	MYSQL_RES* res;
	MYSQL_ROW row;
	int i = 0;

	string messagelist = "SELECT id_user, login_user , name_user FROM user ;";
	const char* showmessagelist = messagelist.c_str();

	cout << "========================================================" << endl;
	cout << "User list: " << endl;
	cout << "|| User ID    || User login     ||  Username    " << endl;

	mysql_query(&mysql, showmessagelist);
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			for (i = 0; i < mysql_num_fields(res); i++) {
				cout << row[i] << "  ";
			}
			cout << endl;
		}
		mysql_free_result(res);
	}
	else
		cout << "MySQL error 4  " << mysql_error(&mysql) << endl;;

	cout << "Select ID user you want to ban" << endl;
	cin >> userID;

	string banhammerUser = "UPDATE user SET login_user = 'Banned' WHERE id_user = '" + userID + "';";
	const char* ban = banhammerUser.c_str();
	mysql_query(&mysql, ban);
	string banhammerUsert = "UPDATE user SET name_user = 'Banned' WHERE id_user = '" + userID + "';";
	const char* ban2 = banhammerUsert.c_str();
	mysql_query(&mysql, ban2);


}
void Admin::DeleteUser()
{
	
	MYSQL mysql; // Дескриптор соединения c MySql
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
		cout << "Success! connecting is on." << endl;
	}

	string userID;

	MYSQL_RES* res;
	MYSQL_ROW row;
	int i = 0;

	string messagelist = "SELECT id_user, login_user , name_user FROM user ;";
	const char* showmessagelist = messagelist.c_str();

	cout << "========================================================" << endl;
	cout << "User list: " << endl;
	cout << "|| User ID    || User login      ||  Username    " << endl;

	mysql_query(&mysql, showmessagelist);
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			for (i = 0; i < mysql_num_fields(res); i++) {
				cout << row[i] << "  ";
			}
			cout << endl;
		}
		mysql_free_result(res);
	}
	else
		cout << "MySQL error 4  " << mysql_error(&mysql) << endl;;

	cout << "Select ID user you want to ban" << endl;
	cin >> userID;

	string deleterUser1 = "UPDATE user SET login_user = 'Deleted' WHERE id_user = '" + userID + "';";
	const char* del1 = deleterUser1.c_str();
	mysql_query(&mysql, del1);
	string deleterUser2 = "UPDATE user SET name_user = 'Deleted' WHERE id_user = '" + userID + "';";
	const char* del2 = deleterUser2.c_str();
	mysql_query(&mysql, del2);
	string deleterUser3 = "UPDATE user SET password_user = 'Deleted' WHERE id_user = '" + userID + "';";
	const char* del3 = deleterUser3.c_str();
	mysql_query(&mysql, del3);
	string deleterUser4 = "UPDATE user SET email_user = 'Deleted' WHERE id_user = '" + userID + "';";
	const char* del4 = deleterUser4.c_str();
	mysql_query(&mysql, del4);
}
