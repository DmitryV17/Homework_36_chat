#include <iostream>
#include "Chat.h"
#include "mysql.h"
//using namespace std;

void Chat::start() {
    isChatWork_ = true; // Флаг для выхода из меню
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
    for (auto& user : users_) // цикл проходит по всему массиву пользователей
    {
        if (login == user.getUserLogin()) // проверка совпадения логина
            return std::make_shared<User>(user); /// возвращает указатель на текущего пользователя
    }

    return nullptr;

}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
    for (auto& user : users_)
    {
        if (name == user.getUserName())
            return std::make_shared<User>(user); // возвращает указатель на текущего пользователя по имени
    }

    return nullptr;

}

void Chat::login() // Авторизация в чат по уже созданному логину и паролю
{

    std::string currentid, login, password, name, email;
    char operation;
    bool isAuth{ false };
    do
    {
        std::cout << "Login: ";
        std::cin >> login;
        std::cout << "Password: ";
        std::cin >> password;

        if (login == "Banned" || login == "Deleted")
        {
            std::cout << "Error, try again" << std::endl;
            Chat::login();
        }


        MYSQL mysql; // Дескриптор соединения c MySql
        mysql_init(&mysql);

        if (&mysql == NULL) {
            // Если дескриптор не получен — выводим сообщение об ошибке
            std::cout << "Error: can't create MySQL-descriptor" << std::endl;
        }

        //Подключаемся к серверу, на котором должна быть создана база данных "Console_chat" root root это имя и пароль пользователя сервера
        if (!mysql_real_connect(&mysql, "localhost", "root", "IlovemySQL666!", "Console_chat", 0, NULL, 0)) {
            // Если нет возможности установить соединение с БД выводим сообщение об ошибке
            std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
        }
        else {
            // Если соединение успешно установлено выводим фразу — "Success!"
            std::cout << "Success! connecting is on." << std::endl;
        }

        std::string query = "SELECT * FROM user WHERE login_user = '" + login + "'";
        mysql_query(&mysql, query.c_str());
        //cout << query << endl;
        MYSQL_RES* res;
        MYSQL_ROW row;

        if ((res = mysql_store_result(&mysql)))
        {
            if ((row = mysql_fetch_row(res)))
            {

                //user.id = std::atoi(row[0]);
                currentid = std::string(row[0]);
                login = std::string(row[1]);
                password = std::string(row[2]);
                name = std::string(row[3]);
                email = std::string(row[4]);

                User user = User(login, password, name, email);
                users_.push_back(user);
                currentUser_ = std::make_shared<User>(user);
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
            std::cout << "Login failed..." << std::endl;
            std::cout << "Press (0) to exit or another button to re-enter: ";
            std::cin >> operation;

            if (operation == '0')
                break;
        }

    } while (!isAuth);
}




void Chat::signUp() // Регистрация пользователя в чате
{
    std::string login, password, name, email;
    // 1.
    std::cout << "Login: ";
    std::cin >> login;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Email: ";
    std::cin >> email;

    // if (getUserByLogin(login) || login == "all" || login == "Deleted")
    if ( login == "Banned" || login == "Deleted" )
    {
        //throw UserLoginExp();
        std::cout<<"This account banned or delete, contact  to admin to know more."<< std::endl;
        Chat::signUp();
    }
    // if (getUserByName(name) || name == "all" || name == "Deleted")
    if ( name == "Banned" || name == "Deleted")
    {
        //throw UserNameExp();
        std::cout<<"This account banned or delete, contact  to admin to know more."<< std::endl;
        Chat::signUp();
    }

    MYSQL mysql; // Дескриптор соединения c MySql
    mysql_init(&mysql);

    if (&mysql == NULL) {
        // Если дескриптор не получен — выводим сообщение об ошибке
        std::cout << "Error: can't create MySQL-descriptor" << std::endl;
    }

    //Подключаемся к серверу, на котором должна быть создана база данных "Console_chat" root root это имя и пароль пользователя сервера
    if (!mysql_real_connect(&mysql, "localhost", "root", "IlovemySQL666!", "Console_chat", 0, NULL, 0)) {
        // Если нет возможности установить соединение с БД выводим сообщение об ошибке
        std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
    }
    else {
        // Если соединение успешно установлено выводим фразу — "Success!"
        std::cout << "Success! connecting is on." << std::endl;
    }

    // 2.
    std::string requestregister = "SELECT EXISTS (SELECT * FROM user WHERE login_user = '" + login + "')";
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
        std::cout << "if ((res = mysql_store_result(&mysql))) is not working" << std::endl;
    }
    // 3. Проверяем результат
    if (unique == false) {
        std::cout << "Error, this user already have account. Please restart the program" << std::endl;
        //throw UserLoginExp();
    }
    else
    {
        // 4.
        User user = User(login, password, name, email);
        users_.push_back(user);
        currentUser_ = std::make_shared<User>(user);
        std::string sqlString = "INSERT INTO user(id_user, login_user, password_user, name_user, email_user) VALUES(default, '" + login + "'" + "," + "'" + password + "'" + "," + "'" + name + "'" + "," + "'" + email + "'" + ")";
        mysql_query(&mysql, sqlString.c_str());
    }

}

