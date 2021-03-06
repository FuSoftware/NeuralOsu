#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T18:50:16
#
#-------------------------------------------------

QT       += core gui
CONFIG += console c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeuralOsu
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    neural/network.cpp \
    neural/qneuralnetwork.cpp \
    neural/neuraltests.cpp \
    osu/interface/qbeatmaplist.cpp \
    osu/engine/qbeatmapscanner.cpp \
    osu/data/qbeatmap.cpp \
    osu/data/qosufile.cpp \
    osu/engine/qbeatmapengine.cpp \
    osu/data/items/timingpoint.cpp \
    osu/data/items/hitobject.cpp \
    osu/data/items/event.cpp \
    osu/osutests.cpp \
    osu/data/items/slider.cpp \
    osu/data/items/spinner.cpp

HEADERS += \
        widget.h \
    neural/network.h \
    neural/qneuralnetwork.h \
    neural/neuraltests.h \
    osu/interface/qbeatmaplist.h \
    osu/engine/qbeatmapscanner.h \
    osu/data/qbeatmap.h \
    osu/data/qosufile.h \
    osu/engine/qbeatmapengine.h \
    osu/data/items/timingpoint.h \
    osu/data/items/hitobject.h \
    osu/data/items/event.h \
    osu/osutests.h \
    osu/data/items/slider.h \
    osu/data/items/spinner.h
