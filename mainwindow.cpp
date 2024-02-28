#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "forms/player.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    ui->players_content->layout()->addWidget(new Player(nullptr, (char *)"/mnt/driveD/Programming/products/desktop/DJ/assets/test1.mp3"));
    ui->players_content->layout()->addWidget(new Player(nullptr, (char *)"/mnt/driveD/Programming/products/desktop/DJ/assets/test2.mp3"));
    ui->players_content->layout()->addWidget(new Player(nullptr, (char *)"/mnt/driveD/Programming/products/desktop/DJ/assets/test1.mp3"));
    ui->players_content->layout()->addWidget(new Player(nullptr, (char *)"/mnt/driveD/Programming/products/desktop/DJ/assets/test2.mp3"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
