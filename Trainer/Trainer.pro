TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_objdetect -lopencv_video -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_face

unix:!macx: LIBS += -L$$PWD/../Face-o-tron-lib/ -lFace-o-tron

INCLUDEPATH += $$PWD/../Face-o-tron
DEPENDPATH += $$PWD/../Face-o-tron
