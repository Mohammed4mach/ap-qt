#ifndef PLAYER_H
#define PLAYER_H

#include <QGroupBox>
#include "utils/mpv.h"

namespace Ui {
class Player;
}

class Player : public QGroupBox
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = nullptr, QString file = "");
    ~Player();

private slots:
    void on_btn_play_clicked();

    void on_btn_close_clicked();

    void on_btn_speed_up_clicked();

    void on_btn_speed_down_clicked();

    void on_btn_forward_clicked();

    void on_btn_backward_clicked();

signals:
    void mpv_events();

private slots:
    void on_mpvEvents();

    void on_chk_pitch_correction_toggled(bool checked);

    void on_btn_reverse_pressed();

    void on_btn_reverse_released();

    void on_slider_volume_valueChanged(int value);

private:
    Ui::Player *ui;
    Mpv * mpv;
    QString file;
    bool played;
    bool finished;
};

#endif // PLAYER_H
