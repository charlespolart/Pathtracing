#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <cstring>
#include <iostream>
#include "Vector.h"

#define FPS 30

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

public:
    GLubyte *getPixels() const;

public:
    void initWindow(int width, int height);

private:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private slots:
  void update_timeOut();

private:
    size_t pWidth, pHeight;
    GLubyte *pixels;
    GLuint textureId;
    QTimer *update_timer;
};

#endif //!GLWIDGET_H
