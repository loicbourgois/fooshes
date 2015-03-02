#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T19:05:04
#
#-------------------------------------------------

QT       += core gui
C
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fooshes
TEMPLATE = app

SOURCES += \
    main.cpp\
    main_window.cpp \
    scene.cpp \
    view.cpp \
    my_query_callback.cpp \
    food.cpp \
    living.cpp \
    fire.cpp \
    foosh.cpp \
    eye.cpp \
    neuron.cpp \
    brain.cpp \
    constants.cpp \
    options_form.cpp \
    infos_form.cpp \
    simulation.cpp

HEADERS += \
    options_form.hpp \
    infos_form.hpp \
    simulation.hpp \
    brain.hpp \
    constants.hpp \
    eye.hpp \
    fire.hpp \
    food.hpp \
    foosh.hpp \
    living.hpp \
    main_window.hpp \
    my_query_callback.hpp \
    neuron.hpp \
    scene.hpp \
    view.hpp

FORMS += \
    main_window.ui \
    options_form.ui \
    infos_form.ui

QMAKE_CXXFLAGS += -std=c++11

win32: LIBS += -L$$PWD/../../../../../Box2D_v2.3.0/Box2D-build/Box2D/ -lBox2D

INCLUDEPATH += $$PWD/../../../../../Box2D_v2.3.0/Box2D
DEPENDPATH += $$PWD/../../../../../Box2D_v2.3.0/Box2D

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../Box2D_v2.3.0/Box2D-build/Box2D/Box2D.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../Box2D_v2.3.0/Box2D-build/Box2D/libBox2D.a
