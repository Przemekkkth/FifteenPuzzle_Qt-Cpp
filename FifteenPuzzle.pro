QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    game.cpp \
    gamescene.cpp \
    main.cpp \
    pixmapitem.cpp \
    view.cpp

HEADERS += \
    game.h \
    gamescene.h \
    pixmapitem.h \
    view.h

RESOURCES += \
    resource.qrc

