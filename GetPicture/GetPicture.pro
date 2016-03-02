QT += core
QT -= gui

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_video -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio

TARGET = GetPicture
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    picture.cpp \
    timer.cpp

HEADERS += \
    picture.h \
    timer.h

