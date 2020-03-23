#include "GLWidgetPathtracing.h"

GLWidgetPathtracing::GLWidgetPathtracing(QWidget *parent) :
    QOpenGLWidget(parent),
    scene(nullptr),
    update_timer(new QTimer(this)),
    pixels(nullptr),
    texture_id(0)
{
    connect(this->update_timer, SIGNAL(timeout()), this, SLOT(update_timeOut()));
    this->update_timer->start(1000/FPS);
}

GLWidgetPathtracing::~GLWidgetPathtracing()
{
    delete this->update_timer;
    if (this->pixels)
        delete [] this->pixels;
}

GLubyte *GLWidgetPathtracing::getPixels() const
{
    return (this->pixels);
}

void GLWidgetPathtracing::setScene(Scene *scene)
{
    this->scene = scene;
}

void GLWidgetPathtracing::init()
{
    if (this->pixels)
        delete [] this->pixels;
    this->pixels = new GLubyte[this->scene->camera->width*this->scene->camera->height*3];
    std::memset(this->pixels, 0, static_cast<size_t>(this->scene->camera->width*this->scene->camera->height*3));
}

void GLWidgetPathtracing::initializeGL()
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &this->texture_id);
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidgetPathtracing::resizeGL(int width, int height)
{
    static_cast<void>(width);
    static_cast<void>(height);
}

void GLWidgetPathtracing::paintGL()
{
    double ratio = qMin(static_cast<double>(this->width())/static_cast<double>(this->scene->camera->width),
                        static_cast<double>(this->height())/static_cast<double>(this->scene->camera->height));
    GLint width = static_cast<GLint>(this->scene->camera->width*ratio), height = static_cast<GLint>(this->scene->camera->height*ratio);

    if (!this->pixels)
        return;
    glViewport((this->width()-width)/2, (this->height()-height)/2, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->scene->camera->width, this->scene->camera->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(-1, 1);
    glTexCoord2i(0, 1); glVertex2i(-1, -1);
    glTexCoord2i(1, 1); glVertex2i(1, -1);
    glTexCoord2i(1, 0); glVertex2i(1, 1);
    glEnd();
}

void GLWidgetPathtracing::update_timeOut()
{
    this->update();
}
