#ifndef MPV_H
#define MPV_H

#include <mpv/client.h>

/**
 * libmpv wrapper for basic mpv operations
 */
class Mpv
{
  private:
    mpv_handle * _handle;

    /**
     * Change property value of type double
     *
     * @param name Name of the property
     * @param amount Amount to be added to the property value
     */
    double change_double_property(char * name, double amount);

  public:
    /**
     * Construct new `Mpv` object.
     * `mpv_handle` is created and initialized during this method.
     */
    Mpv();

    /**
     * Load track
     *
     * @param path Path to the file
     */
    void loadfile(char * path);

    /**
     * Play/Pause current track
     */
    void toggle_play();

    /**
     * Change volume of the track
     *
     * @param amount Amount to be added to current volume level
     *
     * @return new level after change
     */
    double change_volume(double amount);

    /**
     * Increase volume of the track
     *
     * @param amount Amount to be added to current volume level
     *
     * @return new level after increase
     */
    double volume_up(double amount);

    /**
     * Deacrease volume of the track
     *
     * @param amount Amount to be subtracted from current volume level
     *
     * @return new level after deacrease
     */
    double volume_down(double amount);

    /**
     * Change playing speed of the track
     *
     * @param amount Amount to be added to current speed
     *
     * @return current speed
     */
    double change_speed(double amount);

    /**
     * Increase playing speed of the track
     *
     * @param amount Amount to be added to current speed
     *
     * @return current speed
     */
    double speed_up(double amount);

    /**
     * Decrease playing speed of the track
     *
     * @param amount Amount to be subtracted from current speed
     *
     * @return current speed
     */
    double speed_down(double amount);

    /**
     * Seek forward the track
     *
     * @param seconds Number of seconds to seek forward
     *
     * @return seconds passed
     */
    double seek_forward(double seconds);

    /**
     * Seek backward the track
     *
     * @param seconds Number of seconds to seek backward
     *
     * @return seconds passed
     */
    double seek_backward(double seconds);

    /**
     * Free the `mpv_handle` variable
     */
    ~Mpv();
};

#endif // MPV_H
