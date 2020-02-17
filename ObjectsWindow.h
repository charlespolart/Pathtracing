#ifndef OBJECTSWINDOW_H
#define OBJECTSWINDOW_H

#include <QWidget>
#include "Scene.h"

namespace Ui {
class ObjectsWindow;
}

class ObjectsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectsWindow(Scene *scene, QWidget *parent = nullptr);
    ~ObjectsWindow();

public:
    void displayObjectsList();

private:
    Ui::ObjectsWindow *ui;

    Scene *scene;
};

#endif // OBJECTSWINDOW_H
