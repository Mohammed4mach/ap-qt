#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "forms/libraryitem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refresh_library_list();

private slots:
    void on_btn_add_clicked();
    void on_libraryItemRemoved(LibraryItem * item);
    void on_libraryItemPlayed(LibraryItem * item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
