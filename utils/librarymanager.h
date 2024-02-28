#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <QString>
#include <QStringList>

/**
 * Utility to manage persistent data
 */
class LibraryManager
{
public:
    /**
     * Create the file to store persistent data if not exists
     */
    static void create_storage();

    /**
     * Add track to persistent data
     *
     * @param path Path to the track file
     * @return true if track is added successfully
     */
    static bool add_track(QString path);

    /**
     * Remove track from persistent data
     *
     * @param path Path to the track file
     * @return true if track is removed successfully
     */
    static bool remove_track(QString path);

    /**
     * Get all tracks in persistent data
     *
     * @return List of file paths
     */
    static QStringList get_tracks();

private:
    LibraryManager();
    static QString file_storage;
};

#endif // LIBRARYMANAGER_H
