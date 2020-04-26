#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->engine = new Engine(this);
    this->scene = this->engine->getScene();
    this->settingsWindow = new SettingsWindow(this->scene);
    this->objectsWindow = new ObjectsWindow(this->scene);
    this->ui->settings_gridWidget->layout()->addWidget(this->settingsWindow);
    this->ui->objects_gridWidget->layout()->addWidget(this->objectsWindow);
    this->ui->openGL_GLWidget->setSettingsWindow(this->settingsWindow);
    this->ui->openGL_GLWidget->setScene(this->scene);
    this->ui->openGL_GLWidget->pauseRendering(true);
    this->ui->pathtracing_GLWidget->setScene(this->scene);
}

MainWindow::~MainWindow()
{
    this->engine->clean();
    delete this->engine;
    delete this->ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    delete this->settingsWindow;
    delete this->objectsWindow;
    this->engine->stop();
    event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    static bool status = false;

    if (e->key() == Qt::Key::Key_Escape)
    {
        ((QWidget *)this->settingsWindow->parent())->setVisible(status);
        ((QWidget *)this->objectsWindow->parent())->setVisible(status);
        status = !status;
    }
}

void MainWindow::disableOptions(bool status)
{
    this->ui->menuBar->setDisabled(status);
    this->ui->render_pushButton->setDisabled(status);
    this->ui->stop_pushButton->setEnabled(status);
    this->settingsWindow->setDisabled(status);
    this->objectsWindow->setDisabled(status);
    this->ui->openGL_GLWidget->pauseRendering(status);
}

void MainWindow::writeTerminal(const QString &str, bool replace)
{
    if (replace && this->ui->terminal_listWidget->count())
        this->ui->terminal_listWidget->item(this->ui->terminal_listWidget->count()-1)->setText(str);
    else
        this->ui->terminal_listWidget->addItem(str);
    if (this->ui->terminal_listWidget->count())
        this->ui->terminal_listWidget->scrollToItem(this->ui->terminal_listWidget->item(this->ui->terminal_listWidget->count()-1));
}

bool MainWindow::loadFile(QString path)
{
    Benchmark benchmark;
    QFileInfo fi(path);
    QString fileName = fi.fileName();

    if (fileName.isEmpty())
        return (false);

    this->objPath = path;
    this->writeTerminal("Loading "+fileName+" -> ...");
    qApp->processEvents();
    benchmark.start();
    this->scene->loadFile(path.toStdString());
    this->writeTerminal("Loading "+fileName+" -> "+QString::fromStdString(benchmark.getBenchTime().fullTime_str), true);

    this->writeTerminal("Building collision tree -> ...");
    qApp->processEvents();
    benchmark.start();
    this->scene->buidTree();
    this->writeTerminal("Building collision tree -> "+QString::fromStdString(benchmark.getBenchTime().fullTime_str), true);

    if (!this->scene->mesh.collisionTree)
    {
        this->writeTerminal("Failed");
        return (false);
    }
    this->writeTerminal("Success");
    this->ui->render_pushButton->setEnabled(true);
    this->objectsWindow->displayObjectsList();
    this->ui->openGL_GLWidget->pauseRendering(false);
    this->ui->openGL_GLWidget->init();
    return (true);
}

void MainWindow::on_actionImport_obj_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open file"), "",
                                                tr("OBJ file (*.obj);;All Files (*)"));

    if (path.isNull())
        return;
    this->loadFile(path);
}

