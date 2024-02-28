#include "librarymanager.h"
#include <QDir>
#include <QFile>

QString LibraryManager::file_storage = QDir::homePath() + "/.apqt";

void LibraryManager::create_storage()
{
    QFile list_file = QFile(LibraryManager::file_storage);

    if(!list_file.exists())
    {
        list_file.open(QIODevice::WriteOnly);
        list_file.close();
    }
}

bool LibraryManager::add_track(QString path)
{
    QFile list_file(LibraryManager::file_storage);

    if(list_file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        path += "\n";
        qint64 status = list_file.write(path.toLocal8Bit());

        list_file.close();

        if(status == -1)
            return false;

        return true;
    }

    return false;
}

bool LibraryManager::remove_track(QString path)
{
    QFile list_file(LibraryManager::file_storage);

    if(list_file.open(QIODevice::ReadOnly))
    {
        path += "\n";

        QString remaining = "";

        while(true)
        {
            QString track = QString(list_file.readLine());

            if(track.isNull() || track.isEmpty())
                break;

            if(QString::compare(path, track) != 0)
                remaining += track;
        }

        list_file.close();

        if(list_file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qint64 status = list_file.write(remaining.toLocal8Bit());

            list_file.close();

            if(status == -1)
                return false;
        }

        return true;
    }

    return false;
}

QStringList LibraryManager::get_tracks()
{
    QFile list_file(LibraryManager::file_storage);
    QStringList list;

    if(list_file.open(QIODevice::ReadOnly))
    {
        while(true)
        {
            QString track = QString(list_file.readLine());

            if(track.isNull() || track.trimmed().isEmpty())
                break;

            list.append(track.trimmed());
        }

        return list;
    }

    throw -1;
}
