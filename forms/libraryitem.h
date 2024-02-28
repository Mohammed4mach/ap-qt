#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QGroupBox>

namespace Ui {
class LibraryItem;
}

class LibraryItem : public QGroupBox
{
    Q_OBJECT

public:
    explicit LibraryItem(QWidget *parent = nullptr, char * file = (char *)"");
    ~LibraryItem();

private slots:
    void on_btn_delete_clicked();

private:
    Ui::LibraryItem *ui;
    char * file;
};

#endif // LIBRARYITEM_H
