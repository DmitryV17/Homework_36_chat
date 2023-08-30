#ifndef MESLIST_H
#define MESLIST_H

#include <QDialog>

namespace Ui {
class MesList;
}

class MesList : public QDialog
{
    Q_OBJECT

public:
    explicit MesList(QWidget *parent = nullptr);
    ~MesList();

private:
    Ui::MesList *ui;
};

#endif // MESLIST_H
