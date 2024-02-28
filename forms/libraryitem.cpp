#include "libraryitem.h"
#include "ui_libraryitem.h"
#include <QDir>

LibraryItem::LibraryItem(QWidget *parent, QString file)
    : QGroupBox(parent)
    , ui(new Ui::LibraryItem)
    , track(file)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    QString name = file.split(QDir::separator()).last();
    ui->name->setText(name);

    ui->btn_play->setIcon(QIcon(":/assets/play-green.png"));
    ui->btn_play->setIconSize(QSize(30, 30));

    ui->btn_delete->setIcon(QIcon(":/assets/cross.png"));
    ui->btn_delete->setIconSize(QSize(13, 13));
}

LibraryItem::~LibraryItem()
{
    delete ui;
}

void LibraryItem::on_btn_delete_clicked()
{
    emit library_item_removed(this);
}

QString LibraryItem::get_track()
{
    return track;
}

void LibraryItem::on_btn_play_clicked()
{
    emit library_item_played(this);
}
