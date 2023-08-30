��� ������ ����������� ���� � �������������� ���� ������ MySQL, ������� ������������ ��� ������. ��� ������ � ��� ��������������� 
��� ��� ������� ���� ������� "Console_chat", ���� �� �� ��� �� ��� ���������� ��� �� �������:
1. �� ������� ���� ������ MySQL �������� ����� ���� ������ � �������� �:
   CREATE DATABASE Console_chat;
   USE  Console_chat;
2. ������ ����� ������� ������� � ������� �������������:
   CREATE TABLE user(id_user INT AUTO_INCREMENT PRIMARY KEY, login_user VARCHAR(255) NOT NULL, password_user VARCHAR(255), name_user VARCHAR(255), email_user VARCHAR(255));
   ��� ������� ��������� ����������� ��������� �� �������:
   INSERT INTO user(id_user, login_user, password_user, name_user, email_user) VALUES(default, 'Login', 'Password', 'Name', 'Email');
3. ������� ������ ������� � ����������� �������������:
   CREATE TABLE message(id_message INT AUTO_INCREMENT PRIMARY KEY, sender INT, recipient INT, text_message TEXT, time_message TIMESTAMP NOT NULL );
   � ��� ������� ����� �� id ������������� ��� ������������� � ����������� ���������:
   ALTER TABLE message ADD FOREIGN KEY(sender) REFERENCES user(id_user);
   ALTER TABLE message ADD FOREIGN KEY(recipient) REFERENCES user(id_user);
   ��� ������� ��������� ������ ������� ��������� �� �������:
   INSERT INTO message(id_message, sender, recipient, text_message, time_message) values(default, 1, 2, 'Text message', NOW());
   
������ ���� ������ ������ � ������. �������� ��������� Visual Studio ��� ������ � �������� MySQL:
   ��������� ����� ���������� Microsoft Visual C++ � �������� ����� ������ ������ "���������� ���������� Windows�.
   ����� ����� ������� �������� ������� (Property Pages) � ������� �������� ���� (������->��������).
   � ���� �������� ������� ������� �������� � ��������� "�������������� �������� ���������� ������" (�������� ������������->�/�++->�����) ������ "C:\Program Files\MySQL\MySQL Server 8.0\include".
   ����� � � ��������� "�������������� �������� ���������" (�������� ������������->�����������->�����) ������ "C:\Program Files\MySQL\MySQL Server 8.0\lib".
   ����� � ��������� "�������������� �����������" (�������� ������������->�����������->����) �������� �������� libmysql.lib:

   ������ ����� ������������ ������ ����������� ���� ��� ������ � �������� MySQL




