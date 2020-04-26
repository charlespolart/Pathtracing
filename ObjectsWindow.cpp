#include "ObjectsWindow.h"
#include "ui_objectswindow.h"

ObjectsWindow::ObjectsWindow(Scene *scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWindow),
    scene(scene),
    currentObj(nullptr),
    setSurfaceDefault(false)
{
    this->ui->setupUi(this);
    this->displayObjectsList();
    this->ui->materials_comboBox->view()->setMinimumWidth(200);
    this->ui->materials_comboBox->view()->setMinimumHeight(200);
    this->ui->surface_groupBox->setVisible(false);
    this->ui->emission_widget->setVisible(false);
    this->ui->roughness_widget->setVisible(false);
    this->ui->ior_widget->setVisible(false);
    connect(this->ui->materials_comboBox->lineEdit(), SIGNAL(editingFinished()), SLOT(materials_comboBox_editingFinished()));
}

ObjectsWindow::~ObjectsWindow()
{
    delete ui;
}

void ObjectsWindow::updateMaterialList()
{
    this->currentObj = nullptr;
    this->ui->materials_comboBox->clear();
    for (size_t i = 0; i < this->scene->mesh.materials.size(); ++i)
        this->ui->materials_comboBox->addItem(QString::fromStdString(this->scene->mesh.materials[i]->name));
    this->ui->materials_comboBox->setCurrentIndex(-1);
}

void ObjectsWindow::displayObjectsList()
{
    this->currentObj = nullptr;

    this->ui->objects_listWidget->clear();
    for (size_t i = 0; i < this->scene->mesh.objs.size(); ++i)
        this->ui->objects_listWidget->addItem(QString::fromStdString(this->scene->mesh.objs[i]->name));

    this->ui->materials_comboBox->clear();
    for (size_t i = 0; i < this->scene->mesh.materials.size(); ++i)
        this->ui->materials_comboBox->addItem(QString::fromStdString(this->scene->mesh.materials[i]->name));

    this->ui->scrollAreaWidgetContents->setVisible(false);
    this->ui->scrollArea->verticalScrollBar()->hide();
}

void ObjectsWindow::updateSurface()
{
    if (!this->currentObj)
        return;

    this->setSurfaceDefault = false;
    if (currentObj->material->surface == DIFFUSE)
        this->ui->surface_comboBox->setCurrentIndex(this->ui->surface_comboBox->findText("Diffuse"));
    else if (currentObj->material->surface == REFLECTION)
        this->ui->surface_comboBox->setCurrentIndex(this->ui->surface_comboBox->findText("Reflection"));
    else if (currentObj->material->surface == TRANSMISSION)
        this->ui->surface_comboBox->setCurrentIndex(this->ui->surface_comboBox->findText("Transmission"));
    else if (currentObj->material->surface == EMISSION)
        this->ui->surface_comboBox->setCurrentIndex(this->ui->surface_comboBox->findText("Emission"));
    this->on_surface_comboBox_currentIndexChanged(this->ui->surface_comboBox->currentText());
    this->setSurfaceDefault = true;
}

std::string ObjectsWindow::uniqueMaterialName(const std::string &name, int nb)
{
    size_t i = 0;

    for (; i < this->scene->mesh.materials.size(); ++i)
    {
        if (name + (nb == 0 ? "" : "_" + std::to_string(nb)) == this->scene->mesh.materials[i]->name)
            break;
    }
    return (i >= this->scene->mesh.materials.size() ? name + (nb == 0 ? "" : "_" + std::to_string(nb)) : this->uniqueMaterialName(name, nb+1));
}

void ObjectsWindow::on_objects_listWidget_itemSelectionChanged()
{
    for (size_t i = 0; i < this->scene->mesh.objs.size(); ++i)
    {
        if (this->scene->mesh.objs[i]->name == this->ui->objects_listWidget->currentItem()->text().toStdString())
        {
            this->currentObj = this->scene->mesh.objs[i];
            break;
        }
    }
    this->ui->scrollAreaWidgetContents->setVisible(true);
    this->ui->scrollArea->verticalScrollBar()->show();
    this->ui->materials_comboBox->setCurrentIndex(this->ui->materials_comboBox->findText(QString::fromStdString(this->currentObj->material->name)));
}

void ObjectsWindow::on_materials_comboBox_currentIndexChanged(const QString &currentText)
{
    if (!this->currentObj)
        return;

    for (size_t i = 0; i < this->scene->mesh.materials.size(); ++i)
    {
        if (this->scene->mesh.materials[i]->name == currentText.toStdString())
        {
            this->currentObj->material = this->scene->mesh.materials[i];
            break;
        }
    }
    if (this->ui->materials_comboBox->currentIndex() == -1)
    {
        this->ui->surface_groupBox->setVisible(false);
        this->ui->materials_comboBox->lineEdit()->setVisible(false);
    }
    else
    {
        this->ui->surface_groupBox->setVisible(true);
        this->ui->materials_comboBox->lineEdit()->setVisible(true);
    }
    this->updateSurface();
}

