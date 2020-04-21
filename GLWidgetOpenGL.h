#ifndef GLWIDGETOPENGL_H
#define GLWIDGETOPENGL_H

#include <QtOpenGL>
#include <QGLWidget>
#include <GL/glu.h>
#include <cstring>
#include <iostream>
#include "MainWindow.h"
#include "Scene.h"
#include "Vector.h"

#define FPS 30

struct inputs_t
{
    bool rightButton = false;
    bool leftButton = false;
};

class GLWidgetOpenGL: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidgetOpenGL(QWidget *parent = nullptr);
    ~GLWidgetOpenGL();

public:
    void setSettingsWindow(SettingsWindow *settingsWindow);
    void setScene(Scene *scene);

public:
    void init();
    void pauseRendering(bool status);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

private slots:
    void update_timeout();

private:
    SettingsWindow *settingsWindow;
    Scene *scene;
    QTimer update_timer;
    bool rendering;

    QTime frame_time;
    double deltaTime;
    int lastMouseX, lastMouseY;
    Vector3d lastRotation;
    Vector3d lastPosition;
    inputs_t inputs;

    std::vector<Vector3d> vertices;
    std::vector<Vector3d> normals;
    uint *indices;
    size_t indices_size;
    GLuint vbo_vertices_id;
    GLuint vbo_normals_id;
    GLuint vbo_indices_id;
};

#endif // GLWIDGETOPENGL_H
