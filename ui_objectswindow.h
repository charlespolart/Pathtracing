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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectsWindow
{
public:
    QGridLayout *gridLayout_6;
    QSplitter *splitter;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QListWidget *objects_listWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QOpenGLWidget *openGLWidget;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QPushButton *newMaterial_pushButton;
    QWidget *widget_3;
    QGridLayout *gridLayout_7;
    QComboBox *materials_comboBox;
    QPushButton *deleteMaterial_pushButton;
    QGroupBox *surface_groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QPushButton *color_pushButton;
    QLabel *label_2;
    QDoubleSpinBox *emission_doubleSpinBox;

    void setupUi(QWidget *ObjectsWindow)
    {
        if (ObjectsWindow->objectName().isEmpty())
            ObjectsWindow->setObjectName(QString::fromUtf8("ObjectsWindow"));
        ObjectsWindow->resize(364, 936);
        gridLayout_6 = new QGridLayout(ObjectsWindow);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(ObjectsWindow);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setStyleSheet(QString::fromUtf8("QSplitter::handle {\n"
"	background-color: qlineargradient(spread:reflect, x1:1, y1:0.5, x2:1, y2:1, stop:0 rgba(50, 50, 50, 255), stop:1 rgba(255, 255, 255, 255));\n"
"}"));
        splitter->setOrientation(Qt::Vertical);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        objects_listWidget = new QListWidget(widget_2);
        objects_listWidget->setObjectName(QString::fromUtf8("objects_listWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(objects_listWidget->sizePolicy().hasHeightForWidth());
        objects_listWidget->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(objects_listWidget, 0, 0, 1, 1);

        splitter->addWidget(widget_2);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 364, 738));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy2);
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(scrollAreaWidgetContents);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFlat(true);
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(11, 11, 11, -1);
        openGLWidget = new QOpenGLWidget(groupBox_3);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        sizePolicy2.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy2);
        openGLWidget->setMinimumSize(QSize(200, 150));

        gridLayout_4->addWidget(openGLWidget, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_3, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setSizeIncrement(QSize(0, 300));
        groupBox->setFlat(true);
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        newMaterial_pushButton = new QPushButton(groupBox);
        newMaterial_pushButton->setObjectName(QString::fromUtf8("newMaterial_pushButton"));

        gridLayout_5->addWidget(newMaterial_pushButton, 1, 0, 1, 1);

        widget_3 = new QWidget(groupBox);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_7 = new QGridLayout(widget_3);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        materials_comboBox = new QComboBox(widget_3);
        materials_comboBox->setObjectName(QString::fromUtf8("materials_comboBox"));
        materials_comboBox->setMaximumSize(QSize(16777215, 16777215));
        materials_comboBox->setLayoutDirection(Qt::LeftToRight);
        materials_comboBox->setStyleSheet(QString::fromUtf8(""));
        materials_comboBox->setEditable(true);
        materials_comboBox->setInsertPolicy(QComboBox::InsertAtCurrent);
        materials_comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        gridLayout_7->addWidget(materials_comboBox, 0, 0, 1, 1);

        deleteMaterial_pushButton = new QPushButton(widget_3);
        deleteMaterial_pushButton->setObjectName(QString::fromUtf8("deleteMaterial_pushButton"));
        deleteMaterial_pushButton->setMaximumSize(QSize(22, 22));

        gridLayout_7->addWidget(deleteMaterial_pushButton, 0, 1, 1, 1);


        gridLayout_5->addWidget(widget_3, 0, 0, 1, 1);

        surface_groupBox = new QGroupBox(groupBox);
        surface_groupBox->setObjectName(QString::fromUtf8("surface_groupBox"));
        formLayout = new QFormLayout(surface_groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(surface_groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        color_pushButton = new QPushButton(surface_groupBox);
        color_pushButton->setObjectName(QString::fromUtf8("color_pushButton"));

        formLayout->setWidget(1, QFormLayout::FieldRole, color_pushButton);

        label_2 = new QLabel(surface_groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        emission_doubleSpinBox = new QDoubleSpinBox(surface_groupBox);
        emission_doubleSpinBox->setObjectName(QString::fromUtf8("emission_doubleSpinBox"));
        emission_doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        emission_doubleSpinBox->setMaximum(2.000000000000000);
        emission_doubleSpinBox->setSingleStep(0.100000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, emission_doubleSpinBox);


        gridLayout_5->addWidget(surface_groupBox, 2, 0, 1, 1);


        gridLayout->addWidget(groupBox, 2, 0, 1, 1);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrollArea);

        gridLayout_6->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(ObjectsWindow);

        QMetaObject::connectSlotsByName(ObjectsWindow);
    } // setupUi

    void retranslateUi(QWidget *ObjectsWindow)
    {
        ObjectsWindow->setWindowTitle(QApplication::translate("ObjectsWindow", "Objects", nullptr));
        groupBox_3->setTitle(QApplication::translate("ObjectsWindow", "Preview", nullptr));
        groupBox->setTitle(QApplication::translate("ObjectsWindow", "Material", nullptr));
        newMaterial_pushButton->setText(QApplication::translate("ObjectsWindow", "New", nullptr));
        deleteMaterial_pushButton->setText(QApplication::translate("ObjectsWindow", "X", nullptr));
        surface_groupBox->setTitle(QApplication::translate("ObjectsWindow", "Surface", nullptr));
        label->setText(QApplication::translate("ObjectsWindow", "Color", nullptr));
        color_pushButton->setText(QString());
        label_2->setText(QApplication::translate("ObjectsWindow", "Emission", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ObjectsWindow: public Ui_ObjectsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTSWINDOW_H
