TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QT += core widget
SOURCES += main.cpp \
    queuebase.cpp

HEADERS += \
    queuebase.h \
    priorityqueue.h
