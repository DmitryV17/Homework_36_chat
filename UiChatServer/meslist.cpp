#include "meslist.h"
#include "ui_meslist.h"

MesList::MesList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MesList)
{
    ui->setupUi(this);
}

MesList::~MesList()
{
    delete ui;
}
