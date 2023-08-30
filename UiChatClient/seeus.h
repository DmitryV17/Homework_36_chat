#ifndef SEEUS_H
#define SEEUS_H

#include <QDialog>

namespace Ui {
class SeeUs;
}

class SeeUs : public QDialog
{
    Q_OBJECT

public:
    explicit SeeUs(QWidget *parent = nullptr);
    ~SeeUs();

private:
    Ui::SeeUs *ui;
};

#endif // SEEUS_H
