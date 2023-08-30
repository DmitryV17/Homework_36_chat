#include "writemes.h"
#include "ui_writemes.h"

WriteMes::WriteMes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WriteMes)
{
    ui->setupUi(this);
}

WriteMes::~WriteMes()
{
    delete ui;
}
