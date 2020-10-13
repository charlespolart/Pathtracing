#include "Engine.h"

Engine::Engine(QMainWindow *mainwindow) :
    _mainwindow(mainwindow),
    _rendering(false),
    _pause(false),
    _exit(false),
    _scene(new Scene()),
    _pixels(nullptr),
    _pixelsData(nullptr),
    _engine_thread(std::thread(&Engine::render, this))
{
    std::srand(std::time(NULL));
}

Engine::~Engine()
{
    this->_engine_thread.join();
    delete this->_scene;
}

Scene *Engine::getScene()
{
    return (this->_scene);
}

void Engine::setPixels(GLubyte *pixels)
{
    this->_pixels = pixels;
}

void Engine::start()
{
    this->_rendering = true;
}

void Engine::stop()
{
    this->_rendering = false;
}

void Engine::pause()
{
    this->_pause = !this->_pause;
}

void Engine::exit()
{
    this->_exit = true;
}

bool Engine::isRendering() const
{
    return (this->_rendering);
}

bool Engine::isPaused() const
{
    return (this->_pause);
}

void Engine::putPixel(int x, int y, const Vector3d &c)
{
    Vector3d color = c;
    double max = color.max();

    if (max > 1.0)
        color /= max;
    this->_pixels[(x + y*this->_scene->_camera->_width)*3] = static_cast<GLubyte>(color.x*255.0);
    this->_pixels[(x + y*this->_scene->_camera->_width)*3 + 1] = static_cast<GLubyte>(color.y*255.0);
    this->_pixels[(x + y*this->_scene->_camera->_width)*3 + 2] = static_cast<GLubyte>(color.z*255.0);
}

void Engine::drawPathtracing(int *current, int *sample)
{
    int y = 0;

    while (this->_rendering)
    {
        this->_render_mutex.lock();
        if (*current >= this->_scene->_camera->_height)
        {
            if (this->_scene->_samples ? *sample >= this->_scene->_samples : 0)
            {
                this->_render_mutex.unlock();
                return;
            }
            *current = 0;
            (*sample)++;
            int percent = static_cast<double>(*sample)/this->_scene->_samples*100.0;
            QMetaObject::invokeMethod(this->_mainwindow, "writeTerminal", Qt::AutoConnection, Q_ARG(QString, "Sample ["+QString::number(*sample)+(this->_scene->_samples ? "/"+QString::number(this->_scene->_samples)+"] "+QString::number(percent)+"%" : "]")),Q_ARG(bool, true));
            QMetaObject::invokeMethod(this->_mainwindow, "progressBar", Qt::AutoConnection, Q_ARG(int, percent));
        }
        y = *current;
        (*current)++;
        this->_render_mutex.unlock();
        for (int x = 0; x < this->_scene->_camera->_width; ++x)
        {
            pixelData_t *pixelData = &this->_pixelsData[x+y*this->_scene->_camera->_width];
            double xRand = Rand::uniform_random(0.0, 1.0);
            double yRand = Rand::uniform_random(0.0, 1.0);
            Ray ray = this->_scene->_camera->initRay(x + xRand, y + yRand);
            Vector3d color = Pathtracing::render(ray, this->_scene);

            if (color != 0.0)
            {
                pixelData->color = pixelData->color.progressiveAverage(color, pixelData->samples);
                pixelData->samples++;
            }
            this->putPixel(x, y, pixelData->color);
            if (this->_pause)
            {
                this->_render_mutex.lock();
                if (this->_pause)
                {
                    this->_benchmark.pause();
                    while (this->_pause && this->_rendering)
                        Sleep(10);
                    this->_benchmark.resume();
                }
                this->_render_mutex.unlock();
            }
        }
    }
}

void Engine::render()
{
    std::vector<std::thread> render_threads;
    int current = 0;
    int sample = 1;

    while (!this->_exit)
    {
        if (this->_rendering)
        {
            _benchmark.start();
            render_threads.clear();
            current = 0;
            sample = 1;
            if (this->_pixelsData)
                delete [] this->_pixelsData;
            this->_pixelsData = new pixelData_t[this->_scene->_camera->_width * this->_scene->_camera->_height];
            QMetaObject::invokeMethod(this->_mainwindow, "writeTerminal", Qt::AutoConnection,
                                      Q_ARG(QString, "Sample ["+QString::number(sample)+(this->_scene->_samples ? "/"+QString::number(this->_scene->_samples)+"] 0%" : "]")),
                                      Q_ARG(bool, false));
            for (size_t i = 0; i < this->_scene->_totalThreads; ++i)
                render_threads.emplace_back(std::thread(&Engine::drawPathtracing, this, &current, &sample));
            for (size_t i = 0; i < this->_scene->_totalThreads; ++i)
                render_threads[i].join();
            this->_rendering = false;
            this->_pause = false;
            QMetaObject::invokeMethod(this->_mainwindow, "writeTerminal", Qt::AutoConnection, Q_ARG(QString, QString::fromStdString(_benchmark.getBenchTime().fullTime_str)));
            QMetaObject::invokeMethod(this->_mainwindow, "on_stop_pushButton_clicked", Qt::AutoConnection);
        }
        Sleep(10);
    }
}
