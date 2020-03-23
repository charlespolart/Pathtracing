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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include "GLWidgetOpenGL.h"
#include "GLWidgetPathtracing.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSettings;
    QAction *actionObjects;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *render_pushButton;
    QPushButton *stop_pushButton;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *load3DFile_pushButton;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter;
    QWidget *gridWidget;
    QGridLayout *gridLayout_2;
    GLWidgetPathtracing *pathtracing_GLWidget;
    GLWidgetOpenGL *openGL_GLWidget;
    QListWidget *terminal_listWidget;
    QMenuBar *menuBar;
    QMenu *menuWindows;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1142, 735);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionObjects = new QAction(MainWindow);
        actionObjects->setObjectName(QString::fromUtf8("actionObjects"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        render_pushButton = new QPushButton(centralWidget);
        render_pushButton->setObjectName(QString::fromUtf8("render_pushButton"));
        render_pushButton->setEnabled(false);

        horizontalLayout->addWidget(render_pushButton);

        stop_pushButton = new QPushButton(centralWidget);
        stop_pushButton->setObjectName(QString::fromUtf8("stop_pushButton"));
        stop_pushButton->setEnabled(false);

        horizontalLayout->addWidget(stop_pushButton);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        load3DFile_pushButton = new QPushButton(centralWidget);
        load3DFile_pushButton->setObjectName(QString::fromUtf8("load3DFile_pushButton"));

        horizontalLayout_2->addWidget(load3DFile_pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Vertical);
        gridWidget = new QWidget(splitter);
        gridWidget->setObjectName(QString::fromUtf8("gridWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(gridWidget->sizePolicy().hasHeightForWidth());
        gridWidget->setSizePolicy(sizePolicy1);
        gridLayout_2 = new QGridLayout(gridWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pathtracing_GLWidget = new GLWidgetPathtracing(gridWidget);
        pathtracing_GLWidget->setObjectName(QString::fromUtf8("pathtracing_GLWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pathtracing_GLWidget->sizePolicy().hasHeightForWidth());
        pathtracing_GLWidget->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(pathtracing_GLWidget, 0, 1, 1, 1);

        openGL_GLWidget = new GLWidgetOpenGL(gridWidget);
        openGL_GLWidget->setObjectName(QString::fromUtf8("openGL_GLWidget"));
        sizePolicy2.setHeightForWidth(openGL_GLWidget->sizePolicy().hasHeightForWidth());
        openGL_GLWidget->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(openGL_GLWidget, 0, 0, 1, 1);

        splitter->addWidget(gridWidget);
        terminal_listWidget = new QListWidget(splitter);
        terminal_listWidget->setObjectName(QString::fromUtf8("terminal_listWidget"));
        sizePolicy2.setHeightForWidth(terminal_listWidget->sizePolicy().hasHeightForWidth());
        terminal_listWidget->setSizePolicy(sizePolicy2);
        terminal_listWidget->setMinimumSize(QSize(0, 0));
        splitter->addWidget(terminal_listWidget);

        gridLayout->addWidget(splitter, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1142, 26));
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QString::fromUtf8("menuWindows"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuWindows->menuAction());
        menuWindows->addAction(actionSettings);
        menuWindows->addAction(actionObjects);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Pathtracing", nullptr));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", nullptr));
        actionObjects->setText(QApplication::translate("MainWindow", "Objects", nullptr));
        render_pushButton->setText(QApplication::translate("MainWindow", "Render", nullptr));
        stop_pushButton->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        load3DFile_pushButton->setText(QApplication::translate("MainWindow", "Load 3D file", nullptr));
        menuWindows->setTitle(QApplication::translate("MainWindow", "Windows", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
