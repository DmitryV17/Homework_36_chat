#include "loginform.h"
#include "ui_loginform.h"
#include <QMessageBox>
#include <database.h>
LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_SwitchReg_clicked()
{
  emit RegistrationRequested();
}


void LoginForm::on_buttonBox_accepted()
{
     //Проверка логина и пароля


  QString userID;
  QString Login = ui->lineEdit_LogLogin->text();
  QMessageBox::warning(0, "Text Message ", Login);
  QString Password = ui->lineEdit_LogPass->text();
  QMessageBox::warning(0, "Password Message  ", Password);
  loginFound(userID,Login, Password);


  //lineEdit_LogLogin -  поле где вводится логин
  //lineEdit_LogPass = поле где вводится пароль
}


void LoginForm::on_buttonBox_rejected()
{

}

