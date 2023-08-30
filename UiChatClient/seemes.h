#ifndef SEEMES_H
#define SEEMES_H

#include <QDialog>

namespace Ui {
class SeeMes;
}

class SeeMes : public QDialog
{
    Q_OBJECT

public:
    explicit SeeMes(QWidget *parent = nullptr);
    ~SeeMes();

private:
    Ui::SeeMes *ui;
};

#endif // SEEMES_H
