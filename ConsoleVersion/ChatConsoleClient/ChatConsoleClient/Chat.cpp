#include <iostream>
#include "Chat.h"
#include "mysql.h"
using namespace std;

void Chat::start() {
	isChatWork_ = true; // Флаг для выхода из меню
}

shared_ptr<User> Chat::getUserByLogin(const string& login) const
{
	for (auto& user : users_) // цикл проходит по всему массиву пользователей
	{
		if (login == user.getUserLogin()) // проверка совпадения логина
			return make_shared<User>(user); /// возвращает указатель на текущего пользователя
	}

	return nullptr;

}

shared_ptr<User> Chat::getUserByName(const string& name) const
{
	for (auto& user : users_)
	{
		if (name == user.getUserName())
			return make_shared<User>(user); // возвращает указатель на текущего пользователя по имени
	}

	return nullptr;

}

void Chat::login() // Авторизация в чат по уже созданному логину и паролю
{
		
	string currentid, login, password, name, email;
	char operation;
	bool isAuth{ false };
	do
	{
		cout << "Login: ";
		cin >> login;
		cout << "Password: ";
		cin >> password;
		
		if (login == "Banned" || login == "Deleted")
		{
			cout << "Error, try again" << endl;
			Chat::login();
		}
		

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

		string query = "SELECT * FROM user WHERE login_user = '" + login + "'";
		mysql_query(&mysql, query.c_str());
		//cout << query << endl;
		MYSQL_RES* res;
		MYSQL_ROW row;

		if ((res = mysql_store_result(&mysql)))
		{
			if ((row = mysql_fetch_row(res)))
			{
				
				//user.id = std::atoi(row[0]);
				currentid = string(row[0]);
				login = string(row[1]);
				password = string(row[2]);
				name = string(row[3]);
				email = string(row[4]);
				
				User user = User(login, password, name, email);
				users_.push_back(user);
				currentUser_ = make_shared<User>(user);
			}
			mysql_free_result(res);
		}
		//return nullptr;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ != nullptr && (password == currentUser_->getUserPassword()))
		{
			isAuth = true;
		}
		else
		{
			cout << "Login failed..." << endl;
			cout << "Press (0) to exit or another button to re-enter: ";
			cin >> operation;

			if (operation == '0')
				break;
		}

	} while (!isAuth);
}




void Chat::signUp() // Регистрация пользователя в чате
{
	string login, password, name, email;
	// 1.
	cout << "Login: ";
	cin >> login;
	cout << "Password: ";
	cin >> password;
	cout << "Name: ";
	cin >> name;
	cout << "Email: ";
	cin >> email;

	// if (getUserByLogin(login) || login == "all" || login == "Deleted")
	if ( login == "Banned" || login == "Deleted" )
	{
		throw UserLoginExp();
	}
	// if (getUserByName(name) || name == "all" || name == "Deleted")
	if ( name == "Banned" || name == "Deleted")
	{
		throw UserNameExp();
	}

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

	// 2.
	string requestregister = "SELECT EXISTS (SELECT * FROM user WHERE login_user = '" + login + "')";
	mysql_query(&mysql, requestregister.c_str());

	MYSQL_RES* res;
	MYSQL_ROW row;
	bool unique = false;
	if ((res = mysql_store_result(&mysql)))
	{
		if ((row = mysql_fetch_row(res)))
		{
			*row[0] == '0' ? unique = true : unique = false;

			//*row[0] == 0 ? unique = true : unique = false;
		}
		mysql_free_result(res);
	}
	else
	{
		cout << "if ((res = mysql_store_result(&mysql))) is not working" << endl;
	}
	// 3. Проверяем результат
	if (unique == false) {
		cout << "Error, this user already have account. Please restart the program" << endl;
		//throw UserLoginExp();
	}
	else
	{
		// 4.
		User user = User(login, password, name, email);
		users_.push_back(user);
		currentUser_ = make_shared<User>(user);
		string sqlString = "INSERT INTO user(id_user, login_user, password_user, name_user, email_user) VALUES(default, '" + login + "'" + "," + "'" + password + "'" + "," + "'" + name + "'" + "," + "'" + email + "'" + ")";
		mysql_query(&mysql, sqlString.c_str());
	}

}

