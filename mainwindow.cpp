#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "forms/player.h"
#include "utils/librarymanager.h"
#include <QFileDialog>
#include <QDir>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    ui->btn_add->setIcon(QIcon(":/assets/add.png"));
    ui->btn_add->setIconSize(QSize(20, 20));

    refresh_library_list();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_add_clicked()
{
    QString path = QFileDialog::getOpenFileName(
        this,
        tr("Select file"),
        "",
        tr("Audio Files (*.m4a *.mp3 *.ogg *.oga *.mogg *.opus *.wav *.wma *.wv)")
    );

    if(path.isNull())
        return;

    if(LibraryManager::add_track(path))
        refresh_library_list();
}

void MainWindow::refresh_library_list(bool fetch)
{
    try
    {
        if(fetch)
        {
            QStringList tracks = LibraryManager::get_tracks();

            track_list = tracks;
            listed_tracks = tracks;
        }

        auto layout = ui->library_content->layout();

        while(layout->count())
        {
            auto item = layout->itemAt(0);
            auto widget = item->widget();

            layout->removeWidget(widget);
            widget->close();
        }

        foreach(QString track, listed_tracks)
        {
            LibraryItem * item = new LibraryItem(nullptr, track);

            this->ui->library_content->layout()->addWidget(item);
            connect(item, &LibraryItem::library_item_removed, this, &MainWindow::on_libraryItemRemoved);
            connect(item, &LibraryItem::library_item_played, this, &MainWindow::on_libraryItemPlayed);
        }
    }
    catch(int error)
    {

    }
}

void MainWindow::on_libraryItemRemoved(LibraryItem * item)
{
    QString path = item->get_track();

    bool success = LibraryManager::remove_track(path);

    if(success)
        refresh_library_list();
}

void MainWindow::on_libraryItemPlayed(LibraryItem * item)
{
    QString path = item->get_track();

    ui->players_content->layout()->addWidget(new Player(nullptr, path));
}

void MainWindow::on_input_search_textChanged(const QString &query)
{
    listed_tracks.clear();

    foreach(QString track, track_list)
    {
        QString filename = QFileInfo(track).fileName();

        if(filename.contains(query))
            listed_tracks.append(track);
    }

    if(query.isEmpty())
        listed_tracks = track_list;

    refresh_library_list(false);
}
