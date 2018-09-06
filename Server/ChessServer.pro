#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T15:22:45
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessServer
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    listensocket.cpp \
    clientsocket.cpp

HEADERS  += dialog.h \
    listensocket.h \
    clientsocket.h \
    usertype.h


DESTDIR =..\bin

FORMS    += dialog.ui

RESOURCES += \
    resource.qrc

RC_FILE=\
    app.rc
