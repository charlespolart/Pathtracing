#include "GLWidgetOpenGL.h"

GLWidgetOpenGL::GLWidgetOpenGL(QWidget *parent) :
    QOpenGLWidget(parent),
    _scene(nullptr),
    _rendering(true),
    _deltaTime(0.0),
    _lastMouseX(0),
    _lastMouseY(0),
    _indices(nullptr),
    _indices_size(0),
    _vbo_vertices_id(0),
    _vbo_normals_id(0),
    _vbo_indices_id(0)
{
    connect(&this->_update_timer, SIGNAL(timeout()), this, SLOT(update_timeout()));
    this->_update_timer.start(1000/FPS);
}

GLWidgetOpenGL::~GLWidgetOpenGL()
{
    if(glIsBuffer(_vbo_vertices_id) == GL_TRUE)
        glDeleteBuffers(1, &_vbo_vertices_id);
    if(glIsBuffer(_vbo_normals_id) == GL_TRUE)
        glDeleteBuffers(1, &_vbo_normals_id);
    if(glIsBuffer(_vbo_indices_id) == GL_TRUE)
        glDeleteBuffers(1, &_vbo_indices_id);
    if (this->_indices)
        delete [] this->_indices;
}

void GLWidgetOpenGL::mousePressEvent(QMouseEvent *e)
{
    this->_lastMouseX = e->x();
    this->_lastMouseY = e->y();
    if (e->button() == Qt::LeftButton)
    {
        this->_lastRotation = this->_scene->_camera->_rotation;
        this->_inputs.leftButton = true;
    }
    if (e->button() == Qt::RightButton)
    {
        this->_lastPosition = this->_scene->_camera->_position;
        this->_inputs.rightButton = true;
    }
}

void GLWidgetOpenGL::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        this->_inputs.leftButton = false;
    if (e->button() == Qt::RightButton)
        this->_inputs.rightButton = false;
}

void GLWidgetOpenGL::mouseMoveEvent(QMouseEvent *e)
{
    int mouseDeltaX = (e->x() - this->_lastMouseX);
    int mouseDeltaY = (e->y() - this->_lastMouseY);

    if (this->_inputs.leftButton)
    {
        this->_scene->_camera->_rotation.x = this->_lastRotation.x - mouseDeltaY * 0.1;
        this->_scene->_camera->_rotation.y = this->_lastRotation.y - mouseDeltaX * 0.1;
        QMetaObject::invokeMethod(this->_settingsWindow, "updateValues", Qt::AutoConnection);
    }
    if (this->_inputs.rightButton)
    {
        Vector3d up = Vector3d(0.0, mouseDeltaY * 0.01, 0.0).rotation(this->_scene->_camera->_rotation);
        Vector3d right = Vector3d(mouseDeltaX * 0.01, 0.0, 0.0).rotation(this->_scene->_camera->_rotation);
        this->_scene->_camera->_position = this->_lastPosition + up - right;
        QMetaObject::invokeMethod(this->_settingsWindow, "updateValues", Qt::AutoConnection);
    }
}

void GLWidgetOpenGL::wheelEvent(QWheelEvent *e)
{
    Vector3d forward = Vector3d(0.0, 0.0, 1.0).rotation(this->_scene->_camera->_rotation);

    if (e->angleDelta().ry() > 0)
        this->_scene->_camera->_position -= forward;
    if (e->angleDelta().ry() < 0)
        this->_scene->_camera->_position += forward;
    QMetaObject::invokeMethod(this->_settingsWindow, "updateValues", Qt::AutoConnection);
}

void GLWidgetOpenGL::setSettingsWindow(SettingsWindow *settingsWindow)
{
    this->_settingsWindow = settingsWindow;
}

void GLWidgetOpenGL::setScene(Scene *scene)
{
    this->_scene = scene;
}

void GLWidgetOpenGL::pauseRendering(bool status)
{
    this->_rendering = !status;
    this->setDisabled(status);
}

void GLWidgetOpenGL::init()
{
    this->_vertices.clear();
    this->_normals.clear();
    if (this->_indices)
        delete [] this->_indices;
    this->_indices_size = 0;
    for (size_t obj_i = 0; obj_i < this->_scene->_mesh.objs.size(); ++obj_i)
    {
        for (size_t face_i = 0; face_i < this->_scene->_mesh.objs[obj_i]->_faces3.size(); ++face_i)
        {
            for (int i = 0; i < 3; ++i)
            {
                size_t verticeIndex = this->_scene->_mesh.objs[obj_i]->_faces3[face_i].indexV[i];
                size_t normalIndex = this->_scene->_mesh.objs[obj_i]->_faces3[face_i].indexVn[i];
                if (!(verticeIndex-1 < 0 || verticeIndex-1 >= this->_scene->_mesh.vertices.v.size() ||
                      normalIndex-1 < 0 || normalIndex-1 >= this->_scene->_mesh.vertices.vn.size()))
                {
                    this->_vertices.push_back(this->_scene->_mesh.vertices.v[verticeIndex-1]);
                    this->_normals.push_back(this->_scene->_mesh.vertices.vn[normalIndex-1]);
                    _indices_size++;
                }
            }
        }
    }

    this->_indices = new uint[this->_indices_size];
    for (size_t i = 0; i < this->_indices_size; ++i)
        this->_indices[i] = i;

    if(glIsBuffer(this->_vbo_vertices_id) == GL_TRUE)
        glDeleteBuffers(1, &this->_vbo_vertices_id);
    glGenBuffers(1, &this->_vbo_vertices_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_vertices_id);
    glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(Vector3d), &this->_vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(glIsBuffer(this->_vbo_normals_id) == GL_TRUE)
        glDeleteBuffers(1, &this->_vbo_normals_id);
    glGenBuffers(1, &this->_vbo_normals_id);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_normals_id);
    glBufferData(GL_ARRAY_BUFFER, this->_normals.size() * sizeof(Vector3d), &this->_normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(glIsBuffer(this->_vbo_indices_id) == GL_TRUE)
        glDeleteBuffers(1, &this->_vbo_indices_id);
    glGenBuffers(1, &this->_vbo_indices_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo_indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices_size * sizeof(uint), this->_indices, GL_STATIC_DRAW);
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
    this->_deltaTime = this->_frame_time.elapsed() / 1000.0;
    this->_frame_time.start();

    double ratio = qMin(static_cast<double>(this->width())/static_cast<double>(this->_scene->_camera->_width),
                        static_cast<double>(this->height())/static_cast<double>(this->_scene->_camera->_height));
    GLint width = static_cast<GLint>(this->_scene->_camera->_width*ratio), height = static_cast<GLint>(this->_scene->_camera->_height*ratio);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(this->_scene->_camera->_FOV, this->_scene->_camera->_aspectRatio, 0.1, 100.0);
    glViewport((this->width()-width)/2, (this->height()-height)/2, width, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(this->_scene->_camera->_rotation.x, 1.0, 0.0, 0.0);
    glRotated(this->_scene->_camera->_rotation.y, 0.0, 1.0, 0.0);
    glRotated(this->_scene->_camera->_rotation.z, 0.0, 0.0, 1.0);
    glTranslated(-this->_scene->_camera->_position.x, -this->_scene->_camera->_position.y, -this->_scene->_camera->_position.z);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_vertices_id);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_normals_id);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_DOUBLE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo_indices_id);
    glDrawElements(GL_TRIANGLES, this->_indices_size, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLWidgetOpenGL::update_timeout()
{
    if (this->_rendering)
        this->update();
}
