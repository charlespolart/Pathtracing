#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
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
    Q_INVOKABLE void disableOptions(bool status);
    Q_INVOKABLE void writeTerminal(const QString &str, bool replace = false);

private slots:
    void on_load3DFile_pushButton_clicked();
    void on_render_pushButton_clicked();
    Q_INVOKABLE void on_stop_pushButton_clicked();
    void on_width_spinBox_editingFinished();
    void on_height_spinBox_editingFinished();
    void on_cameraPositionX_doubleSpinBox_valueChanged(double value);
    void on_cameraPositionY_doubleSpinBox_valueChanged(double value);
    void on_cameraPositionZ_doubleSpinBox_valueChanged(double value);
    void on_cameraRotationX_doubleSpinBox_valueChanged(double value);
    void on_cameraRotationY_doubleSpinBox_valueChanged(double value);
    void on_cameraRotationZ_doubleSpinBox_valueChanged(double value);

private:
    Engine *engine;
    Scene *scene;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
