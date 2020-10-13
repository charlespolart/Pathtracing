#include "SettingsWindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(Scene *scene, QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::SettingsWindow),
    _scene(scene)
{
    _ui->setupUi(this);
    this->updateValues();
}

SettingsWindow::~SettingsWindow()
{
    delete this->_ui;
}

void SettingsWindow::updateValues()
{
    this->_ui->width_spinBox->setValue(this->_scene->_camera->_width);
    this->on_width_spinBox_editingFinished();
    this->_ui->height_spinBox->setValue(this->_scene->_camera->_height);
    this->on_height_spinBox_editingFinished();
    this->_ui->cameraPositionX_doubleSpinBox->setValue(this->_scene->_camera->_position.x);
    this->_ui->cameraPositionY_doubleSpinBox->setValue(this->_scene->_camera->_position.y);
    this->_ui->cameraPositionZ_doubleSpinBox->setValue(this->_scene->_camera->_position.z);
    this->_ui->cameraRotationX_doubleSpinBox->setValue(this->_scene->_camera->_rotation.x);
    this->_ui->cameraRotationY_doubleSpinBox->setValue(this->_scene->_camera->_rotation.y);
    this->_ui->cameraRotationZ_doubleSpinBox->setValue(this->_scene->_camera->_rotation.z);
    this->_ui->maxSamples_spinBox->setValue(this->_scene->_samples);
    this->_ui->maxDepth_spinBox->setValue(this->_scene->_maxDepth);
}

void SettingsWindow::on_width_spinBox_editingFinished()
{
    int width = (this->_ui->width_spinBox->value()/4)*4;

    this->_ui->width_spinBox->setValue(width);
    this->_scene->_camera->setWidth(width);
}

void SettingsWindow::on_height_spinBox_editingFinished()
{
    int height = (this->_ui->height_spinBox->value()/4)*4;

    this->_ui->height_spinBox->setValue(height);
    this->_scene->_camera->setHeight(height);
}

void SettingsWindow::on_cameraPositionX_doubleSpinBox_valueChanged(double value)
{
    this->_scene->_camera->_position.x = value;
}

void SettingsWindow::on_cameraPositionY_doubleSpinBox_valueChanged(double value)
{
    this->_scene->_camera->_position.y = value;
}

void SettingsWindow::on_cameraPositionZ_doubleSpinBox_valueChanged(double value)
{
    this->_scene->_camera->_position.z = value;
}

void SettingsWindow::on_cameraRotationX_doubleSpinBox_valueChanged(double value)
{
    while (value >= 360.0)
        value -= 360.0;
    while (value <= -360.0)
        value += 360.0;
    this->_ui->cameraRotationX_doubleSpinBox->setValue(value);
    this->_scene->_camera->_rotation.x = value;
}

void SettingsWindow::on_cameraRotationY_doubleSpinBox_valueChanged(double value)
{
    while (value >= 360.0)
        value -= 360.0;
    while (value <= -360.0)
        value += 360.0;
    this->_ui->cameraRotationY_doubleSpinBox->setValue(value);
    this->_scene->_camera->_rotation.y = value;
}

void SettingsWindow::on_cameraRotationZ_doubleSpinBox_valueChanged(double value)
{
    while (value >= 360.0)
        value -= 360.0;
    while (value <= -360.0)
        value += 360.0;
    this->_ui->cameraRotationZ_doubleSpinBox->setValue(value);
    this->_scene->_camera->_rotation.z = value;
}

void SettingsWindow::on_maxSamples_spinBox_valueChanged(int value)
{
    this->_scene->_samples = value;

}

void SettingsWindow::on_maxDepth_spinBox_valueChanged(int value)
{
    this->_scene->_maxDepth = value;
}
