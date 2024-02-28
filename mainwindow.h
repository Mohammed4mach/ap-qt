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
    void refresh_library_list(bool fetch = true);

private slots:
    void on_btn_add_clicked();
    void on_libraryItemRemoved(LibraryItem * item);
    void on_libraryItemPlayed(LibraryItem * item);
    void on_input_search_textChanged(const QString &query);

private:
    Ui::MainWindow *ui;
    QStringList track_list;
    QStringList listed_tracks;
};
#endif // MAINWINDOW_H
