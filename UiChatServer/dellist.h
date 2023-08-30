#ifndef DELLIST_H
#define DELLIST_H

#include <QDialog>

namespace Ui {
class DelList;
}

class DelList : public QDialog
{
    Q_OBJECT

public:
    explicit DelList(QWidget *parent = nullptr);
    ~DelList();

private:
    Ui::DelList *ui;
};

#endif // DELLIST_H
