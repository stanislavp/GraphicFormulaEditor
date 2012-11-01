#-------------------------------------------------
#
# Project created by QtCreator 2012-10-27T00:36:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicFormulaEditor
TEMPLATE = app

FORMS    += MainWindow.ui

include (Config/files.pri)

HEADERS += \
    GraphicSystem/src/rowmoving.h \
    GraphicSystem/CursorPosition.h

SOURCES += \
    GraphicSystem/src/rowmoving.cpp \
    GraphicSystem/rowMoving.cpp \
    GraphicSystem/RowMoving.cpp \
    GraphicSystem/src/CursorPosition.cpp
