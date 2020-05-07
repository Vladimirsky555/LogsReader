#-------------------------------------------------
#
# Project created by QtCreator 2018-01-14T15:47:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0.0
QMAKE_TARGET_COMPANY = Smartech
QMAKE_TARGET_PRODUCT = LogReader
QMAKE_TARGET_DESCRIPTION = LogReader for Agent and ContentService
QMAKE_TARGET_COPYRIGHT = BearWin

win32: RC_ICONS = $$PWD/images/app.ico

TARGET = LogsReader
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qregexphighlighter.cpp \
    task_chosen_lines.cpp

HEADERS += \
        mainwindow.h \
    qregexphighlighter.h \
    task_chosen_lines.h

FORMS += \
        mainwindow.ui \
    task_chosen_lines.ui
