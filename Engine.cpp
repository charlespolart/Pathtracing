#include "Engine.h"

Engine::Engine(QMainWindow *mainwindow) :
    mainwindow(mainwindow),
    rendering(false),
    exit(false),
    scene(new Scene()),
    pixels(nullptr),
    pixelsData(nullptr),
    engine_thread(std::thread(&Engine::render, this))
{
    std::srand(std::time(NULL));
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

void Engine::drawPathtracing(int *current, int *sample)
{
    int y = 0;

    while (this->rendering)
    {
        this->render_mutex.lock();
        if (*current >= this->scene->camera->height)
        {
            if (this->scene->samples ? *sample >= this->scene->samples : 0)
            {
                this->render_mutex.unlock();
                return;
            }
            *current = 0;
            (*sample)++;
            QMetaObject::invokeMethod(this->mainwindow, "writeTerminal", Qt::AutoConnection, Q_ARG(QString, "Sample ["+QString::number(*sample)+(this->scene->samples ? "/"+QString::number(this->scene->samples)+"]" : "]")), Q_ARG(bool, true));
        }
        y = *current;
        (*current)++;
        this->render_mutex.unlock();
        for (int x = 0; x < this->scene->camera->width; ++x)
        {
            double xRand = static_cast<double>(std::rand()) / RAND_MAX, yRand = static_cast<double>(std::rand()) / RAND_MAX;
            Vector3d color = Pathtracing::render(this->scene->camera->initRay(x + xRand, y + yRand), this->scene);
            if (color != 0)
                this->pixelsData[x+y*this->scene->camera->width].color += color;
            this->putPixel(x, y, this->pixelsData[x+y*this->scene->camera->width].color / this->pixelsData[x+y*this->scene->camera->width].samples);
            if (color != 0)
                this->pixelsData[x+y*this->scene->camera->width].samples++;
        }
    }
}

void Engine::render()
{
    std::vector<std::thread> render_threads;
    Benchmark benchmark;
    int current = 0;
    int sample = 1;

    while (!this->exit)
    {
        if (this->rendering)
        {
            benchmark.start();
            render_threads.clear();
            current = 0;
            sample = 1;
            if (this->pixelsData)
                delete [] this->pixelsData;
            this->pixelsData = new pixelData_t[this->scene->camera->width * this->scene->camera->height];
            QMetaObject::invokeMethod(this->mainwindow, "writeTerminal", Qt::AutoConnection, Q_ARG(QString, "Sample ["+QString::number(sample)+(this->scene->samples ? "/"+QString::number(this->scene->samples)+"]" : "]")), Q_ARG(bool, false));
            for (size_t i = 0; i < this->scene->totalThreads; ++i)
                render_threads.emplace_back(std::thread(&Engine::drawPathtracing, this, &current, &sample));
            for (size_t i = 0; i < this->scene->totalThreads; ++i)
                render_threads[i].join();
            this->rendering = false;
            QMetaObject::invokeMethod(this->mainwindow, "writeTerminal", Qt::AutoConnection, Q_ARG(QString, QString::fromStdString(benchmark.getBenchTime().fullTime_str)));
            QMetaObject::invokeMethod(this->mainwindow, "on_stop_pushButton_clicked", Qt::AutoConnection);
        }
        Sleep(10);
    }
}
