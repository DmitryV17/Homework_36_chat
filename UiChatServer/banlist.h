#ifndef BANLIST_H
#define BANLIST_H

#include <QDialog>

namespace Ui {
class BanList;
}

class BanList : public QDialog
{
    Q_OBJECT

public:
    explicit BanList(QWidget *parent = nullptr);
    ~BanList();

private:
    Ui::BanList *ui;
};

#endif // BANLIST_H
