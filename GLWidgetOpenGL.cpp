#include "GLWidgetOpenGL.h"

GLWidgetOpenGL::GLWidgetOpenGL(QWidget *parent) :
    QOpenGLWidget(parent),
    scene(nullptr),
    deltaTime(0.0),
    lastMouseX(0),
    lastMouseY(0),
    indices(nullptr),
    indices_size(0),
    vbo_vertices_id(0),
    vbo_normals_id(0),
    vbo_indices_id(0)
{
    connect(&this->update_timer, SIGNAL(timeout()), this, SLOT(update_timeout()));
    this->update_timer.start(1000/FPS);
}

GLWidgetOpenGL::~GLWidgetOpenGL()
{
    if(glIsBuffer(vbo_vertices_id) == GL_TRUE)
        glDeleteBuffers(1, &vbo_vertices_id);
    if(glIsBuffer(vbo_normals_id) == GL_TRUE)
        glDeleteBuffers(1, &vbo_normals_id);
    if(glIsBuffer(vbo_indices_id) == GL_TRUE)
        glDeleteBuffers(1, &vbo_indices_id);
    if (this->indices)
        delete [] this->indices;
}

void GLWidgetOpenGL::mousePressEvent(QMouseEvent *e)
{
    this->lastMouseX = e->x();
    this->lastMouseY = e->y();
    if (e->button() == Qt::LeftButton)
    {
        this->lastRotation = this->scene->camera->rotation;
        this->inputs.leftButton = true;
    }
    if (e->button() == Qt::RightButton)
    {
        this->lastPosition = this->scene->camera->position;
        this->inputs.rightButton = true;
    }
}

void GLWidgetOpenGL::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        this->inputs.leftButton = false;
    if (e->button() == Qt::RightButton)
        this->inputs.rightButton = false;
}

void GLWidgetOpenGL::mouseMoveEvent(QMouseEvent *e)
{
    int mouseDeltaX = (e->x() - this->lastMouseX);
    int mouseDeltaY = (e->y() - this->lastMouseY);

    if (this->inputs.leftButton)
    {
        this->scene->camera->rotation.x = this->lastRotation.x - mouseDeltaY * 0.1;
        this->scene->camera->rotation.y = this->lastRotation.y - mouseDeltaX * 0.1;
        QMetaObject::invokeMethod(this->settingsWindow, "updateValues", Qt::AutoConnection);
    }
    if (this->inputs.rightButton)
    {
        Vector3d up(0.0, mouseDeltaY * 0.01, 0.0);
        Vector3d right(mouseDeltaX * 0.01, 0.0, 0.0);
        up.rotation(this->scene->camera->rotation);
        right.rotation(this->scene->camera->rotation);
        this->scene->camera->position = this->lastPosition + up - right;
        QMetaObject::invokeMethod(this->settingsWindow, "updateValues", Qt::AutoConnection);
    }
}

void GLWidgetOpenGL::wheelEvent(QWheelEvent *e)
{
    Vector3d forward(0.0, 0.0, 1.0);

    forward.rotation(this->scene->camera->rotation);
    if (e->angleDelta().ry() > 0)
        this->scene->camera->position -= forward;
    else if (e->angleDelta().ry() < 0)
        this->scene->camera->position += forward;
    QMetaObject::invokeMethod(this->settingsWindow, "updateValues", Qt::AutoConnection);
}

void GLWidgetOpenGL::setSettingsWindow(SettingsWindow *settingsWindow)
{
    this->settingsWindow = settingsWindow;
}

void GLWidgetOpenGL::setScene(Scene *scene)
{
    this->scene = scene;
}

void GLWidgetOpenGL::init()
{
    this->vertices.clear();
    this->normals.clear();
    if (this->indices)
        delete [] this->indices;
    this->indices_size = 0;
    for (size_t obj_i = 0; obj_i < this->scene->mesh.objs.size(); ++obj_i)
    {
        for (size_t face_i = 0; face_i < this->scene->mesh.objs[obj_i]->faces3.size(); ++face_i)
        {
            for (int i = 0; i < 3; ++i)
            {
                size_t verticeIndex = this->scene->mesh.objs[obj_i]->faces3[face_i].indexV[i];
                size_t normalIndex = this->scene->mesh.objs[obj_i]->faces3[face_i].indexVn[i];
                this->vertices.push_back(this->scene->mesh.vertices.v[verticeIndex-1]);
                this->normals.push_back(this->scene->mesh.vertices.vn[normalIndex-1]);
                indices_size++;
            }
        }
    }

    this->indices = new uint[indices_size];
    for (size_t i = 0; i < this->indices_size; ++i)
        this->indices[i] = i;

    if(glIsBuffer(vbo_vertices_id) == GL_TRUE)
        glDeleteBuffers(1, &vbo_vertices_id);
    glGenBuffers(1, &this->vbo_vertices_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertices_id);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vector3d), &this->vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(glIsBuffer(vbo_normals_id) == GL_TRUE)
        glDeleteBuffers(1, &vbo_normals_id);
    glGenBuffers(1, &this->vbo_normals_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_normals_id);
    glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(Vector3d), &this->normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(glIsBuffer(vbo_indices_id) == GL_TRUE)
        glDeleteBuffers(1, &vbo_indices_id);
    glGenBuffers(1, &this->vbo_indices_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo_indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_size * sizeof(uint), this->indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLWidgetOpenGL::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidgetOpenGL::resizeGL(int width, int height)
{
    static_cast<void>(width);
    static_cast<void>(height);
}

void GLWidgetOpenGL::paintGL()
{
    this->deltaTime = this->frame_time.elapsed() / 1000.0;
    this->frame_time.start();

    double ratio = qMin(static_cast<double>(this->width())/static_cast<double>(this->scene->camera->width),
                        static_cast<double>(this->height())/static_cast<double>(this->scene->camera->height));
    GLint width = static_cast<GLint>(this->scene->camera->width*ratio), height = static_cast<GLint>(this->scene->camera->height*ratio);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this->scene->camera->FOV, this->scene->camera->aspectRatio, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport((this->width()-width)/2, (this->height()-height)/2, width, height);
    glRotated(this->scene->camera->rotation.x, 1.0, 0.0, 0.0);
    glRotated(this->scene->camera->rotation.y, 0.0, 1.0, 0.0);
    glRotated(this->scene->camera->rotation.z, 0.0, 0.0, 1.0);
    glTranslated(-this->scene->camera->position.x, -this->scene->camera->position.y, -this->scene->camera->position.z);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertices_id);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_normals_id);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_DOUBLE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo_indices_id);
    glDrawElements(GL_TRIANGLES, this->indices_size, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLWidgetOpenGL::update_timeout()
{
    this->update();
}
