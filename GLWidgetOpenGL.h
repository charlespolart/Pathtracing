#ifndef GLWIDGETOPENGL_H
#define GLWIDGETOPENGL_H

#include <QtOpenGL>
#include <QGLWidget>
#include <GL/glu.h>
#include <cstring>
#include <iostream>
#include "Scene.h"
#include "Vector.h"

#define FPS 30

class GLWidgetOpenGL: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidgetOpenGL(QWidget *parent = nullptr);
    ~GLWidgetOpenGL();

public:
    void setScene(Scene *scene);

public:
    void init();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private slots:
  void update_timeOut();

private:
    Scene *scene;
    QTimer *update_timer;

    std::vector<Vector3d> vertices;
    std::vector<Vector3d> normals;
    uint *indices;
    size_t indices_size;
    GLuint vbo_vertices_id;
    GLuint vbo_normals_id;
    GLuint vbo_indices_id;
};

#endif // GLWIDGETOPENGL_H
