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

BOX2D = ../../../../Box2D_v2.3.0/Box2D/Box2D/

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
    simulation.cpp \
    $${BOX2D}/Collision/Shapes/b2ChainShape.cpp \
    $${BOX2D}/Collision/Shapes/b2CircleShape.cpp \
    $${BOX2D}/Collision/Shapes/b2EdgeShape.cpp \
    $${BOX2D}/Collision/Shapes/b2PolygonShape.cpp \
    $${BOX2D}/Collision/b2BroadPhase.cpp \
    $${BOX2D}/Collision/b2CollideCircle.cpp \
    $${BOX2D}/Collision/b2CollideEdge.cpp \
    $${BOX2D}/Collision/b2CollidePolygon.cpp \
    $${BOX2D}/Collision/b2Collision.cpp \
    $${BOX2D}/Collision/b2Distance.cpp \
    $${BOX2D}/Collision/b2DynamicTree.cpp \
    $${BOX2D}/Collision/b2TimeOfImpact.cpp \
    $${BOX2D}/Common/b2BlockAllocator.cpp \
    $${BOX2D}/Common/b2Draw.cpp \
    $${BOX2D}/Common/b2Math.cpp \
    $${BOX2D}/Common/b2Settings.cpp \
    $${BOX2D}/Common/b2StackAllocator.cpp \
    $${BOX2D}/Common/b2Timer.cpp \
    $${BOX2D}/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    $${BOX2D}/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    $${BOX2D}/Dynamics/Contacts/b2CircleContact.cpp \
    $${BOX2D}/Dynamics/Contacts/b2Contact.cpp \
    $${BOX2D}/Dynamics/Contacts/b2ContactSolver.cpp \
    $${BOX2D}/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    $${BOX2D}/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    $${BOX2D}/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    $${BOX2D}/Dynamics/Contacts/b2PolygonContact.cpp \
    $${BOX2D}/Dynamics/Joints/b2DistanceJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2FrictionJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2GearJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2Joint.cpp \
    $${BOX2D}/Dynamics/Joints/b2MotorJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2MouseJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2PrismaticJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2PulleyJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2RevoluteJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2RopeJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2WeldJoint.cpp \
    $${BOX2D}/Dynamics/Joints/b2WheelJoint.cpp \
    $${BOX2D}/Dynamics/b2Body.cpp \
    $${BOX2D}/Dynamics/b2ContactManager.cpp \
    $${BOX2D}/Dynamics/b2Fixture.cpp \
    $${BOX2D}/Dynamics/b2Island.cpp \
    $${BOX2D}/Dynamics/b2World.cpp \
    $${BOX2D}/Dynamics/b2WorldCallbacks.cpp \
    $${BOX2D}/Rope/b2Rope.cpp \
    ihm/control_form.cpp \
    ihm/new_simulation_dialog.cpp

HEADERS += \
    options_form.hpp \
    simulation.hpp \
    brain.hpp \
    constants.hpp \
    eye.hpp \
    fire.hpp \
    food.hpp \
    foosh.hpp \
    living.hpp \
    my_query_callback.hpp \
    neuron.hpp \
    scene.hpp \
    view.hpp \
    $${BOX2D}/Collision/Shapes/b2ChainShape.h \
    $${BOX2D}/Collision/Shapes/b2CircleShape.h \
    $${BOX2D}/Collision/Shapes/b2EdgeShape.h \
    $${BOX2D}/Collision/Shapes/b2PolygonShape.h \
    $${BOX2D}/Collision/Shapes/b2Shape.h \
    $${BOX2D}/Collision/b2BroadPhase.h \
    $${BOX2D}/Collision/b2Collision.h \
    $${BOX2D}/Collision/b2Distance.h \
    $${BOX2D}/Collision/b2DynamicTree.h \
    $${BOX2D}/Collision/b2TimeOfImpact.h \
    $${BOX2D}/Common/b2BlockAllocator.h \
    $${BOX2D}/Common/b2Draw.h \
    $${BOX2D}/Common/b2GrowableStack.h \
    $${BOX2D}/Common/b2Math.h \
    $${BOX2D}/Common/b2Settings.h \
    $${BOX2D}/Common/b2StackAllocator.h \
    $${BOX2D}/Common/b2Timer.h \
    $${BOX2D}/Dynamics/Contacts/b2ChainAndCircleContact.h \
    $${BOX2D}/Dynamics/Contacts/b2ChainAndPolygonContact.h \
    $${BOX2D}/Dynamics/Contacts/b2CircleContact.h \
    $${BOX2D}/Dynamics/Contacts/b2Contact.h \
    $${BOX2D}/Dynamics/Contacts/b2ContactSolver.h \
    $${BOX2D}/Dynamics/Contacts/b2EdgeAndCircleContact.h \
    $${BOX2D}/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
    $${BOX2D}/Dynamics/Contacts/b2PolygonAndCircleContact.h \
    $${BOX2D}/Dynamics/Contacts/b2PolygonContact.h \
    $${BOX2D}/Dynamics/Joints/b2DistanceJoint.h \
    $${BOX2D}/Dynamics/Joints/b2FrictionJoint.h \
    $${BOX2D}/Dynamics/Joints/b2GearJoint.h \
    $${BOX2D}/Dynamics/Joints/b2Joint.h \
    $${BOX2D}/Dynamics/Joints/b2MotorJoint.h \
    $${BOX2D}/Dynamics/Joints/b2MouseJoint.h \
    $${BOX2D}/Dynamics/Joints/b2PrismaticJoint.h \
    $${BOX2D}/Dynamics/Joints/b2PulleyJoint.h \
    $${BOX2D}/Dynamics/Joints/b2RevoluteJoint.h \
    $${BOX2D}/Dynamics/Joints/b2RopeJoint.h \
    $${BOX2D}/Dynamics/Joints/b2WeldJoint.h \
    $${BOX2D}/Dynamics/Joints/b2WheelJoint.h \
    $${BOX2D}/Dynamics/b2Body.h \
    $${BOX2D}/Dynamics/b2ContactManager.h \
    $${BOX2D}/Dynamics/b2Fixture.h \
    $${BOX2D}/Dynamics/b2Island.h \
    $${BOX2D}/Dynamics/b2TimeStep.h \
    $${BOX2D}/Dynamics/b2World.h \
    $${BOX2D}/Dynamics/b2WorldCallbacks.h \
    $${BOX2D}/Rope/b2Rope.h \
    $${BOX2D}/Box2D.h \
    infos_form.hpp \
    main_window.hpp \
    ihm/control_form.hpp \
    ihm/new_simulation_dialog.hpp

FORMS += \
    main_window.ui \
    options_form.ui \
    infos_form.ui \
    ihm/control_form.ui \
    ihm/new_simulation_dialog.ui

QMAKE_CXXFLAGS += -std=c++11

win32: LIBS += -L$$PWD/../../../../../Box2D_v2.3.0/Box2D-build/Box2D/ -lBox2D

INCLUDEPATH += $$PWD/../../../../../Box2D_v2.3.0/Box2D
DEPENDPATH += $$PWD/../../../../../Box2D_v2.3.0/Box2D

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../Box2D_v2.3.0/Box2D-build/Box2D/Box2D.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../Box2D_v2.3.0/Box2D-build/Box2D/libBox2D.a