void Chat::showChat() const // показывает отправленные сообщения, конкретному пользователю или всем
{
    std::string name;
    name = currentUser_->getUserName();
    //cout << "1:"<<  name << endl;

    std::cout << "Show sent or incoming messages?" << std::endl;
    std::cout << "(1)Sent" << std::endl;
    std::cout << "(2)Inconibg" << std::endl;
    char operation2;
    std::cin >> operation2;

    if (operation2 == '1')
    {

        MYSQL mysql; // Дескриптор соединения c MySql
        mysql_init(&mysql);

        if (&mysql == NULL) {
            // Если дескриптор не получен — выводим сообщение об ошибке
            std::cout << "Error: can't create MySQL-descriptor" << std::endl;
        }

        //Подключаемся к серверу, на котором должна быть создана база данных "Console_chat" root root это имя и пароль пользователя сервера
        if (!mysql_real_connect(&mysql, "localhost", "root", "IlovemySQL666!", "Console_chat", 0, NULL, 0)) {
            // Если нет возможности установить соединение с БД выводим сообщение об ошибке
            std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
        }
        else {
            // Если соединение успешно установлено выводим фразу — "Success!"
            std::cout << "Success! connecting is on." << std::endl;
        }

        MYSQL_RES* res;
        MYSQL_ROW row;
        int i = 0;

        std::string sentmessage = "SELECT j1.name_user Sender, j2.name_user Recipient, text_message FROM message JOIN user j1 on message.sender = j1.id_user JOIN user j2 on message.recipient = j2.id_user WHERE j1.name_user = '" + name + "'; ";
        const char* showmessagelist2 = sentmessage.c_str();
        std::cout << sentmessage << std::endl;

        std::cout << "========================================================" << std::endl;
        std::cout << "Message list: " << std::endl;
        std::cout << "Sender || Recipient || Text Message " << std::endl;
        mysql_query(&mysql, showmessagelist2);
        if (res = mysql_store_result(&mysql)) {
            while (row = mysql_fetch_row(res)) {
                for (i = 0; i < mysql_num_fields(res); i++) {
                    std::cout << row[i] << "  ";
                }
                std::cout << std::endl;
            }
            mysql_free_result(res);
        }
        else
            std::cout << "MySQL error 4 " << mysql_error(&mysql) << std::endl;;

        std::cout << "- - - - - - - - - - - -" << std::endl;
    }


    else if (operation2 == '2')
    {
        MYSQL mysql; // Дескриптор соединения c MySql
        mysql_init(&mysql);

        if (&mysql == NULL) {
            // Если дескриптор не получен — выводим сообщение об ошибке
            std::cout << "Error: can't create MySQL-descriptor" << std::endl;
        }

        //Подключаемся к серверу, на котором должна быть создана база данных "Console_chat" root root это имя и пароль пользователя сервера
        if (!mysql_real_connect(&mysql, "localhost", "root", "IlovemySQL666!", "Console_chat", 0, NULL, 0)) {
            // Если нет возможности установить соединение с БД выводим сообщение об ошибке
            std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
        }
        else {
            // Если соединение успешно установлено выводим фразу — "Success!"
            std::cout << "Success! connecting is on." << std::endl;
        }

        MYSQL_RES* res;
        MYSQL_ROW row;
        int i = 0;

        std::string sentmessage = "SELECT j1.name_user Sender, j2.name_user Recipient, text_message FROM message JOIN user j1 on message.sender = j1.id_user JOIN user j2 on message.recipient = j2.id_user WHERE j2.name_user = '" + name + "'; ";
        const char* showmessagelist2 = sentmessage.c_str();
        std::cout << sentmessage << std::endl;

        std::cout << "========================================================" << std::endl;
        std::cout << "Message list: " << std::endl;
        std::cout << " Sender || Recipient || Text Message " << std::endl;
        mysql_query(&mysql, showmessagelist2);
        if (res = mysql_store_result(&mysql)) {
            while (row = mysql_fetch_row(res)) {
                for (i = 0; i < mysql_num_fields(res); i++) {
                    std::cout << row[i] << "  ";
                }
                std::cout << std::endl;
            }
            mysql_free_result(res);
        }
        else
           std::cout << "MySQL error 4 " << mysql_error(&mysql) << std::endl;;

        std::cout << "- - - - - - - - - - - -" << std::endl;
    }
    else
    {
        std::cout << "Select 1 or 2 ..." << std::endl;
        std::cin >> operation2;

    }


}

