#-------------------------------------------------
#
# Project created by QtCreator 2014-01-22T13:48:37
#
#-------------------------------------------------

QT       += core gui
         QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scheduler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    course.cpp \
    scheduler.cpp \
    coursewidget.cpp \
    crnwidget.cpp \
    filedownloader.cpp

HEADERS  += mainwindow.h \
    course.h \
    scheduler.h \
    coursewidget.h \
    crnwidget.h \
    filedownloader.h

FORMS    += mainwindow.ui
