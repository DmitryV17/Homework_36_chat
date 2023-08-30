#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static MainWindow* createClient();

private slots:
    void on_pushButton_Developer_clicked();

    void on_pushButton_SeeMessages_clicked();

    void on_pushButton_SeeUsers_clicked();

    void on_pushButton_Write_clicked();

    void on_actionOpen_another_client_triggered();

    void on_actionExit_triggered();

    void on_pushButton_QuitAccount_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
