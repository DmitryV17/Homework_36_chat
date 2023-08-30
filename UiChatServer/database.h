#ifndef DATABASE_H
#define DATABASE_H

#include "mysql.h"
#include<QMessageBox>
#include<iostream>
#include<vector>

bool createConnection();
std::vector <std::string>  seeusers();



class DataBase
{
public:
    DataBase();
};



#endif // DATABASE_H
