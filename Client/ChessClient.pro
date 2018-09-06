#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T16:50:50
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessClient
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    computer.cpp \
    fivechessboard.cpp \
    rule.cpp \
    stone.cpp

HEADERS  += dialog.h \
    usertype.h \
    computer.h \
    fivechessboard.h \
    rule.h \
    stone.h


DESTDIR =..\bin

FORMS    += dialog.ui
RC_FILE=\
    app.rc

RESOURCES += \
    images.qrc
