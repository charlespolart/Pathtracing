#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->engine = new Engine(this);
    this->scene = this->engine->getScene();
    this->ui->setupUi(this);
    this->ui->width_spinBox->setValue(this->scene->camera->width);
    this->ui->height_spinBox->setValue(this->scene->camera->height);
    this->ui->cameraPositionX_doubleSpinBox->setValue(this->scene->camera->position.x);
    this->ui->cameraPositionY_doubleSpinBox->setValue(this->scene->camera->position.y);
    this->ui->cameraPositionZ_doubleSpinBox->setValue(this->scene->camera->position.z);
    this->ui->cameraRotationX_doubleSpinBox->setValue(this->scene->camera->rotation.x);
    this->ui->cameraRotationY_doubleSpinBox->setValue(this->scene->camera->rotation.y);
    this->ui->cameraRotationZ_doubleSpinBox->setValue(this->scene->camera->rotation.z);
}

MainWindow::~MainWindow()
{
    this->engine->clean();
    delete this->engine;
    delete this->ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->engine->stop();
    event->accept();
}

void MainWindow::disableOptions(bool status)
{
    this->ui->render_pushButton->setDisabled(status);
    this->ui->stop_pushButton->setEnabled(status);
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

void MainWindow::on_load3DFile_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open file"), "",
                                                    tr("OBJ file (*.obj);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    this->writeTerminal("Loading \""+fileName+"\" ...");
    qApp->processEvents();
    this->scene->loadFile(fileName.toStdString());
    if (this->scene->mesh.collisionTree)
    {
        this->writeTerminal("Success");
        this->ui->render_pushButton->setEnabled(true);
    }
    else
        this->writeTerminal("Failed");
}

void MainWindow::on_render_pushButton_clicked()
{
    this->disableOptions(true);
    this->ui->openGLWidget->initWindow(this->scene->camera->width, this->scene->camera->height);
    this->engine->setPixels(this->ui->openGLWidget->getPixels());
    this->engine->start();
}

void MainWindow::on_stop_pushButton_clicked()
{
    this->engine->stop();
}

void MainWindow::on_width_spinBox_editingFinished()
{
    int width = (this->ui->width_spinBox->value()/4)*4;

    this->ui->width_spinBox->setValue(width);
    this->scene->camera->setWidth(width);
}

void MainWindow::on_height_spinBox_editingFinished()
{
    int height = (this->ui->height_spinBox->value()/4)*4;

    this->ui->height_spinBox->setValue(height);
    this->scene->camera->setHeight(height);
}

void MainWindow::on_cameraPositionX_doubleSpinBox_valueChanged(double value)
{
    this->scene->camera->position.x = value;
}

void MainWindow::on_cameraPositionY_doubleSpinBox_valueChanged(double value)
{
    this->scene->camera->position.y = value;
}

void MainWindow::on_cameraPositionZ_doubleSpinBox_valueChanged(double value)
{
    this->scene->camera->position.z = value;
}

void MainWindow::on_cameraRotationX_doubleSpinBox_valueChanged(double value)
{
    while (value >= 360.0)
        value -= 360.0;
    while (value <= -360.0)
        value += 360.0;
    this->ui->cameraRotationX_doubleSpinBox->setValue(value);
    this->scene->camera->rotation.x = value;
}

void MainWindow::on_cameraRotationY_doubleSpinBox_valueChanged(double value)
{
    while (value >= 360.0)
        value -= 360.0;
    while (value <= -360.0)
        value += 360.0;
    this->ui->cameraRotationY_doubleSpinBox->setValue(value);
    this->scene->camera->rotation.y = value;
}

void MainWindow::on_cameraRotationZ_doubleSpinBox_valueChanged(double value)
{
    while (value >= 360.0)
        value -= 360.0;
    while (value <= -360.0)
        value += 360.0;
    this->ui->cameraRotationZ_doubleSpinBox->setValue(value);
    this->scene->camera->rotation.z = value;
}
