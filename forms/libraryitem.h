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
    explicit LibraryItem(QWidget *parent = nullptr, QString file = "");
    ~LibraryItem();
    QString get_track();
    QString get_track_name();

signals:
    void library_item_removed(LibraryItem * item);
    void library_item_played(LibraryItem * item);

private slots:
    void on_btn_delete_clicked();
    void on_btn_play_clicked();

private:
    Ui::LibraryItem *ui;
    QString track;
    QString track_name;
};

#endif // LIBRARYITEM_H
