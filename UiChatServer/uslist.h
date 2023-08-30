#ifndef USLIST_H
#define USLIST_H

#include <QDialog>

namespace Ui {
class UsList;
}

class UsList : public QDialog
{
    Q_OBJECT

public:
    explicit UsList(QWidget *parent = nullptr);
    ~UsList();

private:
    Ui::UsList *ui;
};

#endif // USLIST_H
