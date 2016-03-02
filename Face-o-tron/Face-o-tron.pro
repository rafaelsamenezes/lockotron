#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T13:52:19
#
#-------------------------------------------------

QT       -= gui

TARGET = Face-o-tron
TEMPLATE = lib

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_objdetect -lopencv_video -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_face

DEFINES += FACEOTRON_LIBRARY

SOURCES += faceotron.cpp \
    facedetection.cpp \
    facepre.cpp \
    haarcascade.cpp \
    trainer.cpp

HEADERS += faceotron.h\
    facedetection.h \
    facepre.h \
    haarcascade.h \
    trainer.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
