#include "Engine.h"

Engine::Engine(QMainWindow *mainwindow) :
    mainwindow(mainwindow),
    rendering(false),
    exit(false),
    scene(new Scene()),
    pixels(nullptr),
    engine_thread(std::thread(&Engine::render, this))
{
}

Engine::~Engine()
{
    this->engine_thread.join();
    delete this->scene;
}

Scene *Engine::getScene()
{
    return (this->scene);
}

void Engine::setPixels(GLubyte *pixels)
{
    this->pixels = pixels;
}

void Engine::start()
{
    this->rendering = true;
}

void Engine::stop()
{
    this->rendering = false;
}

void Engine::pause()
{
}

void Engine::clean()
{
    this->exit = true;
}

void Engine::putPixel(int x, int y, const Vector3d &c)
{
    Vector3d color = c;
    double max = std::max(std::max(color.x, color.y), color.z);

    if (max > 1.0)
        color /= max;
    this->pixels[(x + y*this->scene->camera->width)*3] = static_cast<GLubyte>(color.x*255.0);
    this->pixels[(x + y*this->scene->camera->width)*3 + 1] = static_cast<GLubyte>(color.y*255.0);
    this->pixels[(x + y*this->scene->camera->width)*3 + 2] = static_cast<GLubyte>(color.z*255.0);
}

void Engine::drawPathtracing(int *current)
{
    int y = 0;

    while (this->rendering)
    {
        this->render_mutex.lock();
        if (*current >= this->scene->camera->height)
        {
            this->render_mutex.unlock();
            break;
        }
        y = *current;
        (*current)++;
        this->render_mutex.unlock();
        for (int x = 0; x < this->scene->camera->width; ++x)
        {
            this->putPixel(x, y, Pathtracing::render(this->scene->camera->initRay(x, y), this->scene, Vector2i(x, y)));
        }
    }
}

/*void Engine::drawPathtracing(int *current)
{
    int y = 0;

    while (this->rendering)
    {
        this->render_mutex.lock();
        if (*current >= this->scene->camera->height)
        {
            *current = 0;
        }
        y = *current;
        (*current)++;
        this->render_mutex.unlock();
        for (int x = 0; x < this->scene->camera->width; ++x)
        {
            this->putPixel(x, y, Pathtracing::render(this->scene->camera->initRay(x, y), this->scene, Vector2i(x, y)));
        }
    }
}*/

void Engine::render()
{
    std::vector<std::thread> render_threads;
    Benchmark benchmark;
    int current = 0;

    while (!this->exit)
    {
        if (this->rendering)
        {
            benchmark.start();
            render_threads.clear();
            current = 0;
            for (size_t i = 0; i < this->scene->totalThreads; ++i)
                render_threads.emplace_back(std::thread(&Engine::drawPathtracing, this, &current));
            for (size_t i = 0; i < this->scene->totalThreads; ++i)
                render_threads[i].join();
            this->rendering = false;
            QMetaObject::invokeMethod(this->mainwindow, "writeTerminal", Qt::AutoConnection, Q_ARG(QString, QString::fromStdString(benchmark.getBenchTime().fullTime_str)));
            QMetaObject::invokeMethod(this->mainwindow, "disableOptions", Qt::AutoConnection, Q_ARG(bool, false));
        }
        Sleep(10);
    }
}
