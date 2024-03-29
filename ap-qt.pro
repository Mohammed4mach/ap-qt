QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    forms/libraryitem.cpp \
    forms/player.cpp \
    main.cpp \
    mainwindow.cpp \
    utils/librarymanager.cpp \
    utils/mpv.cpp

HEADERS += \
    forms/libraryitem.h \
    forms/player.h \
    mainwindow.h \
    utils/librarymanager.h \
    utils/mpv.h

FORMS += \
    forms/libraryitem.ui \
    forms/player.ui \
    mainwindow.ui

LIBS += `pkg-config --cflags --libs mpv`

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  app.qrc
