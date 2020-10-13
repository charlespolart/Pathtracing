#include "ui_objectswindow.h"
#include "ObjectsWindow.h"

ObjectsWindow::ObjectsWindow(Scene *scene, QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ObjectsWindow),
    _scene(scene),
    _currentObj(nullptr),
    _setSurfaceDefault(true)
{
    this->_ui->setupUi(this);
    this->hideUI();
}

ObjectsWindow::~ObjectsWindow()
{
    delete this->_ui;
}

void ObjectsWindow::hideUI()
{
    this->_ui->surface_groupBox->setVisible(false);
    this->_ui->roughness_label->setVisible(false);
    this->_ui->roughness_doubleSpinBox->setVisible(false);
    this->_ui->ior_label->setVisible(false);
    this->_ui->ior_doubleSpinBox->setVisible(false);
    this->_ui->scrollAreaWidgetContents->setVisible(false);
    this->_ui->scrollArea->verticalScrollBar()->hide();
}

void ObjectsWindow::displayObjectsList()
{
    this->_currentObj = nullptr;

    this->_ui->objects_listWidget->clear();
    this->hideUI();
    for (size_t i = 0; i < this->_scene->_mesh.objs.size(); ++i)
        this->_ui->objects_listWidget->addItem(QString::fromStdString(this->_scene->_mesh.objs[i]->_name));
}

void ObjectsWindow::updateSurface()
{
    this->_ui->roughness_label->setVisible(false);
    this->_ui->roughness_doubleSpinBox->setVisible(false);
    this->_ui->ior_label->setVisible(false);
    this->_ui->ior_doubleSpinBox->setVisible(false);
    if (_currentMaterial->_surface == DIFFUSE)
    {
        this->_ui->surface_comboBox->setCurrentIndex(this->_ui->surface_comboBox->findText("Diffuse"));
    }
    else if (this->_currentMaterial->_surface == REFLECTION)
    {
        this->_ui->surface_comboBox->setCurrentIndex(this->_ui->surface_comboBox->findText("Reflection"));
        this->_ui->roughness_label->setVisible(true);
        this->_ui->roughness_doubleSpinBox->setVisible(true);
    }
    else if (this->_currentMaterial->_surface == TRANSMISSION)
    {
        this->_ui->surface_comboBox->setCurrentIndex(this->_ui->surface_comboBox->findText("Transmission"));
        this->_ui->roughness_label->setVisible(true);
        this->_ui->roughness_doubleSpinBox->setVisible(true);
        this->_ui->ior_label->setVisible(true);
        this->_ui->ior_doubleSpinBox->setVisible(true);
    }
    this->_ui->color_pushButton->setStyleSheet("background-color: rgb("+
                                              QString::number(this->_currentMaterial->_color.x*255.0)+","+
                                              QString::number(this->_currentMaterial->_color.y*255.0)+","+
                                              QString::number(this->_currentMaterial->_color.z*255.0)+")");
    this->_ui->emission_doubleSpinBox->setValue(this->_currentMaterial->_emission);
    this->_ui->roughness_doubleSpinBox->setValue(this->_currentMaterial->_roughness);
    this->_ui->ior_doubleSpinBox->setValue(this->_currentMaterial->_ior);
}

void ObjectsWindow::on_objects_listWidget_itemSelectionChanged()
{
    this->_ui->materials_listWidget->clear();
    for (size_t i = 0; i < this->_scene->_mesh.objs.size(); ++i)
    {
        if (this->_scene->_mesh.objs[i]->_name == this->_ui->objects_listWidget->currentItem()->text().toStdString())
        {
            this->_currentObj = this->_scene->_mesh.objs[i];
            break;
        }
    }
    if (!this->_currentObj)
        return;
    for (size_t i = 0; i < this->_currentObj->_materials.size(); ++i)
        this->_ui->materials_listWidget->addItem(QString::fromStdString(this->_currentObj->_materials[i]->_name));
    if (this->_currentObj->_materials.size())
    {
        this->_ui->scrollAreaWidgetContents->setVisible(true);
        this->_ui->scrollArea->verticalScrollBar()->show();
        this->_ui->materials_listWidget->setCurrentRow(0);
    }
    else
    {
        this->_ui->scrollAreaWidgetContents->setVisible(false);
        this->_ui->scrollArea->verticalScrollBar()->hide();
    }
}

void ObjectsWindow::on_materials_listWidget_itemSelectionChanged()
{
    this->_currentMaterial = this->_scene->_mesh.materials[this->_ui->materials_listWidget->currentItem()->text().toStdString()];
    if (!this->_currentMaterial)
        return;
    this->_ui->surface_groupBox->setVisible(true);
    this->_setSurfaceDefault = false;
    this->updateSurface();
    this->_setSurfaceDefault = true;
}

void ObjectsWindow::on_surface_comboBox_currentIndexChanged(const QString &currentText)
{
    if (this->_setSurfaceDefault)
    {
        this->_currentMaterial->_roughness = 0.0;
        this->_currentMaterial->_ior = 1.0;
        this->_currentMaterial->_emission = 0.0;
    }
    if (currentText == "Diffuse")
        this->_currentMaterial->_surface = DIFFUSE;
    else if (currentText == "Reflection")
        this->_currentMaterial->_surface = REFLECTION;
    else if (currentText == "Transmission")
        this->_currentMaterial->_surface = TRANSMISSION;
    this->updateSurface();
}

void ObjectsWindow::on_color_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(QColor(static_cast<int>(this->_currentMaterial->_color.x*255.0),
                                                 static_cast<int>(this->_currentMaterial->_color.y*255.0),
                                                 static_cast<int>(this->_currentMaterial->_color.z*255.0)));

    if (!color.isValid())
        return;
    this->_currentMaterial->_color = Vector3d(color.red()/255.0, color.green()/255.0, color.blue()/255.0);
    this->_ui->color_pushButton->setStyleSheet("background-color: rgb("+
                                              QString::number(this->_currentMaterial->_color.x*255.0)+","+
                                              QString::number(this->_currentMaterial->_color.y*255.0)+","+
                                              QString::number(this->_currentMaterial->_color.z*255.0)+")");
}

void ObjectsWindow::on_emission_doubleSpinBox_valueChanged(double value)
{
    this->_currentMaterial->_emission = value;
}

void ObjectsWindow::on_roughness_doubleSpinBox_valueChanged(double value)
{
    this->_currentMaterial->_roughness = value;
}

void ObjectsWindow::on_ior_doubleSpinBox_valueChanged(double value)
{
    this->_currentMaterial->_ior = value;
}