void Chat::showChat() const // показывает отправленные сообщения, конкретному пользователю или всем
{
	string name;
	name = currentUser_->getUserName();
	//cout << "1:"<<  name << endl;
			
	cout << "Show sent or incoming messages?" << endl;
	cout << "(1)Sent" << endl;
	cout << "(2)Inconibg" << endl;
	char operation2;
	cin >> operation2;

	if (operation2 == '1')
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

		string sentmessage = "SELECT j1.name_user Sender, j2.name_user Recipient, text_message FROM message JOIN user j1 on message.sender = j1.id_user JOIN user j2 on message.recipient = j2.id_user WHERE j1.name_user = '" + name + "'; ";
		const char* showmessagelist2 = sentmessage.c_str();
		cout << sentmessage << endl;

		cout << "========================================================" << endl;
		cout << "Message list: " << endl;
		cout << "Sender || Recipient || Text Message " << endl;
		mysql_query(&mysql, showmessagelist2);
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
			cout << "MySQL error 4 " << mysql_error(&mysql) << endl;;

		cout << "- - - - - - - - - - - -" << endl;
	}
			

	else if (operation2 == '2')
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

		string sentmessage = "SELECT j1.name_user Sender, j2.name_user Recipient, text_message FROM message JOIN user j1 on message.sender = j1.id_user JOIN user j2 on message.recipient = j2.id_user WHERE j2.name_user = '" + name + "'; ";
		const char* showmessagelist2 = sentmessage.c_str();
		cout << sentmessage << endl;

		cout << "========================================================" << endl;
		cout << "Message list: " << endl;
		cout << " Sender || Recipient || Text Message " << endl;
		mysql_query(&mysql, showmessagelist2);
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
			cout << "MySQL error 4 " << mysql_error(&mysql) << endl;;

		cout << "- - - - - - - - - - - -" << endl;
	}
	else
	{
		cout << "Select 1 or 2 ..." << endl;
		cin >> operation2;

	}
		
	
}

void Chat::showLoginMenu() // Отображение стартового меню программы - Меню верхнего уровня
{
	currentUser_ = nullptr;

	char operation;

	do
	{
		cout << "(1)Login" << endl;
		cout << "(2)SignUp" << endl;
		cout << "(3)Developers" << endl;
		cout << "(0)Exit" << endl;
		//cout << "\033[36m" << ">> " << "\033[0m";
		cin >> operation;

		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case '3':
			cout << "The project was made by:" << endl;
			cout << "Dmitry Vorobiev" << endl;
			cout << "My page on Github - https://github.com/DmitryV17" << endl;
			cout << "To continue select one of the following options.." << endl;
			break;
		case '0':
			isChatWork_ = false;
			break;
		default:
			cout << "1 or 2 ..." << endl;
			break;

		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu() // отображает внутреннее меню чата, после авторизации пользователя
{
	char operation;

	cout << "Hello, " << currentUser_->getUserName() << endl;

	while (currentUser_)
	{
		cout << "(1)Show chat | (2)Send a message| (3)Show other users | (0)Exit ";

		cout << endl
			<< ">> ";
		cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '0':
			currentUser_ = nullptr;
			break;
		default:
			cout << "Make a choice, press a number.." << endl;
			break;
		}


	}
}

void Chat::showAllUsersName() const //Показать имена пользователей в чате
{
	cout << "- - - In chat - - -" << endl;



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

	string messagelist = "SELECT name_user  FROM user ;";
	const char* showmessagelist = messagelist.c_str();

	cout << "========================================================" << endl;
	cout << "User list: " << endl;

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

void Chat::addMessage() // Формирование сообщения
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

	string userName;
	string companionName;
	string senderID;
	string recipientID;
	string text;
	userName = currentUser_->getUserName();

	cout << "========================================================" << endl;
	cout << "To whom do you want to write a message?" << endl;
	string messagelist = "SELECT name_user  FROM user ;";
	const char* showmessagelist = messagelist.c_str();

	cout << "========================================================" << endl;
	cout << "User list: " << endl;

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
	
	cout << "Enter a name: " << endl;
	cin >> companionName;
	cout << "Write text message: " << endl;
	do // Вот здесь мне  приходится использовать такой цикл, чтобы getline нормально принимал текст
	{
		getline(cin, text);
	} while (!text.length() == 0);
	getline(cin, text);
	cout << text << endl;

	
	string query = "SELECT id_user from user where name_user = '" + userName + "'";
	mysql_query(&mysql, query.c_str());
	cout << query << endl;
	

	if ((res = mysql_store_result(&mysql)))
	{
		if ((row = mysql_fetch_row(res)))
		{
					
			senderID = string(row[0]);
			cout << "senderID is " << senderID << endl;
			
		}
		mysql_free_result(res);
	}
	
	string companionQuarry = "SELECT id_user from user where name_user = '" + companionName + "'";
	mysql_query(&mysql, companionQuarry.c_str());
	cout << companionQuarry << endl;
	//MYSQL_RES* res;
	//MYSQL_ROW row;

	if ((res = mysql_store_result(&mysql)))
	{
		if ((row = mysql_fetch_row(res)))
		{

			recipientID = string(row[0]);
			cout << "recipientID is "<< recipientID << endl;

		}
		mysql_free_result(res);
	}
     
	string sendmessage = "INSERT INTO message(id_message, sender, recipient, text_message, time_message) VALUES(default, " + senderID + "," + recipientID + "," + " ' " + text + " ' " + "," + "NOW()" + ")";
	cout << sendmessage << endl;
	const char* sendmessageofcourse = sendmessage.c_str();
	//cout << sendmessage << endl;
	cout << "========================================================" << endl;

	mysql_query(&mysql, sendmessageofcourse);

	cout << "========================================================" << endl;
	
	
}