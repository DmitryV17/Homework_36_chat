#include "database.h"
#include<iostream>
#include<vector>
#include<string>


bool createConnection(){

    MYSQL mysql; // Дескриптор соединения c MySql


    mysql_init(&mysql);

    if (&mysql == NULL) {
        // Если дескриптор не получен — выводим сообщение об ошибке
        QMessageBox::warning(0, "Error desctiptor connection", "Not connected");
        return false;
    }

    //Подключаемся к серверу, на котором должна быть создана база данных "Console_chat" root root это имя и пароль пользователя сервера
    if (!mysql_real_connect(&mysql, "localhost", "root", "IlovemySQL666!", "Console_chat", 0, NULL, 0)) {
        // Если нет возможности установить соединение с БД выводим сообщение об ошибке
        QMessageBox::warning(0, "Error  connection", "Not connected");
        return false;
    }
    else {
        // Если соединение успешно установлено выводим фразу — "Success!"
        //QMessageBox::information(0, "Connection is goodn", "Connection is on");
        return true;
    }

};

std::vector <std::string> seeusers(){

    MYSQL mysql;

    createConnection();

    MYSQL_RES* res;
    MYSQL_ROW row;
    int i = 0;

    std::string messagelist = "SELECT * FROM user ;";
    const char* showmessagelist = messagelist.c_str();

    std::vector<std::string> UqderList;
    mysql_query(&mysql, showmessagelist);
    if (res = mysql_store_result(&mysql)) {
        while (row = mysql_fetch_row(res)) {
            for (i = 0; i < mysql_num_fields(res); i++) {

                //std::cout << row[i] << "  ";
                UqderList[i] = row[i];
            }
            std::cout << std::endl;
        }
        mysql_free_result(res);
    }
    else
        std::cout << "MySQL error 4  " << mysql_error(&mysql) << std::endl;;

    std::vector<std::string> userList2;
    std::vector<QString> userList; for (const auto &qstr : userList) {
        userList2.push_back(qstr.toStdString());
    }
    return userList2;


    std::cout << "- - - - - - - - -" << std::endl;


};


DataBase::DataBase()
{

}



/*
DataBase::DataBase()
{

}
*/
