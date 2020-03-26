#ifndef GLWIDGETPATHTRACING_H
#define GLWIDGETPATHTRACING_H

#include <QtOpenGL>
#include <QGLWidget>
#include <cstring>
#include <iostream>
#include "Scene.h"
#include "Vector.h"

#define FPS 30

class GLWidgetPathtracing : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit GLWidgetPathtracing(QWidget *parent = nullptr);
    ~GLWidgetPathtracing();

public:
    GLubyte *getPixels() const;
    void setScene(Scene *scene);
    void stop();

public:
    void init();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private slots:
  void update_timeout();

private:
    Scene *scene;
    QTimer update_timer;
    int currentWidth, currentHeight;
    bool rendering;

    GLubyte *pixels;
    GLuint texture_id;
};

#endif // GLWIDGETPATHTRACING_H
