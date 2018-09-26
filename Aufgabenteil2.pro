TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= QT += widgets

SOURCES += main.cpp \
    zeichenfeld.cpp \
    meinwidget.cpp

HEADERS += \
    meinwidget.h \
    zeichenfeld.h

QT += widgets