void MainWindow::on_actionSave_scene_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save scene"), "",
                                                    tr("JSON file (*.json);;All Files (*)"));

    if (fileName.isNull())
        return;

    /* Create JSON */
    QJsonObject jsonObject;
    QJsonDocument jsonDocument;

    jsonObject["obj"] = this->objPath;

    jsonObject["camera"] = QJsonObject({{"resolution", QJsonObject({{"width", this->scene->camera->width},
                                                                    {"height", this->scene->camera->height}})},
                                        {"position", QJsonObject({{"x", this->scene->camera->position.x},
                                                                  {"y", this->scene->camera->position.y},
                                                                  {"z", this->scene->camera->position.z}})},
                                        {"rotation", QJsonObject({{"x", this->scene->camera->rotation.x},
                                                                  {"y", this->scene->camera->rotation.y},
                                                                  {"z", this->scene->camera->rotation.z}})}});

    jsonObject["pathtracing"] = QJsonObject({{"pixel", QJsonObject({{"samples", this->scene->samples},
                                                                    {"depth", this->scene->maxDepth}})}});

    {
        QJsonArray jsonArray;

        for (size_t i = 0; i < this->scene->mesh.materials.size(); ++i)
        {
            QString surface;

            if (this->scene->mesh.materials[i]->surface == DIFFUSE) surface = "DIFFUSE";
            else if (this->scene->mesh.materials[i]->surface == REFLECTION) surface = "REFLECTION";
            else if (this->scene->mesh.materials[i]->surface == TRANSMISSION) surface = "TRANSMISSION";
            else if (this->scene->mesh.materials[i]->surface == EMISSION) surface = "EMISSION";
            jsonArray.push_back(QJsonObject({{"name", QString::fromStdString(this->scene->mesh.materials[i]->name)},
                                             {"surface", surface},
                                             {"color", QJsonObject({{"r", this->scene->mesh.materials[i]->color.x},
                                                                    {"g", this->scene->mesh.materials[i]->color.y},
                                                                    {"b", this->scene->mesh.materials[i]->color.z}})},
                                             {"emission", this->scene->mesh.materials[i]->emission}}));
        }
        jsonObject["materials"] = jsonArray;
    }

    {
        QJsonArray jsonArray;

        for (size_t i = 0; i < this->scene->mesh.objs.size(); ++i)
        {
            jsonArray.push_back(QJsonObject({{"name", QString::fromStdString(this->scene->mesh.objs[i]->name)},
                                             {"material", QString::fromStdString(this->scene->mesh.objs[i]->material->name)}}));
        }
        jsonObject["objects"] = jsonArray;
    }

    jsonDocument.setObject(jsonObject);

    /* Save JSON */
    std::ofstream file;

    file.open(fileName.toStdString());
    file << jsonDocument.toJson().toStdString();
    file.close();
}

void MainWindow::on_actionLoad_scene_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load scene"), "",
                                                    tr("JSON file (*.json);;All Files (*)"));
    if (fileName.isNull())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QByteArray saveData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(saveData);

    /* Read JSON */
    if (!this->loadFile(document["obj"].toString()))
        return;

    this->scene->camera->width = document["camera"]["resolution"]["width"].toInt();
    this->scene->camera->height = document["camera"]["resolution"]["height"].toInt();
    this->scene->camera->position.x = document["camera"]["position"]["x"].toDouble();
    this->scene->camera->position.y = document["camera"]["position"]["y"].toDouble();
    this->scene->camera->position.z = document["camera"]["position"]["z"].toDouble();
    this->scene->camera->rotation.x = document["camera"]["rotation"]["x"].toDouble();
    this->scene->camera->rotation.y = document["camera"]["rotation"]["y"].toDouble();
    this->scene->camera->rotation.z = document["camera"]["rotation"]["z"].toDouble();
    this->scene->samples = document["pathtracing"]["pixel"]["samples"].toInt();
    this->scene->maxDepth = document["pathtracing"]["pixel"]["depth"].toInt();
    this->settingsWindow->updateValues();

    {
        QJsonArray jsonArray = document["materials"].toArray();

        for (const QJsonValue &jsonValue : jsonArray)
        {
            Material *material = new Material();
            QString surface = jsonValue.toObject()["surface"].toString();

            if (surface == "DIFFUSE") material->surface = DIFFUSE;
            else if (surface == "REFLECTION") material->surface = REFLECTION;
            else if (surface == "TRANSMISSION") material->surface = TRANSMISSION;
            else if (surface == "EMISSION") material->surface = EMISSION;
            material->name = jsonValue.toObject()["name"].toString().toStdString();
            material->color = Vector3d(jsonValue.toObject()["color"].toObject()["r"].toDouble(),
                    jsonValue.toObject()["color"].toObject()["g"].toDouble(),
                    jsonValue.toObject()["color"].toObject()["b"].toDouble());
            material->emission = jsonValue.toObject()["emission"].toDouble();
            this->scene->mesh.materials.push_back(material);
        }
        this->objectsWindow->updateMaterialList();
    }

    {
        QJsonArray jsonArray = document["objects"].toArray();

        for (const QJsonValue &jsonValue : jsonArray)
        {
            if (!jsonValue.toObject()["material"].toString().isEmpty())
            {
                for (size_t i = 0; i < this->scene->mesh.objs.size(); ++i)
                {
                    if (jsonValue.toObject()["name"].toString().toStdString() == this->scene->mesh.objs[i]->name)
                    {
                        for (size_t t = 0; t < this->scene->mesh.materials.size(); ++t)
                        {
                            if (jsonValue.toObject()["material"].toString().toStdString() == this->scene->mesh.materials[t]->name)
                            {
                                this->scene->mesh.objs[i]->material = this->scene->mesh.materials[t];
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

void MainWindow::on_render_pushButton_clicked()
{
    this->disableOptions(true);
    this->ui->pathtracing_GLWidget->init();
    this->engine->setPixels(this->ui->pathtracing_GLWidget->getPixels());
    this->engine->start();
}

void MainWindow::on_stop_pushButton_clicked()
{
    this->engine->stop();
    this->disableOptions(false);
    this->ui->pathtracing_GLWidget->stop();
}
