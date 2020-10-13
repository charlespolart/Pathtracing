#-------------------------------------------------
#
# Project created by QtCreator 2019-10-14T18:02:08
#
#-------------------------------------------------

QT       += core gui opengl

LIBS += $$_PRO_FILE_PWD_\libs\FreeImage\FreeImage.lib
INCLUDEPATH += $$_PRO_FILE_PWD_\libs\FreeImage
INCLUDEPATH += srcs

LIBS += -lopengl32 -lglu32

#QMAKE_CXXFLAGS+= -fopenmp
#QMAKE_LFLAGS +=  -fopenmp

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pathtracing
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

SOURCES += \
        srcs/BSDF.cpp \
        srcs/Benchmark.cpp \
        srcs/Camera.cpp \
        srcs/CastRay.cpp \
        srcs/CollisionTree.cpp \
        srcs/Engine.cpp \
        srcs/FileImport.cpp \
        srcs/GLWidgetOpenGL.cpp \
        srcs/GLWidgetPathtracing.cpp \
        srcs/Material.cpp \
        srcs/Obj3d.cpp \
        srcs/ObjectsWindow.cpp \
        srcs/Pathtracing.cpp \
        srcs/Scene.cpp \
        srcs/SettingsWindow.cpp \
        srcs/Vector.cpp \
        srcs/main.cpp \
        srcs/MainWindow.cpp

HEADERS += \
        srcs/BSDF.h \
        srcs/Benchmark.h \
        srcs/Camera.h \
        srcs/CastRay.h \
        srcs/CollisionTree.h \
        srcs/Engine.h \
        srcs/FileImport.h \
        srcs/GLWidgetOpenGL.h \
        srcs/GLWidgetPathtracing.h \
        srcs/MainWindow.h \
        srcs/Material.h \
        srcs/Obj3d.h \
        srcs/ObjectsWindow.h \
        srcs/Pathtracing.h \
        srcs/Rand.h \
        srcs/Ray.h \
        srcs/Scene.h \
        srcs/SettingsWindow.h \
        srcs/Vector.h

FORMS += \
        forms/mainwindow.ui \
        forms/objectswindow.ui \
        forms/settingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
