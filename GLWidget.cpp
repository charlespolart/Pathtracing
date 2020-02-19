#include "GLWidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    pWidth(0), pHeight(0),
    pixels(nullptr),
    textureId(0),
    update_timer(new QTimer(this))
{
    connect(this->update_timer, SIGNAL(timeout()), this, SLOT(update_timeOut()));
    this->update_timer->start(1000/FPS);
}

GLWidget::~GLWidget()
{
    delete this->update_timer;
    if (this->pixels)
        delete [] this->pixels;
}

GLubyte *GLWidget::getPixels() const
{
    return (this->pixels);
}

void GLWidget::initWindow(int width, int height)
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    this->pWidth = width;
    this->pHeight = height;
    if (this->pixels)
        delete [] this->pixels;
    this->pixels = new GLubyte[this->pWidth*this->pHeight*3];
    std::memset(this->pixels, 0, static_cast<size_t>(this->pWidth*this->pHeight*3));
}

void GLWidget::initializeGL()
{
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
}

void GLWidget::resizeGL(int width, int height)
{
    static_cast<void>(width);
    static_cast<void>(height);
}

void GLWidget::paintGL()
{
    double ratio = qMin(static_cast<double>(this->width())/static_cast<double>(this->pWidth),
                        static_cast<double>(this->height())/static_cast<double>(this->pHeight));
    GLint width = static_cast<GLint>(this->pWidth*ratio), height = static_cast<GLint>(this->pHeight*ratio);

    if (!this->pixels)
        return;
    glViewport((this->width()-width)/2, (this->height()-height)/2, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->pWidth, this->pHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, this->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(-1, 1);
    glTexCoord2i(0, 1); glVertex2i(-1, -1);
    glTexCoord2i(1, 1); glVertex2i(1, -1);
    glTexCoord2i(1, 0); glVertex2i(1, 1);
    glEnd();
}

void GLWidget::update_timeOut()
{
    this->update();
}
