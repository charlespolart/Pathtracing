#ifndef ENGINE_H
#define ENGINE_H

#include <thread>
#include <mutex>
#include <QtOpenGL>
#include "Scene.h"
#include "Camera.h"
#include "Pathtracing.h"
#include "Benchmark.h"

struct pixelData_t
{
    Vector3d color;
    int samples = 1;
};

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
    void drawPathtracing(int *current, int *sample);
    void displayRenderTime(long long time);
    void render();

private:
    QMainWindow *mainwindow;
    bool rendering;
    bool exit;
    Scene *scene;
    GLubyte *pixels;
    pixelData_t *pixelsData;
    std::mutex render_mutex;
    std::thread engine_thread;
};

#endif // ENGINE_H
