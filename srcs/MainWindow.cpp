#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    this->_ui->setupUi(this);
    this->_engine = new Engine(this);
    this->_scene = this->_engine->getScene();
    this->_settingsWindow = new SettingsWindow(this->_scene);
    this->_objectsWindow = new ObjectsWindow(this->_scene);
    this->_ui->settings_gridWidget->layout()->addWidget(this->_settingsWindow);
    this->_ui->objects_gridWidget->layout()->addWidget(this->_objectsWindow);
    this->_ui->openGL_GLWidget->setSettingsWindow(this->_settingsWindow);
    this->_ui->openGL_GLWidget->setScene(this->_scene);
    this->_ui->openGL_GLWidget->pauseRendering(true);
    this->_ui->pathtracing_GLWidget->setScene(this->_scene);
    this->_ui->progressBar->setVisible(false);
}

MainWindow::~MainWindow()
{
    this->_engine->exit();
    delete this->_engine;
    delete this->_ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    delete this->_settingsWindow;
    delete this->_objectsWindow;
    this->_engine->stop();
    event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    static bool status = false;

    if (e->key() == Qt::Key::Key_Escape)
    {
        ((QWidget *)this->_settingsWindow->parent())->setVisible(status);
        ((QWidget *)this->_objectsWindow->parent())->setVisible(status);
        status = !status;
    }
}

void MainWindow::disableOptions(bool status)
{
    this->_ui->menuBar->setDisabled(status);
    this->_ui->stop_pushButton->setEnabled(status);
    this->_settingsWindow->setDisabled(status);
    this->_objectsWindow->setDisabled(status);
    this->_ui->openGL_GLWidget->pauseRendering(status);
}

void MainWindow::progressBar(int nb)
{
    this->_ui->progressBar->setValue(nb);
}

void MainWindow::writeTerminal(const QString &str, bool replace)
{
    if (replace && this->_ui->terminal_listWidget->count())
        this->_ui->terminal_listWidget->item(this->_ui->terminal_listWidget->count()-1)->setText(str);
    else
        this->_ui->terminal_listWidget->addItem(str);
    if (this->_ui->terminal_listWidget->count())
        this->_ui->terminal_listWidget->scrollToItem(this->_ui->terminal_listWidget->item(this->_ui->terminal_listWidget->count()-1));
}