void Chat::showLoginMenu() // Отображение стартового меню программы - Меню верхнего уровня
{
    currentUser_ = nullptr;

    char operation;

    do
    {
        std::cout << "(1)Login" << std::endl;
        std::cout << "(2)SignUp" << std::endl;
        std::cout << "(3)Developers" << std::endl;
        std::cout << "(0)Exit" << std::endl;
        //cout << "\033[36m" << ">> " << "\033[0m";
        std::cin >> operation;

        switch (operation)
        {
        case '1':
            login();
            break;
        case '2':
            //try
            //{
                signUp();
            //}
           // catch (const ) exception& e)
            //{
             //   cout << e.what() << endl;
            //}
            break;
        case '3':
            std::cout << "The project was made by:" << std::endl;
            std::cout << "Dmitry Vorobiev" << std::endl;
            std::cout << "My page on Github - https://github.com/DmitryV17" << std::endl;
            std::cout << "To continue select one of the following options.." << std::endl;
            break;
        case '0':
            isChatWork_ = false;
            break;
        default:
            std::cout << "1 or 2 ..." << std::endl;
            break;

        }
    } while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu() // отображает внутреннее меню чата, после авторизации пользователя
{
    char operation;

    std::cout << "Hello, " << currentUser_->getUserName() << std::endl;

    while (currentUser_)
    {
        std::cout << "(1)Show chat | (2)Send a message| (3)Show other users | (0)Exit ";

        std::cout << std::endl
             << ">> ";
        std::cin >> operation;

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
            std::cout << "Make a choice, press a number.." << std::endl;
            break;
        }


    }
}

void Chat::showAllUsersName() const //Показать имена пользователей в чате
{
    std::cout << "- - - In chat - - -" << std::endl;



    MYSQL mysql; // Дескриптор соединения c MySql
    mysql_init(&mysql);

    if (&mysql == NULL) {
        // Если дескриптор не получен — выводим сообщение об ошибке
        std::cout << "Error: can't create MySQL-descriptor" << std::endl;
    }

    //Подключаемся к серверу, на котором должна быть создана база данных "Console_chat" root root это имя и пароль пользователя сервера
    if (!mysql_real_connect(&mysql, "localhost", "root", "IlovemySQL666!", "Console_chat", 0, NULL, 0)) {
        // Если нет возможности установить соединение с БД выводим сообщение об ошибке
        std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
    }
    else {
        // Если соединение успешно установлено выводим фразу — "Success!"
        std::cout << "Success! connecting is on." << std::endl;
    }


    MYSQL_RES* res;
    MYSQL_ROW row;
    int i = 0;

    std::string messagelist = "SELECT name_user  FROM user ;";
    const char* showmessagelist = messagelist.c_str();

    std::cout << "========================================================" << std::endl;
    std::cout << "User list: " << std::endl;

    mysql_query(&mysql, showmessagelist);
    if (res = mysql_store_result(&mysql)) {
        while (row = mysql_fetch_row(res)) {
            for (i = 0; i < mysql_num_fields(res); i++) {
                std::cout << row[i] << "  ";
            }
            std::cout << std::endl;
        }
        mysql_free_result(res);
    }
    else
       std::cout << "MySQL error 4  " << mysql_error(&mysql) << std::endl;;


    std::cout << "- - - - - - - - -" << std::endl;
}

