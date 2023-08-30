#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "seemes.h"
#include "seeus.h"
#include "writemes.h"
#include "startscreen.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::createClient()
{
    StartScreen s;
    s.exec();
    return nullptr;
}


void MainWindow::on_pushButton_Developer_clicked()
{
    QMessageBox::information(this, "Developer", "The project was made by Dmitry Vorobiev. If chat not working read Readme.txt file");

}


void MainWindow::on_pushButton_SeeMessages_clicked()
{
    SeeMes mesList;
    mesList.setModal(true);
    mesList.exec();
}


void MainWindow::on_pushButton_SeeUsers_clicked()
{
    SeeUs usList;
    usList.setModal(true);
    usList.exec();
    //seeusers() - функция для вывода всех пользователей
    //listWidget_SeeUs - окно куда должны выводится результаты
}


void MainWindow::on_pushButton_Write_clicked()
{
    WriteMes wrime;
    wrime.setModal(true);
    wrime.exec();
}


void MainWindow::on_actionOpen_another_client_triggered()
{
    createClient();
}


void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton retry =   QMessageBox::question(this, "Exit", "You want close application?", QMessageBox::Yes | QMessageBox::No );

    if (retry == QMessageBox::Yes){
        QApplication::quit();
    }
}


void MainWindow::on_pushButton_QuitAccount_clicked()
{
    // Тут выход из программы ы целом
    QMessageBox::StandardButton retry =   QMessageBox::question(this, "Exit", "You want close application?", QMessageBox::Yes | QMessageBox::No );

    if (retry == QMessageBox::Yes){
        QApplication::quit();
    }
}

