#include "seemes.h"
#include "ui_seemes.h"

SeeMes::SeeMes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeeMes)
{
    ui->setupUi(this);
}

SeeMes::~SeeMes()
{
    delete ui;
}