bool MainWindow::loadFile(QString path)
{
    Benchmark benchmark;
    QFileInfo fi(path);
    QString fileName = fi.fileName();

    if (fileName.isEmpty())
        return (false);

    this->_objPath = path;
    this->writeTerminal("Loading "+fileName+" -> ...");
    qApp->processEvents();
    benchmark.start();
    if (!this->_scene->loadFile(path.toStdString()))
    {
        this->writeTerminal("Failed to open");
        return (false);
    }
    this->writeTerminal("Loading "+fileName+" -> "+QString::fromStdString(benchmark.getBenchTime().fullTime_str), true);

    this->writeTerminal("Building collision tree -> ...");
    qApp->processEvents();
    benchmark.start();
    this->_scene->buidTree();
    this->writeTerminal("Building collision tree -> "+QString::fromStdString(benchmark.getBenchTime().fullTime_str), true);

    if (!this->_scene->_mesh.collisionTree)
    {
        this->writeTerminal("Failed");
        return (false);
    }
    this->writeTerminal("Success");
    this->_ui->render_pushButton->setEnabled(true);
    this->_objectsWindow->displayObjectsList();
    this->_ui->openGL_GLWidget->pauseRendering(false);
    this->_ui->openGL_GLWidget->init();
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

    QJsonObject jsonObject;
    QJsonDocument jsonDocument;

    jsonObject["obj"] = this->_objPath;

    jsonObject["camera"] = QJsonObject({{"resolution", QJsonObject({{"width", this->_scene->_camera->_width},
                                                                    {"height", this->_scene->_camera->_height}})},
                                        {"position", QJsonObject({{"x", this->_scene->_camera->_position.x},
                                                                  {"y", this->_scene->_camera->_position.y},
                                                                  {"z", this->_scene->_camera->_position.z}})},
                                        {"rotation", QJsonObject({{"x", this->_scene->_camera->_rotation.x},
                                                                  {"y", this->_scene->_camera->_rotation.y},
                                                                  {"z", this->_scene->_camera->_rotation.z}})}});

    jsonObject["pathtracing"] = QJsonObject({{"pixel", QJsonObject({{"samples", this->_scene->_samples},
                                                                    {"depth", this->_scene->_maxDepth}})}});

    QJsonArray jsonArray;

    for (std::map<std::string, Material *>::iterator it = this->_scene->_mesh.materials.begin(); it != this->_scene->_mesh.materials.end(); ++it)
    {
        if (!it->second) continue; /* !!! NEED TO FIX !!! */
        QString surface;

        if (it->second->_surface == DIFFUSE) surface = "DIFFUSE";
        else if (it->second->_surface == REFLECTION) surface = "REFLECTION";
        else if (it->second->_surface == TRANSMISSION) surface = "TRANSMISSION";
        jsonArray.push_back(QJsonObject({{"name", QString::fromStdString(it->second->_name)},
                                         {"surface", surface},
                                         {"color", QJsonObject({{"r", it->second->_color.x},
                                                                {"g", it->second->_color.y},
                                                                {"b", it->second->_color.z}})},
                                         {"roughness", it->second->_roughness},
                                         {"ior", it->second->_ior},
                                         {"emission", it->second->_emission}}));
    }
    jsonObject["materials"] = jsonArray;

    jsonDocument.setObject(jsonObject);

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

    this->_scene->_camera->_width = document["camera"]["resolution"]["width"].toInt();
    this->_scene->_camera->_height = document["camera"]["resolution"]["height"].toInt();
    this->_scene->_camera->_position.x = document["camera"]["position"]["x"].toDouble();
    this->_scene->_camera->_position.y = document["camera"]["position"]["y"].toDouble();
    this->_scene->_camera->_position.z = document["camera"]["position"]["z"].toDouble();
    this->_scene->_camera->_rotation.x = document["camera"]["rotation"]["x"].toDouble();
    this->_scene->_camera->_rotation.y = document["camera"]["rotation"]["y"].toDouble();
    this->_scene->_camera->_rotation.z = document["camera"]["rotation"]["z"].toDouble();
    this->_scene->_samples = document["pathtracing"]["pixel"]["samples"].toInt();
    this->_scene->_maxDepth = document["pathtracing"]["pixel"]["depth"].toInt();
    this->_settingsWindow->updateValues();

    if (!this->loadFile(document["obj"].toString()))
        return;

    QJsonArray jsonArray = document["materials"].toArray();

    for (const QJsonValue &jsonValue : jsonArray)
    {
        std::string name = jsonValue.toObject()["name"].toString().toStdString();
        if (this->_scene->_mesh.materials.find(name) == this->_scene->_mesh.materials.end())
            continue;
        Material *material = this->_scene->_mesh.materials[name];
        QString surface = jsonValue.toObject()["surface"].toString();

        if (surface == "DIFFUSE") material->_surface = DIFFUSE;
        else if (surface == "REFLECTION") material->_surface = REFLECTION;
        else if (surface == "TRANSMISSION") material->_surface = TRANSMISSION;
        material->_color = Vector3d(jsonValue.toObject()["color"].toObject()["r"].toDouble(),
                jsonValue.toObject()["color"].toObject()["g"].toDouble(),
                jsonValue.toObject()["color"].toObject()["b"].toDouble());
        material->_roughness = jsonValue.toObject()["roughness"].toDouble();
        material->_ior = jsonValue.toObject()["ior"].toDouble();
        material->_emission = jsonValue.toObject()["emission"].toDouble();
    }
}

void MainWindow::on_render_pushButton_clicked()
{
    if (this->_engine->isRendering())
    {
        this->_engine->pause();
        this->_ui->render_pushButton->setText(this->_engine->isPaused() ? "Resume" : "Pause");
    }
    else
    {
        this->_ui->render_pushButton->setText("Pause");
        if (this->_scene->_samples)
        {
            this->_ui->progressBar->setValue(0);
            this->_ui->progressBar->setVisible(true);
        }
        this->disableOptions(true);
        this->_ui->pathtracing_GLWidget->init();
        this->_engine->setPixels(this->_ui->pathtracing_GLWidget->getPixels());
        this->_engine->start();
    }
}

void MainWindow::on_stop_pushButton_clicked()
{
    this->_ui->render_pushButton->setText("Render");
    this->_engine->stop();
    this->_ui->progressBar->setVisible(false);
    this->disableOptions(false);
    this->_ui->pathtracing_GLWidget->stop();
}
