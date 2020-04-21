/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *width_spinBox;
    QSpinBox *height_spinBox;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QDoubleSpinBox *cameraPositionX_doubleSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *cameraPositionY_doubleSpinBox;
    QLabel *label_3;
    QDoubleSpinBox *cameraPositionZ_doubleSpinBox;
    QGroupBox *groupBox_3;
    QFormLayout *formLayout_3;
    QLabel *label_8;
    QDoubleSpinBox *cameraRotationX_doubleSpinBox;
    QLabel *label_6;
    QDoubleSpinBox *cameraRotationY_doubleSpinBox;
    QLabel *label_7;
    QDoubleSpinBox *cameraRotationZ_doubleSpinBox;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout_4;
    QLabel *label_9;
    QSpinBox *maxSamples_spinBox;
    QSpinBox *maxDepth_spinBox;
    QLabel *label_10;

    void setupUi(QWidget *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QString::fromUtf8("SettingsWindow"));
        SettingsWindow->resize(456, 703);
        gridLayout = new QGridLayout(SettingsWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_5 = new QGroupBox(SettingsWindow);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setFlat(true);
        verticalLayout = new QVBoxLayout(groupBox_5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(9, -1, 9, -1);
        groupBox = new QGroupBox(groupBox_5);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        width_spinBox = new QSpinBox(groupBox);
        width_spinBox->setObjectName(QString::fromUtf8("width_spinBox"));
        width_spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        width_spinBox->setMaximum(9999);

        formLayout->setWidget(0, QFormLayout::FieldRole, width_spinBox);

        height_spinBox = new QSpinBox(groupBox);
        height_spinBox->setObjectName(QString::fromUtf8("height_spinBox"));
        height_spinBox->setLayoutDirection(Qt::LeftToRight);
        height_spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        height_spinBox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        height_spinBox->setMaximum(9999);

        formLayout->setWidget(1, QFormLayout::FieldRole, height_spinBox);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox_2 = new QGroupBox(groupBox_5);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        cameraPositionX_doubleSpinBox = new QDoubleSpinBox(groupBox_2);
        cameraPositionX_doubleSpinBox->setObjectName(QString::fromUtf8("cameraPositionX_doubleSpinBox"));
        cameraPositionX_doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cameraPositionX_doubleSpinBox->setDecimals(5);
        cameraPositionX_doubleSpinBox->setMinimum(-99999999.000000000000000);
        cameraPositionX_doubleSpinBox->setMaximum(99999999.000000000000000);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cameraPositionX_doubleSpinBox);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        cameraPositionY_doubleSpinBox = new QDoubleSpinBox(groupBox_2);
        cameraPositionY_doubleSpinBox->setObjectName(QString::fromUtf8("cameraPositionY_doubleSpinBox"));
        cameraPositionY_doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cameraPositionY_doubleSpinBox->setDecimals(5);
        cameraPositionY_doubleSpinBox->setMinimum(-99999999.000000000000000);
        cameraPositionY_doubleSpinBox->setMaximum(99999999.000000000000000);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cameraPositionY_doubleSpinBox);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        cameraPositionZ_doubleSpinBox = new QDoubleSpinBox(groupBox_2);
        cameraPositionZ_doubleSpinBox->setObjectName(QString::fromUtf8("cameraPositionZ_doubleSpinBox"));
        cameraPositionZ_doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cameraPositionZ_doubleSpinBox->setDecimals(5);
        cameraPositionZ_doubleSpinBox->setMinimum(-99999999.000000000000000);
        cameraPositionZ_doubleSpinBox->setMaximum(99999999.000000000000000);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, cameraPositionZ_doubleSpinBox);


        horizontalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox_5);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        formLayout_3 = new QFormLayout(groupBox_3);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_8);

        cameraRotationX_doubleSpinBox = new QDoubleSpinBox(groupBox_3);
        cameraRotationX_doubleSpinBox->setObjectName(QString::fromUtf8("cameraRotationX_doubleSpinBox"));
        cameraRotationX_doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cameraRotationX_doubleSpinBox->setDecimals(5);
        cameraRotationX_doubleSpinBox->setMinimum(-99999999.000000000000000);
        cameraRotationX_doubleSpinBox->setMaximum(99999999.000000000000000);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, cameraRotationX_doubleSpinBox);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_6);

        cameraRotationY_doubleSpinBox = new QDoubleSpinBox(groupBox_3);
        cameraRotationY_doubleSpinBox->setObjectName(QString::fromUtf8("cameraRotationY_doubleSpinBox"));
        cameraRotationY_doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cameraRotationY_doubleSpinBox->setDecimals(5);
        cameraRotationY_doubleSpinBox->setMinimum(-99999999.000000000000000);
        cameraRotationY_doubleSpinBox->setMaximum(99999999.000000000000000);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, cameraRotationY_doubleSpinBox);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, label_7);

        cameraRotationZ_doubleSpinBox = new QDoubleSpinBox(groupBox_3);
        cameraRotationZ_doubleSpinBox->setObjectName(QString::fromUtf8("cameraRotationZ_doubleSpinBox"));
        cameraRotationZ_doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cameraRotationZ_doubleSpinBox->setDecimals(5);
        cameraRotationZ_doubleSpinBox->setMinimum(-99999999.000000000000000);
        cameraRotationZ_doubleSpinBox->setMaximum(99999999.000000000000000);

        formLayout_3->setWidget(5, QFormLayout::FieldRole, cameraRotationZ_doubleSpinBox);


        horizontalLayout_2->addWidget(groupBox_3);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addWidget(groupBox_5, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        groupBox_6 = new QGroupBox(SettingsWindow);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setFlat(true);
        verticalLayout_2 = new QVBoxLayout(groupBox_6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, -1, 9, -1);
        groupBox_4 = new QGroupBox(groupBox_6);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        formLayout_4 = new QFormLayout(groupBox_4);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_9);

        maxSamples_spinBox = new QSpinBox(groupBox_4);
        maxSamples_spinBox->setObjectName(QString::fromUtf8("maxSamples_spinBox"));
        maxSamples_spinBox->setLayoutDirection(Qt::LeftToRight);
        maxSamples_spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, maxSamples_spinBox);

        maxDepth_spinBox = new QSpinBox(groupBox_4);
        maxDepth_spinBox->setObjectName(QString::fromUtf8("maxDepth_spinBox"));
        maxDepth_spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, maxDepth_spinBox);

        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_10);


        verticalLayout_2->addWidget(groupBox_4);


        gridLayout->addWidget(groupBox_6, 1, 0, 1, 1);


        retranslateUi(SettingsWindow);

        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QWidget *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QApplication::translate("SettingsWindow", "Settings", nullptr));
        groupBox_5->setTitle(QApplication::translate("SettingsWindow", "Camera", nullptr));
        groupBox->setTitle(QApplication::translate("SettingsWindow", "Resolution", nullptr));
        label->setText(QApplication::translate("SettingsWindow", "X", nullptr));
        label_2->setText(QApplication::translate("SettingsWindow", "Y", nullptr));
        width_spinBox->setPrefix(QString());
        groupBox_2->setTitle(QApplication::translate("SettingsWindow", "Position", nullptr));
        label_5->setText(QApplication::translate("SettingsWindow", "X", nullptr));
        label_4->setText(QApplication::translate("SettingsWindow", "Y", nullptr));
        label_3->setText(QApplication::translate("SettingsWindow", "Z", nullptr));
        groupBox_3->setTitle(QApplication::translate("SettingsWindow", "Rotation", nullptr));
        label_8->setText(QApplication::translate("SettingsWindow", "X", nullptr));
        label_6->setText(QApplication::translate("SettingsWindow", "Y", nullptr));
        label_7->setText(QApplication::translate("SettingsWindow", "Z", nullptr));
        groupBox_6->setTitle(QApplication::translate("SettingsWindow", "Pathtracing", nullptr));
        groupBox_4->setTitle(QApplication::translate("SettingsWindow", "Pixel", nullptr));
        label_9->setText(QApplication::translate("SettingsWindow", "Samples", nullptr));
        label_10->setText(QApplication::translate("SettingsWindow", "Depth", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
