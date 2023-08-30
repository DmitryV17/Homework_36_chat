#include "seeus.h"
#include "ui_seeus.h"

SeeUs::SeeUs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeeUs)
{
    ui->setupUi(this);
}

SeeUs::~SeeUs()
{
    delete ui;
}
