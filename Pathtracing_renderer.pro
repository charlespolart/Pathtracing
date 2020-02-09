#-------------------------------------------------
#
# Project created by QtCreator 2019-10-14T18:02:08
#
#-------------------------------------------------

QT       += core gui opengl

LIBS += -lopengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pathtracing_renderer
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

CONFIG += c++11

SOURCES += \
        Camera.cpp \
        CastRay.cpp \
        CollisionTree.cpp \
        Engine.cpp \
        FileImport.cpp \
        Obj3d.cpp \
        Raytracing.cpp \
        Scene.cpp \
        Vector.cpp \
        GLWidget.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        Camera.h \
        CastRay.h \
        CollisionTree.h \
        Engine.h \
        FileImport.h \
        MainWindow.h \
        Obj3d.h \
        Ray.h \
        Raytracing.h \
        Scene.h \
        Vector.h \
        GLWidget.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
