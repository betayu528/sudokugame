#-------------------------------------------------
#
# Project created by QtCreator 2017-02-07T10:52:34
#
#-------------------------------------------------

QT       += core gui

DESTDIR = ../bin

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudoku
TEMPLATE = app

SUBDIRS += /tests/sudokutest.pro

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/itemwidget.cpp \
    src/optiondialog.cpp \
    src/sudoku.cpp \
    src/sudokuboard.cpp \
    src/gameboard.cpp \
    src/loghandler.cpp

HEADERS  += src/mainwindow.h \
    src/itemwidget.h \
    src/optiondialog.h \
    src/sudoku.h \
    src/sudokuboard.h \
    src/gameboard.h \
    src/loghandler.h

RESOURCES += \
    resources/png.qrc

FORMS += \
    resources/form.ui


#ICON = sudoku.icns
