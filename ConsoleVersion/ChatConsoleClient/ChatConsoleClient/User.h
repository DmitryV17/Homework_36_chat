#pragma once
#include <string>
using namespace std;

class User
{
private:
	const string login_; // ����� ������������
	string password_;  // ������
	string name_; // ��� ������������
	string email_; // �������� ���� ������������

public:
	User(const string& login, const string& password, const string& name, const string& email)
		:login_(login), password_(password), name_(name), email_(email) {}

	const string& getUserLogin() const noexcept { return this->login_; } /// ��������� ����� ������������

	const string& getUserPassword() const { return this->password_; } /// ��������� ������ ������������
	void setUserPassword(const string& password) { this->password_ = password; } /// ������� ������ ������������

	const string& getUserName() const { return this->name_; } /// ��������� ��� ������������
	void setUserName(const string& name) { this->name_ = name; } /// �������� ��� ������������

	const string& getUserEmail() const { return this->email_; } /// ��������� �������� ����  ������������
	void setUserEmail(const string& email) { this->email_ = email; } /// �������� �������� ���� ������������
};