void Chat::addMessage() // Формирование сообщения
{
    MYSQL mysql; // Дескриптор соединения c MySql
    mysql_init(&mysql);

    if (&mysql == NULL) {
        // Если дескриптор не получен — выводим сообщение об ошибке
        std::cout << "Error: can't create MySQL-descriptor" << std::endl;
    }

    //Подключаемся к серверу, на котором должна быть создана база данных "Console_chat" root root это имя и пароль пользователя сервера
    if (!mysql_real_connect(&mysql, "localhost", "root", "IlovemySQL666!", "Console_chat", 0, NULL, 0)) {
        // Если нет возможности установить соединение с БД выводим сообщение об ошибке
        std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
    }
    else {
        // Если соединение успешно установлено выводим фразу — "Success!"
        std::cout << "Success! connecting is on." << std::endl;
    }
    MYSQL_RES* res;
    MYSQL_ROW row;
    int i = 0;

    std::string userName;
    std::string companionName;
    std::string senderID;
    std::string recipientID;
    std::string text;
    userName = currentUser_->getUserName();

    std::cout << "========================================================" << std::endl;
    std::cout << "To whom do you want to write a message?" << std::endl;
    std::string messagelist = "SELECT name_user  FROM user ;";
    const char* showmessagelist = messagelist.c_str();

    std::cout << "========================================================" << std::endl;
    std::cout << "User list: " << std::endl;

    mysql_query(&mysql, showmessagelist);
    if (res = mysql_store_result(&mysql)) {
        while (row = mysql_fetch_row(res)) {
            for (i = 0; i < mysql_num_fields(res); i++) {
                std::cout << row[i] << "  ";
            }
            std::cout << std::endl;
        }
        mysql_free_result(res);
    }
    else
        std::cout << "MySQL error 4  " << mysql_error(&mysql) << std::endl;;

    std::cout << "Enter a name: " << std::endl;
    std::cin >> companionName;
    std::cout << "Write text message: " << std::endl;
    do // Вот здесь мне  приходится использовать такой цикл, чтобы getline нормально принимал текст
    {
        getline(std::cin, text);
    } while (!text.length() == 0);
    getline(std::cin, text);
    std::cout << text << std::endl;


    std::string query = "SELECT id_user from user where name_user = '" + userName + "'";
    mysql_query(&mysql, query.c_str());
    std::cout << query << std::endl;


    if ((res = mysql_store_result(&mysql)))
    {
        if ((row = mysql_fetch_row(res)))
        {

            senderID = std::string(row[0]);
            std::cout << "senderID is " << senderID << std::endl;

        }
        mysql_free_result(res);
    }

    std::string companionQuarry = "SELECT id_user from user where name_user = '" + companionName + "'";
    mysql_query(&mysql, companionQuarry.c_str());
    std::cout << companionQuarry << std::endl;
    //MYSQL_RES* res;
    //MYSQL_ROW row;

    if ((res = mysql_store_result(&mysql)))
    {
        if ((row = mysql_fetch_row(res)))
        {

            recipientID = std::string(row[0]);
            std::cout << "recipientID is "<< recipientID << std::endl;

        }
        mysql_free_result(res);
    }

    std::string sendmessage = "INSERT INTO message(id_message, sender, recipient, text_message, time_message) VALUES(default, " + senderID + "," + recipientID + "," + " ' " + text + " ' " + "," + "NOW()" + ")";
    std::cout << sendmessage << std::endl;
    const char* sendmessageofcourse = sendmessage.c_str();
    //cout << sendmessage << endl;
    std::cout << "========================================================" << std::endl;

    mysql_query(&mysql, sendmessageofcourse);

    std::cout << "========================================================" << std::endl;

}
