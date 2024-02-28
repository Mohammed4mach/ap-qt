#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "forms/player.h"
#include "forms/libraryitem.h"
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    ui->btn_add->setIcon(QIcon(":/assets/add.png"));
    ui->btn_add->setIconSize(QSize(20, 20));

    refresh_library_list();

    ui->players_content->layout()->addWidget(new Player(nullptr, (char *)"/mnt/driveD/Programming/products/desktop/DJ/assets/test1.mp3"));
    ui->players_content->layout()->addWidget(new Player(nullptr, (char *)"/mnt/driveD/Programming/products/desktop/DJ/assets/test1.mp3"));
    ui->players_content->layout()->addWidget(new Player(nullptr, (char *)"/mnt/driveD/Programming/products/desktop/DJ/assets/test2.mp3"));
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

    QFile list_file(QDir::homePath() + "/.apqt");

    if(list_file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        path += "\n";
        list_file.write(path.toLocal8Bit());

        list_file.close();

        refresh_library_list();
    }
}

void MainWindow::refresh_library_list()
{
    QFile list_file(QDir::homePath() + "/.apqt");

    if(list_file.open(QIODevice::ReadOnly))
    {
        auto layout = ui->library_content->layout();

        while(layout->count())
        {
            auto item = layout->itemAt(0);
            auto widget = item->widget();

            qDebug() << layout->count();
            layout->removeWidget(widget);
            widget->close();
        }

        while(true)
        {
            auto line = list_file.readLine();

            if(line.isNull())
                break;

            this->ui->library_content->layout()->addWidget(new LibraryItem(nullptr, (char *)line.trimmed().constData()));
        }
    }
}
