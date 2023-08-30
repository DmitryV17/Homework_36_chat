#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "uslist.h"
#include "meslist.h"
#include "banlist.h"
#include "dellist.h"
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


void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox::information(this, "Help", "If program not working read Readme.txt file.");

}


void MainWindow::on_pushButton_6_clicked()
{
    QMessageBox::StandardButton retry =   QMessageBox::question(this, "Exit", "You want close application?", QMessageBox::Yes | QMessageBox::No );

    if (retry == QMessageBox::Yes){
        QApplication::quit();
    }

}


void MainWindow::on_pushButton_userList_clicked()
{
    UsList ulist;
    ulist.setModal(true);
    ulist.exec();

}


void MainWindow::on_pushButton_messageList_clicked()
{
    MesList meslist;
    meslist.setModal(true);
    meslist.exec();
}


void MainWindow::on_pushButton_ban_clicked()
{
    BanList banlist;
    banlist.setModal(true);
    banlist.exec();
}


void MainWindow::on_pushButton_Delete_clicked()
{
    DelList dellist;
    dellist.setModal(true);
    dellist.exec();
}

