#include "GLWidgetPathtracing.h"

GLWidgetPathtracing::GLWidgetPathtracing(QWidget *parent) :
    QOpenGLWidget(parent),
    scene(nullptr),
    currentWidth(0),
    currentHeight(0),
    rendering(true),
    pixels(nullptr),
    texture_id(0)
{
    connect(&this->update_timer, SIGNAL(timeout()), this, SLOT(update_timeout()));
    this->update_timer.start(1000/FPS);
}

GLWidgetPathtracing::~GLWidgetPathtracing()
{
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

void GLWidgetPathtracing::stop()
{
    this->update();
    this->rendering = false;
}

void GLWidgetPathtracing::init()
{
    if (this->pixels)
        delete [] this->pixels;
    this->currentWidth = this->scene->camera->width;
    this->currentHeight = this->scene->camera->height;
    this->pixels = new GLubyte[this->currentWidth*this->currentHeight*3];
    std::memset(this->pixels, 0, static_cast<size_t>(this->currentWidth*this->currentHeight*3));
    this->rendering = true;
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
    double ratio = qMin(static_cast<double>(this->width())/static_cast<double>(this->currentWidth),
                        static_cast<double>(this->height())/static_cast<double>(this->currentHeight));
    GLint width = static_cast<GLint>(this->currentWidth*ratio), height = static_cast<GLint>(this->currentHeight*ratio);

    if (!this->pixels)
        return;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport((this->width()-width)/2, (this->height()-height)/2, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->currentWidth, this->currentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, this->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(-1, 1);
    glTexCoord2i(0, 1); glVertex2i(-1, -1);
    glTexCoord2i(1, 1); glVertex2i(1, -1);
    glTexCoord2i(1, 0); glVertex2i(1, 1);
    glEnd();
}

void GLWidgetPathtracing::update_timeout()
{
    if (this->rendering)
        this->update();
}
