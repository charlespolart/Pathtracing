/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include "GLWidgetOpenGL.h"
#include "GLWidgetPathtracing.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionImport_obj;
    QAction *actionSave_scene;
    QAction *actionLoad_scene;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QWidget *settings_gridWidget;
    QGridLayout *gridLayout_4;
    QWidget *gridWidget;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *render_pushButton;
    QPushButton *stop_pushButton;
    QSplitter *splitter;
    QWidget *gridWidget1;
    QGridLayout *gridLayout_2;
    GLWidgetOpenGL *openGL_GLWidget;
    GLWidgetPathtracing *pathtracing_GLWidget;
    QListWidget *terminal_listWidget;
    QWidget *objects_gridWidget;
    QGridLayout *gridLayout_6;
    QMenuBar *menuBar;
    QMenu *menuWindows;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1142, 735);
        actionImport_obj = new QAction(MainWindow);
        actionImport_obj->setObjectName(QString::fromUtf8("actionImport_obj"));
        actionSave_scene = new QAction(MainWindow);
        actionSave_scene->setObjectName(QString::fromUtf8("actionSave_scene"));
        actionLoad_scene = new QAction(MainWindow);
        actionLoad_scene->setObjectName(QString::fromUtf8("actionLoad_scene"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setStyleSheet(QString::fromUtf8("QSplitter::handle {\n"
"	background-color: qlineargradient(spread:reflect, x1:0.5, y1:1, x2:1, y2:1, stop:0 rgba(50, 50, 50, 255), stop:1 rgba(255, 255, 255, 255));\n"
"}"));
        splitter_2->setFrameShape(QFrame::NoFrame);
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setOpaqueResize(true);
        splitter_2->setHandleWidth(5);
        splitter_2->setChildrenCollapsible(true);
        settings_gridWidget = new QWidget(splitter_2);
        settings_gridWidget->setObjectName(QString::fromUtf8("settings_gridWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settings_gridWidget->sizePolicy().hasHeightForWidth());
        settings_gridWidget->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(settings_gridWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        splitter_2->addWidget(settings_gridWidget);
        gridWidget = new QWidget(splitter_2);
        gridWidget->setObjectName(QString::fromUtf8("gridWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gridWidget->sizePolicy().hasHeightForWidth());
        gridWidget->setSizePolicy(sizePolicy1);
        gridLayout_3 = new QGridLayout(gridWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(6);
        gridLayout_3->setContentsMargins(0, 0, 0, 9);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        render_pushButton = new QPushButton(gridWidget);
        render_pushButton->setObjectName(QString::fromUtf8("render_pushButton"));
        render_pushButton->setEnabled(false);

        horizontalLayout->addWidget(render_pushButton);

        stop_pushButton = new QPushButton(gridWidget);
        stop_pushButton->setObjectName(QString::fromUtf8("stop_pushButton"));
        stop_pushButton->setEnabled(false);

        horizontalLayout->addWidget(stop_pushButton);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);

        splitter = new QSplitter(gridWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy2);
        splitter->setStyleSheet(QString::fromUtf8("QSplitter::handle {\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:0.5, x2:1, y2:1, stop:0 rgba(50, 50, 50, 255), stop:1 rgba(255, 255, 255, 255));\n"
"}"));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setOrientation(Qt::Vertical);
        gridWidget1 = new QWidget(splitter);
        gridWidget1->setObjectName(QString::fromUtf8("gridWidget1"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(gridWidget1->sizePolicy().hasHeightForWidth());
        gridWidget1->setSizePolicy(sizePolicy3);
        gridLayout_2 = new QGridLayout(gridWidget1);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(1);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        openGL_GLWidget = new GLWidgetOpenGL(gridWidget1);
        openGL_GLWidget->setObjectName(QString::fromUtf8("openGL_GLWidget"));
        sizePolicy.setHeightForWidth(openGL_GLWidget->sizePolicy().hasHeightForWidth());
        openGL_GLWidget->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(openGL_GLWidget, 0, 0, 1, 1);

        pathtracing_GLWidget = new GLWidgetPathtracing(gridWidget1);
        pathtracing_GLWidget->setObjectName(QString::fromUtf8("pathtracing_GLWidget"));
        sizePolicy.setHeightForWidth(pathtracing_GLWidget->sizePolicy().hasHeightForWidth());
        pathtracing_GLWidget->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pathtracing_GLWidget, 0, 1, 1, 1);

        splitter->addWidget(gridWidget1);
        terminal_listWidget = new QListWidget(splitter);
        terminal_listWidget->setObjectName(QString::fromUtf8("terminal_listWidget"));
        sizePolicy.setHeightForWidth(terminal_listWidget->sizePolicy().hasHeightForWidth());
        terminal_listWidget->setSizePolicy(sizePolicy);
        terminal_listWidget->setMinimumSize(QSize(0, 0));
        splitter->addWidget(terminal_listWidget);

        gridLayout_3->addWidget(splitter, 1, 0, 1, 1);

        splitter_2->addWidget(gridWidget);
        objects_gridWidget = new QWidget(splitter_2);
        objects_gridWidget->setObjectName(QString::fromUtf8("objects_gridWidget"));
        sizePolicy.setHeightForWidth(objects_gridWidget->sizePolicy().hasHeightForWidth());
        objects_gridWidget->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(objects_gridWidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        splitter_2->addWidget(objects_gridWidget);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1142, 26));
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QString::fromUtf8("menuWindows"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuWindows->menuAction());
        menuWindows->addAction(actionLoad_scene);
        menuWindows->addAction(actionSave_scene);
        menuWindows->addSeparator();
        menuWindows->addAction(actionImport_obj);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Pathtracing", nullptr));
        actionImport_obj->setText(QApplication::translate("MainWindow", "Import .obj", nullptr));
        actionSave_scene->setText(QApplication::translate("MainWindow", "Save scene", nullptr));
        actionLoad_scene->setText(QApplication::translate("MainWindow", "Load scene", nullptr));
        render_pushButton->setText(QApplication::translate("MainWindow", "Render", nullptr));
        stop_pushButton->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        menuWindows->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
