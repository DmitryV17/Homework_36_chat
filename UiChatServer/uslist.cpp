#include "uslist.h"
#include "ui_uslist.h"

UsList::UsList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsList)
{
    ui->setupUi(this);
}

UsList::~UsList()
{
    delete ui;
}
