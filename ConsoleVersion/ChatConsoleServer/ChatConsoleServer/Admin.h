#pragma once
#include <iostream>
#include "mysql.h"


using namespace std;


class Admin {
	
public:
	void start();/// ������ ���� ��� ������
	
	void showUserList(); // �������� ������ ���� �������������
	void showMessageList(); // �������� ��� ��������� � ����
	void Banhammer(); // �������� ������������
	void DeleteUser();  // ������� ������������
	
};