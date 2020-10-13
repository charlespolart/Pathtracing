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
    SettingsWindow *_settingsWindow;
    Scene *_scene;
    QTimer _update_timer;
    bool _rendering;

    QElapsedTimer _frame_time;
    double _deltaTime;
    int _lastMouseX, _lastMouseY;
    Vector3d _lastRotation;
    Vector3d _lastPosition;
    inputs_t _inputs;

    std::vector<Vector3d> _vertices;
    std::vector<Vector3d> _normals;
    uint *_indices;
    size_t _indices_size;
    GLuint _vbo_vertices_id;
    GLuint _vbo_normals_id;
    GLuint _vbo_indices_id;
};

#endif // GLWIDGETOPENGL_H
