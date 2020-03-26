#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->engine = new Engine(this);
    this->scene = this->engine->getScene();
    this->settingsWindow = new SettingsWindow(this->scene);
    this->objectsWindow = new ObjectsWindow(this->scene);
    this->settingsWindow->show();
    this->objectsWindow->show();
    this->ui->setupUi(this);
    this->resizeWindows();
    connect(this->ui->actionSettings, &QAction::triggered, this->settingsWindow, &SettingsWindow::show);
    connect(this->ui->actionObjects, &QAction::triggered, this->objectsWindow, &ObjectsWindow::show);
    this->ui->openGL_GLWidget->setSettingsWindow(this->settingsWindow);
    this->ui->openGL_GLWidget->setScene(this->scene);
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

void MainWindow::resizeWindows()
{
    QDesktopWidget desktop;
    QRect screenSize = desktop.availableGeometry(this);
    int titleBarHeight = QApplication::style()->pixelMetric(QStyle::PM_TitleBarHeight);
    int width = screenSize.width();
    int height = screenSize.height() - titleBarHeight;
    double mainWindowWidthRatio = 0.6;

    this->resize(width*mainWindowWidthRatio, height);
    this->move(width*(1.0-mainWindowWidthRatio)/2.0, 0);
    this->settingsWindow->resize(width*(1.0-mainWindowWidthRatio)/2.0, height);
    this->settingsWindow->move(0, 0);
    this->objectsWindow->resize(width*(1.0-mainWindowWidthRatio)/2.0, height);
    this->objectsWindow->move(width*((1.0-mainWindowWidthRatio)/2.0+mainWindowWidthRatio), 0);
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
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open file"), "",
                                                tr("OBJ file (*.obj);;All Files (*)"));
    QFileInfo fi(path);
    QString fileName = fi.fileName();
    Benchmark benchmark;

    if (fileName.isEmpty())
        return;

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

    if (this->scene->mesh.collisionTree)
    {
        this->writeTerminal("Success");
        this->ui->render_pushButton->setEnabled(true);
        this->objectsWindow->displayObjectsList();
        this->ui->openGL_GLWidget->init();
    }
    else
        this->writeTerminal("Failed");
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
