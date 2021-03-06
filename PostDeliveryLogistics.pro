#-------------------------------------------------
#
# Project created by QtCreator 2019-03-30T16:35:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PostDeliveryLogistics
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

SOURCES += \
        main.cpp \
       ui/mainwindow.cpp \
    ui/helpwindow.cpp \
    credentials.cpp \
    ui/loginscreen.cpp \
    ui/adminscreen.cpp \
    ui/userscreen.cpp \
    ui/graph/edge.cpp \
    ui/graph/node.cpp \
    ui/graph/graphwidget.cpp \
    ui/screen.cpp \
    ui/manipulator.cpp

HEADERS += \
    graph.h \
    serialize.h \
    singleton.h \
        ui/mainwindow.h \
    ui/helpwindow.h \
    credentials.h \
    ui/loginscreen.h \
    ui/adminscreen.h \
    ui/userscreen.h \
    ui/graph/edge.h \
    ui/graph/node.h \
    ui/graph/graphwidget.h \
    ui/screen.h \
    ui/manipulator.h \
    exceptions.h \
    allocator.h \
    iterator.h \
    invariant.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
