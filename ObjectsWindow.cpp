#include "ObjectsWindow.h"
#include "ui_objectswindow.h"

ObjectsWindow::ObjectsWindow(Scene *scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWindow),
    scene(scene),
    currentObj(nullptr)
{
    this->ui->setupUi(this);
    this->displayObjectsList();
    this->ui->materials_comboBox->view()->setMinimumWidth(200);
    this->ui->materials_comboBox->view()->setMinimumHeight(200);
    this->ui->surface_groupBox->setVisible(false);
    //this->ui->materials_comboBox->setLineEdit(new QLineEdit);
    connect(this->ui->materials_comboBox->lineEdit(), SIGNAL(editingFinished()), SLOT(materials_comboBox_editingFinished()));
}

ObjectsWindow::~ObjectsWindow()
{
    delete ui;
}

void ObjectsWindow::displayObjectsList()
{
    this->ui->objects_listWidget->clear();
    for (size_t i = 0; i < this->scene->mesh.objs.size(); ++i)
        this->ui->objects_listWidget->addItem(QString::fromStdString(this->scene->mesh.objs[i]->name));

    this->ui->materials_comboBox->clear();
    for (size_t i = 0; i < this->scene->mesh.materials.size(); ++i)
        this->ui->materials_comboBox->addItem(QString::fromStdString(this->scene->mesh.materials[i]->name));

    this->ui->scrollAreaWidgetContents->setVisible(false);
    this->ui->scrollArea->verticalScrollBar()->hide();
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

void ObjectsWindow::on_objects_listWidget_currentTextChanged(const QString &currentText)
{
    for (size_t i = 0; i < this->scene->mesh.objs.size(); ++i)
    {
        if (this->scene->mesh.objs[i]->name == currentText.toStdString())
        {
            this->currentObj = this->scene->mesh.objs[i];
            break;
        }
    }
    this->ui->materials_comboBox->setCurrentIndex(-1);
    this->ui->materials_comboBox->setCurrentText(QString::fromStdString(this->currentObj->material->name));
    this->on_materials_comboBox_currentIndexChanged(QString::fromStdString(this->currentObj->material->name));
    this->ui->scrollAreaWidgetContents->setVisible(true);
    this->ui->scrollArea->verticalScrollBar()->show();
}

void ObjectsWindow::on_materials_comboBox_currentIndexChanged(const QString &currentText)
{
    if (currentText == "")
    {
        this->ui->surface_groupBox->setVisible(false);
        this->ui->materials_comboBox->lineEdit()->setVisible(false);
        return;
    }
    for (size_t i = 0; i < this->scene->mesh.materials.size(); ++i)
    {
        if (this->scene->mesh.materials[i]->name == currentText.toStdString())
        {
            this->currentObj->material = this->scene->mesh.materials[i];
            break;
        }
    }
    this->ui->emission_doubleSpinBox->setValue(this->currentObj->material->emission);
    this->ui->surface_groupBox->setVisible(true);
    this->ui->materials_comboBox->lineEdit()->setVisible(true);
}

void ObjectsWindow::materials_comboBox_editingFinished()
{
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
    Material *material = new Material();

    material->name = this->uniqueMaterialName("Material");
    this->scene->mesh.materials.push_back(material);
    this->ui->materials_comboBox->addItem(QString::fromStdString(material->name));
    for (size_t i = 0; i < this->scene->mesh.objs.size(); ++i)
    {
        if (this->scene->mesh.objs[i]->name == this->ui->objects_listWidget->currentItem()->text().toStdString())
        {
            this->scene->mesh.objs[i]->material = material;
            break;
        }
    }
    this->ui->materials_comboBox->setCurrentText(QString::fromStdString(material->name));
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

void ObjectsWindow::on_deleteMaterial_pushButton_clicked()
{
    this->ui->materials_comboBox->setCurrentIndex(-1);
    this->on_materials_comboBox_currentIndexChanged("");
    this->currentObj->material = &this->scene->mesh.defaultMaterial;
}
