QT += core
QT -= gui

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_video -lopencv_core -lopencv_objdetect -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio

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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Face-o-tron-lib/release/ -lFace-o-tron
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Face-o-tron-lib/debug/ -lFace-o-tron
else:unix: LIBS += -L$$PWD/../Face-o-tron-lib/ -lFace-o-tron

INCLUDEPATH += $$PWD/../Face-o-tron
DEPENDPATH += $$PWD/../Face-o-tron
