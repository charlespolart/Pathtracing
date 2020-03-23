/********************************************************************************
** Form generated from reading UI file 'objectswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTSWINDOW_H
#define UI_OBJECTSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectsWindow
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QListWidget *objects_listWidget;

    void setupUi(QWidget *ObjectsWindow)
    {
        if (ObjectsWindow->objectName().isEmpty())
            ObjectsWindow->setObjectName(QString::fromUtf8("ObjectsWindow"));
        ObjectsWindow->resize(378, 613);
        gridLayout = new QGridLayout(ObjectsWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        objects_listWidget = new QListWidget(ObjectsWindow);
        objects_listWidget->setObjectName(QString::fromUtf8("objects_listWidget"));

        gridLayout->addWidget(objects_listWidget, 0, 0, 1, 1);


        retranslateUi(ObjectsWindow);

        QMetaObject::connectSlotsByName(ObjectsWindow);
    } // setupUi

    void retranslateUi(QWidget *ObjectsWindow)
    {
        ObjectsWindow->setWindowTitle(QApplication::translate("ObjectsWindow", "Objects", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ObjectsWindow: public Ui_ObjectsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTSWINDOW_H
