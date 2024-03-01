#include "mpv.h"

Mpv::Mpv()
{
    this->_handle = mpv_create();

    if(!this->_handle)
        throw -1;

    int status = mpv_initialize(this->_handle);

    if(status < MPV_ERROR_SUCCESS)
        throw -1;
}

double Mpv::change_double_property(char * name, double amount)
{
    double current_value = 0.000000;

    mpv_get_property(this->_handle, name, MPV_FORMAT_DOUBLE, &current_value);

    double new_value = current_value + amount;

    mpv_set_property(this->_handle, name, MPV_FORMAT_DOUBLE, &new_value);
    mpv_get_property(this->_handle, name, MPV_FORMAT_DOUBLE, &new_value);

    return new_value;
}

void Mpv::change_flag_property(char * name, bool on)
{
    int flag = on ? 1 : 0;

    mpv_set_property(this->_handle, name, MPV_FORMAT_FLAG, &flag);
}

void Mpv::change_string_property(char * name, char * value)
{
    mpv_set_option_string(this->_handle, name, value);
}

void Mpv::loadfile(char * path)
{
    const char * cmd[] = {"loadfile", path, NULL};

    int status = mpv_command(this->_handle, cmd);

    if(status < MPV_ERROR_SUCCESS)
        throw -1;
}

char * Mpv::filename()
{
    char * name = mpv_get_property_string(this->_handle, "media-title");

    return name;
}

void Mpv::toggle_play()
{
    const char * cmd[] = {"cycle", "pause", NULL};

    mpv_command(this->_handle, cmd);
}

double Mpv::change_volume(double amount)
{
    return change_double_property((char *)"volume", amount);
}

double Mpv::volume_up(double amount)
{
    return this->change_volume(amount);
}

double Mpv::volume_down(double amount)
{
    return this->change_volume(-amount);
}

double Mpv::change_speed(double amount)
{
    return change_double_property((char *)"speed", amount);
}

double Mpv::speed_up(double amount)
{
    return this->change_speed(amount);
}

double Mpv::speed_down(double amount)
{
    return this->change_speed(-amount);
}

double Mpv::seek_forward(double amount)
{
    return this->change_double_property((char *)"time-pos", amount);
}

double Mpv::seek_backward(double amount)
{
    return this->change_double_property((char *)"time-pos", -amount);
}

mpv_event * Mpv::get_event(double timeout)
{
    return mpv_wait_event(this->_handle, timeout);
}

void Mpv::set_wakeup_callback(void (* callback)(void * data), void * data)
{
    mpv_set_wakeup_callback(this->_handle, callback, data);
}

void Mpv::set_no_video(bool on)
{
    change_flag_property((char *)"no-video", on);
}

void Mpv::disable_video()
{
    change_string_property((char *)"vo", (char *)"null");
}

char * Mpv::get_title()
{
    char * title = mpv_get_property_string(this->_handle, (char *)"media-title");

    return title;
}

void Mpv::set_pitch_correction(bool on)
{
    char * name = (char *)"audio-pitch-correction";
    char * value = on ? (char *)"yes" : (char *)"no";

    change_string_property(name, value);
}

Mpv::~Mpv()
{
    mpv_destroy(this->_handle);
}