void ObjectsWindow::materials_comboBox_editingFinished()
{
    if (!this->currentObj)
        return;

    if (this->ui->materials_comboBox->currentText() == "")
    {
        this->ui->materials_comboBox->setCurrentText(QString::fromStdString(this->currentObj->material->name));
        return;
    }
    this->currentObj->material->name = this->ui->materials_comboBox->currentText().toStdString();
    this->ui->materials_comboBox->setItemText(this->ui->materials_comboBox->currentIndex(), this->ui->materials_comboBox->currentText());
}

void ObjectsWindow::on_newMaterial_pushButton_clicked()
{
    if (!this->currentObj)
        return;

    Material *material = new Material();

    material->name = this->uniqueMaterialName("Material");
    this->scene->mesh.materials.push_back(material);
    this->ui->materials_comboBox->addItem(QString::fromStdString(material->name));
    this->currentObj->material = material;
    this->ui->materials_comboBox->setCurrentIndex(this->ui->materials_comboBox->findText(QString::fromStdString(this->currentObj->material->name)));
    this->setSurfaceDefault = true;
    this->on_surface_comboBox_currentIndexChanged(this->ui->surface_comboBox->itemText(0));
}

void ObjectsWindow::on_deleteMaterial_pushButton_clicked()
{
    if (!this->currentObj)
        return;

    this->currentObj->material = &this->scene->mesh.defaultMaterial;
    this->ui->materials_comboBox->setCurrentIndex(-1);
}

void ObjectsWindow::on_surface_comboBox_currentIndexChanged(const QString &currentText)
{
    if (!this->currentObj)
        return;

    if (this->setSurfaceDefault)
    {
        this->currentObj->material->color = Vector3d(1.0, 1.0, 1.0);
        this->currentObj->material->emission = 0.0;
        this->currentObj->material->roughness = 0.0;
        this->currentObj->material->ior = 0.0;
    }
    this->ui->emission_widget->setVisible(false);
    this->ui->roughness_widget->setVisible(false);
    this->ui->ior_widget->setVisible(false);
    if (currentText == "Diffuse")
    {
        this->currentObj->material->surface = DIFFUSE;
    }
    else if (currentText == "Reflection")
    {
        this->currentObj->material->surface = REFLECTION;
        this->ui->roughness_widget->setVisible(true);
    }
    else if (currentText == "Transmission")
    {
        this->currentObj->material->surface = TRANSMISSION;
        if (this->setSurfaceDefault)
            this->currentObj->material->ior = 1.0;
        this->ui->roughness_widget->setVisible(true);
        this->ui->ior_widget->setVisible(true);
    }
    else if (currentText == "Emission")
    {
        this->currentObj->material->surface = EMISSION;
        if (this->setSurfaceDefault)
            this->currentObj->material->emission = 1.0;
        this->ui->emission_widget->setVisible(true);
    }
    this->ui->color_pushButton->setStyleSheet("background-color: rgb("+
                                              QString::number(this->currentObj->material->color.x*255.0)+","+
                                              QString::number(this->currentObj->material->color.y*255.0)+","+
                                              QString::number(this->currentObj->material->color.z*255.0)+")");
    this->ui->emission_doubleSpinBox->setValue(this->currentObj->material->emission);
    this->ui->roughness_doubleSpinBox->setValue(this->currentObj->material->roughness);
    this->ui->ior_doubleSpinBox->setValue(this->currentObj->material->ior);
}

void ObjectsWindow::on_color_pushButton_clicked()
{
    if (!this->currentObj)
        return;

    QColor color = QColorDialog::getColor(QColor(static_cast<int>(this->currentObj->material->color.x*255.0),
                                                 static_cast<int>(this->currentObj->material->color.y*255.0),
                                                 static_cast<int>(this->currentObj->material->color.z*255.0)));

    if (!color.isValid())
        return;
    this->currentObj->material->color = Vector3d(color.red()/255.0, color.green()/255.0, color.blue()/255.0);
    this->ui->color_pushButton->setStyleSheet("background-color: rgb("+
                                              QString::number(this->currentObj->material->color.x*255.0)+","+
                                              QString::number(this->currentObj->material->color.y*255.0)+","+
                                              QString::number(this->currentObj->material->color.z*255.0)+")");
}

void ObjectsWindow::on_emission_doubleSpinBox_valueChanged(double value)
{
    std::string name = this->ui->materials_comboBox->currentText().toStdString();

    for (size_t i = 0; i < this->scene->mesh.materials.size(); ++i)
    {
        if (this->scene->mesh.materials[i]->name == name)
        {
            this->scene->mesh.materials[i]->emission = value;
            break;
        }
    }
}
