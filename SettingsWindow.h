#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include "Scene.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(Scene *scene, QWidget *parent = nullptr);
    ~SettingsWindow();

private:
    Q_INVOKABLE void updateValues();

private slots:
    void on_width_spinBox_editingFinished();
    void on_height_spinBox_editingFinished();
    void on_cameraPositionX_doubleSpinBox_valueChanged(double value);
    void on_cameraPositionY_doubleSpinBox_valueChanged(double value);
    void on_cameraPositionZ_doubleSpinBox_valueChanged(double value);
    void on_cameraRotationX_doubleSpinBox_valueChanged(double value);
    void on_cameraRotationY_doubleSpinBox_valueChanged(double value);
    void on_cameraRotationZ_doubleSpinBox_valueChanged(double value);
    void on_maxSamples_spinBox_valueChanged(int value);
    void on_maxDepth_spinBox_valueChanged(int value);

private:
    Ui::SettingsWindow *ui;

    Scene *scene;
};

#endif // SETTINGSWINDOW_H
