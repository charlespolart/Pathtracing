#ifndef OBJECTSWINDOW_H
#define OBJECTSWINDOW_H

#include <QScrollBar>
#include <QLineEdit>
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
    std::string uniqueMaterialName(const std::string &name, int nb = 0);

private slots:
    void on_objects_listWidget_currentTextChanged(const QString &currentText);
    void on_materials_comboBox_currentIndexChanged(const QString &currentText);
    void materials_comboBox_editingFinished();
    void on_newMaterial_pushButton_clicked();
    void on_deleteMaterial_pushButton_clicked();
    void on_emission_doubleSpinBox_valueChanged(double value);

private:
    Ui::ObjectsWindow *ui;

    Scene *scene;
    Obj3d *currentObj;
};

#endif // OBJECTSWINDOW_H
