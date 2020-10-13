#ifndef OBJECTSWINDOW_H
#define OBJECTSWINDOW_H

#include <QScrollBar>
#include <QLineEdit>
#include <QColorDialog>
#include <iostream>
#include "Scene.h"

namespace Ui {
class ObjectsWindow;
}

class ObjectsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectsWindow(Scene *scene, QWidget *parent = nullptr);
    ~ObjectsWindow();

public:
    void displayObjectsList();

private:
    void hideUI();
    void updateSurface();

private slots:
    void on_objects_listWidget_itemSelectionChanged();
    void on_materials_listWidget_itemSelectionChanged();
    void on_surface_comboBox_currentIndexChanged(const QString &currentText);
    void on_color_pushButton_clicked();
    void on_emission_doubleSpinBox_valueChanged(double value);
    void on_roughness_doubleSpinBox_valueChanged(double value);
    void on_ior_doubleSpinBox_valueChanged(double value);

private:
    Ui::ObjectsWindow *_ui;

    Scene *_scene;
    Obj3d *_currentObj;
    Material *_currentMaterial;
    bool _setSurfaceDefault;
};

#endif // OBJECTSWINDOW_H
