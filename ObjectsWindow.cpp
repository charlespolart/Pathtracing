#include "ObjectsWindow.h"
#include "ui_objectswindow.h"

ObjectsWindow::ObjectsWindow(Scene *scene, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWindow),
    scene(scene)
{
    ui->setupUi(this);
    this->displayObjectsList();
}

ObjectsWindow::~ObjectsWindow()
{
    delete ui;
}

void ObjectsWindow::displayObjectsList()
{
    this->ui->objects_listWidget->clear();
    for (size_t i = 0; i < scene->mesh.objs.size(); ++i)
    {
        this->ui->objects_listWidget->addItem(QString::fromStdString(scene->mesh.objs[i]->name));
    }
}
