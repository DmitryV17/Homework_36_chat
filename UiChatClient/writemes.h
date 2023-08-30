#ifndef WRITEMES_H
#define WRITEMES_H

#include <QDialog>

namespace Ui {
class WriteMes;
}

class WriteMes : public QDialog
{
    Q_OBJECT

public:
    explicit WriteMes(QWidget *parent = nullptr);
    ~WriteMes();

private:
    Ui::WriteMes *ui;
};

#endif // WRITEMES_H
