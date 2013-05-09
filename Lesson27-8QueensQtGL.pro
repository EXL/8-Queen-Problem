#-------------------------------------------------
#
# Project created by QtCreator 2013-04-10T19:43:42
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lesson27-8QueensQtGL
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    glwgt.cpp \
    logic.cpp

HEADERS  += widget.h \
    glwgt.h \
    logic.h

RESOURCES += \
    qtgl.qrc

RC_FILE += \
    res_win.rc

TRANSLATIONS += \
    queens_ru.ts \
    queens_en.ts
