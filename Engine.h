#ifndef ENGINE_H
#define ENGINE_H

#include <thread>
#include <mutex>
#include <QtOpenGL>
#include "Scene.h"
#include "Camera.h"
#include "Pathtracing.h"
#include "Benchmark.h"

class Engine
{
public:
    Engine(QMainWindow *mainwindow);
    ~Engine();

public:
    Scene *getScene();
    void setPixels(GLubyte *pixels);

    void start();
    void stop();
    void pause();
    void clean();

private:
    void putPixel(int x, int y, const Vector3d &c);
    Vector3d raytracing(const Ray &);
    Vector3d pathtracing(const Ray &);
    void drawRaytracing(int *current);
    void drawPathtracing(int *current);
    void displayRenderTime(long long time);
    void render();

private:
    QMainWindow *mainwindow;
    bool rendering;
    bool exit;
    Scene *scene;
    GLubyte *pixels;
    std::mutex render_mutex;
    std::thread engine_thread;
};

#endif // ENGINE_H
