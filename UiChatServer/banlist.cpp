#include "banlist.h"
#include "ui_banlist.h"

BanList::BanList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BanList)
{
    ui->setupUi(this);
}

BanList::~BanList()
{
    delete ui;
}
