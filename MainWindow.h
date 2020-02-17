#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "SettingsWindow.h"
#include "ObjectsWindow.h"
#include "Engine.h"

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
    void resizeWindows();
    Q_INVOKABLE void disableOptions(bool status);
    Q_INVOKABLE void writeTerminal(const QString &str, bool replace = false);

private slots:
    void on_load3DFile_pushButton_clicked();
    void on_render_pushButton_clicked();
    Q_INVOKABLE void on_stop_pushButton_clicked();
    void on_comboBox_activated(const QString &arg1);

private:
    ObjectsWindow *objectsWindow;
    SettingsWindow *settingsWindow;

    Engine *engine;
    Scene *scene;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
