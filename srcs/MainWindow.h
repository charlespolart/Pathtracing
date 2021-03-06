#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "Engine.h"
#include "SettingsWindow.h"
#include "ObjectsWindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *e);
    void resizeWindows();
    void disableOptions(bool status);
    Q_INVOKABLE void progressBar(int nb);
    Q_INVOKABLE void writeTerminal(const QString &str, bool replace = false);
    bool loadFile(QString path);

private slots:
    void on_actionImport_obj_triggered();
    void on_actionSave_scene_triggered();
    void on_actionLoad_scene_triggered();
    void on_render_pushButton_clicked();
    Q_INVOKABLE void on_stop_pushButton_clicked();

private:
    ObjectsWindow *_objectsWindow;
    SettingsWindow *_settingsWindow;

    Engine *_engine;
    Scene *_scene;
    QString _objPath;
    Ui::MainWindow *_ui;
};

#endif // MAINWINDOW_H
