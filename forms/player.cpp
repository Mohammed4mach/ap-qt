#include "player.h"
#include "ui_player.h"
#include <QDir>
#include <QtConcurrent/QtConcurrent>
#include <mpv/client.h>

static void wakeup(void * player)
{
    Player * widget = (Player *)player;

    emit widget->mpv_events();
}

Player::Player(QWidget *parent, QString file)
    : QGroupBox(parent)
    , ui(new Ui::Player),
    file(file)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    setlocale(LC_NUMERIC, "C");
    played = false;
    finished = true;

    try
    {
        mpv = new Mpv();

        mpv->loadfile((char *)file.toLocal8Bit().constData());
        played = true;
        finished = false;

        QString name = QString(mpv->get_title());
        ui->name->setText(name);

        connect(this, &Player::mpv_events, this, &Player::on_mpvEvents, Qt::QueuedConnection);
        mpv->set_wakeup_callback(wakeup, this);

        mpv->disable_video();
    }
    catch(int error)
    {
        ui->error->setText("Error");
    }

    ui->btn_close->setIcon(QIcon(":/assets/close-red.png"));
    ui->btn_close->setIconSize(QSize(15, 15));

    ui->btn_play->setIcon(
        QIcon(
            played ? ":/assets/pause.png" : ":/assets/play.png"
        )
    );
    ui->btn_play->setIconSize(QSize(25, 25));

    ui->btn_forward->setIcon(QIcon(":/assets/fast-forward.png"));
    ui->btn_forward->setIconSize(QSize(25, 25));

    ui->btn_backward->setIcon(QIcon(":/assets/previous.png"));
    ui->btn_backward->setIconSize(QSize(25, 25));

    ui->btn_speed_up->setIcon(QIcon(":/assets/speed-up.png"));
    ui->btn_speed_up->setIconSize(QSize(25, 25));

    ui->btn_speed_down->setIcon(QIcon(":/assets/speed-down.png"));
    ui->btn_speed_down->setIconSize(QSize(25, 25));

    ui->btn_reverse->setIcon(QIcon(":/assets/play-reverse.png"));
    ui->btn_reverse->setIconSize(QSize(25, 25));

    ui->chk_pitch_correction->setChecked(true);
}

Player::~Player()
{
    delete ui;
    delete mpv;
}

void Player::on_btn_play_clicked()
{
    if(finished)
    {
        mpv->loadfile((char *)file.toLocal8Bit().data());

        played = true;
        finished = false;
    }
    else
    {
        mpv->toggle_play();
        played = !played;
    }

    ui->btn_play->setIcon(
        QIcon(
            played ? ":/assets/pause.png" : ":/assets/play.png"
        )
    );
}

void Player::on_btn_close_clicked()
{
    close();
}

void Player::on_btn_speed_up_clicked()
{
    double speed = mpv->speed_up(0.1);
    ui->lbl_speed->setText(QString::number(speed));
}

void Player::on_btn_speed_down_clicked()
{
    double speed = mpv->speed_down(0.1);
    ui->lbl_speed->setText(QString::number(speed));
}

void Player::on_btn_forward_clicked()
{
    mpv->seek_forward(5);
}

void Player::on_btn_backward_clicked()
{
    mpv->seek_backward(5);
}

void Player::on_mpvEvents()
{
    while(mpv)
    {
        mpv_event * event = mpv->get_event();

        if(event->event_id == MPV_EVENT_NONE)
            break;

        switch(event->event_id)
        {
            case MPV_EVENT_END_FILE:
                finished = true;
                played = false;
                ui->btn_play->setIcon(QIcon(":/assets/play.png"));
                return;
        }
    }

    char * title = mpv->get_title();
    QString name = QString(title);
    ui->name->setText(name);
}

void Player::on_chk_pitch_correction_toggled(bool checked)
{
    mpv->set_pitch_correction(checked);
}

void Player::on_btn_reverse_pressed()
{
    mpv->play_backward();
}

void Player::on_btn_reverse_released()
{
    mpv->play_forward();
}

void Player::on_slider_volume_valueChanged(int value)
{
    double new_value = mpv->set_volume(value);
    ui->lbl_volume->setText(QString::number(new_value));
}
