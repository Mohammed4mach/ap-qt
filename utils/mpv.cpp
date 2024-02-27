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

  return new_value;
}

void Mpv::loadfile(char * path)
{
  const char * cmd[] = {"loadfile", path, NULL};

  int status = mpv_command(this->_handle, cmd);

  if(status < MPV_ERROR_SUCCESS)
    throw -1;
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

Mpv::~Mpv()
{
  mpv_destroy(this->_handle);
}
