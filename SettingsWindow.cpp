#include "SettingsWindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(Scene *scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow),
    scene(scene)
{
    ui->setupUi(this);
    this->ui->width_spinBox->setValue(this->scene->camera->width);
    this->ui->height_spinBox->setValue(this->scene->camera->height);
    this->ui->cameraPositionX_doubleSpinBox->setValue(this->scene->camera->position.x);
    this->ui->cameraPositionY_doubleSpinBox->setValue(this->scene->camera->position.y);
    this->ui->cameraPositionZ_doubleSpinBox->setValue(this->scene->camera->position.z);
    this->ui->cameraRotationX_doubleSpinBox->setValue(this->scene->camera->rotation.x);
    this->ui->cameraRotationY_doubleSpinBox->setValue(this->scene->camera->rotation.y);
    this->ui->cameraRotationZ_doubleSpinBox->setValue(this->scene->camera->rotation.z);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_width_spinBox_editingFinished()
{
    int width = (this->ui->width_spinBox->value()/4)*4;

    this->ui->width_spinBox->setValue(width);
    this->scene->camera->setWidth(width);
}

void SettingsWindow::on_height_spinBox_editingFinished()
{
    int height = (this->ui->height_spinBox->value()/4)*4;

    this->ui->height_spinBox->setValue(height);
    this->scene->camera->setHeight(height);
}

void SettingsWindow::on_cameraPositionX_doubleSpinBox_valueChanged(double value)
{
    this->scene->camera->position.x = value;
}

void SettingsWindow::on_cameraPositionY_doubleSpinBox_valueChanged(double value)
{
    this->scene->camera->position.y = value;
}

void SettingsWindow::on_cameraPositionZ_doubleSpinBox_valueChanged(double value)
{
    this->scene->camera->position.z = value;
}

void SettingsWindow::on_cameraRotationX_doubleSpinBox_valueChanged(double value)
{
    while (value >= 360.0)
        value -= 360.0;
    while (value <= -360.0)
        value += 360.0;
    this->ui->cameraRotationX_doubleSpinBox->setValue(value);
    this->scene->camera->rotation.x = value;
}

void SettingsWindow::on_cameraRotationY_doubleSpinBox_valueChanged(double value)
{
    while (value >= 360.0)
        value -= 360.0;
    while (value <= -360.0)
        value += 360.0;
    this->ui->cameraRotationY_doubleSpinBox->setValue(value);
    this->scene->camera->rotation.y = value;
}

void SettingsWindow::on_cameraRotationZ_doubleSpinBox_valueChanged(double value)
{
    while (value >= 360.0)
        value -= 360.0;
    while (value <= -360.0)
        value += 360.0;
    this->ui->cameraRotationZ_doubleSpinBox->setValue(value);
    this->scene->camera->rotation.z = value;
}
