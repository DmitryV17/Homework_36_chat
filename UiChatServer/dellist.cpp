#include "dellist.h"
#include "ui_dellist.h"

DelList::DelList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelList)
{
    ui->setupUi(this);
}

DelList::~DelList()
{
    delete ui;
}
