#include "GLWidgetPathtracing.h"

GLWidgetPathtracing::GLWidgetPathtracing(QWidget *parent) :
    QOpenGLWidget(parent),
    _scene(nullptr),
    _currentWidth(0),
    _currentHeight(0),
    _rendering(true),
    _pixels(nullptr),
    _texture_id(0)
{
    connect(&this->_update_timer, SIGNAL(timeout()), this, SLOT(update_timeout()));
    this->_update_timer.start(1000/FPS);
}

GLWidgetPathtracing::~GLWidgetPathtracing()
{
    if (this->_pixels)
        delete [] this->_pixels;
}

GLubyte *GLWidgetPathtracing::getPixels() const
{
    return (this->_pixels);
}

void GLWidgetPathtracing::setScene(Scene *scene)
{
    this->_scene = scene;
}

void GLWidgetPathtracing::stop()
{
    this->update();
    this->_rendering = false;
}

void GLWidgetPathtracing::init()
{
    if (this->_pixels)
        delete [] this->_pixels;
    this->_currentWidth = this->_scene->_camera->_width;
    this->_currentHeight = this->_scene->_camera->_height;
    this->_pixels = new GLubyte[this->_scene->_camera->_width*this->_scene->_camera->_height*3];
    std::memset(this->_pixels, 0, static_cast<size_t>(this->_scene->_camera->_width*this->_scene->_camera->_height*3));
    this->_rendering = true;
}

void GLWidgetPathtracing::initializeGL()
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &this->_texture_id);
    glBindTexture(GL_TEXTURE_2D, this->_texture_id);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidgetPathtracing::resizeGL(int width, int height)
{
    static_cast<void>(width);
    static_cast<void>(height);
}

void GLWidgetPathtracing::paintGL()
{
    double ratio = qMin(static_cast<double>(this->width())/static_cast<double>(this->_currentWidth),
                        static_cast<double>(this->height())/static_cast<double>(this->_currentHeight));
    GLint width = static_cast<GLint>(this->_currentWidth*ratio), height = static_cast<GLint>(this->_currentHeight*ratio);

    if (!this->_pixels)
        return;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport((this->width()-width)/2, (this->height()-height)/2, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_currentWidth, this->_currentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, this->_pixels);
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
    if (this->_rendering)
        this->update();
}
