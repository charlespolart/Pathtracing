#include "Camera.h"

Camera::Camera() :
    position(0.0, 0.0, 3.0)
{
    this->setWidth(480);
    this->setHeight(360);
    this->setFOV(60);
}

void Camera::setWidth(int width)
{
    this->width = width;
    this->aspectRatio = std::max(this->width, this->height) / static_cast<double>(std::min(this->width, this->height));
    this->inv = this->width < this->height;
}

void Camera::setHeight(int height)
{
    this->height= height;
    this->aspectRatio = std::max(this->width, this->height) / static_cast<double>(std::min(this->width, this->height));
    this->inv = this->width < this->height;
}

void Camera::setFOV(int FOV)
{
    this->FOV = FOV;
    this->scale = std::tan(this->FOV/2.0 * M_PI / 180.0);
}

Ray Camera::initRay(double x, double y) const
{
    Vector3d direction;

    if (!inv)
    {
        direction.x = (2.0 * ((x + 0.5) / this->width) - 1.0) * this->scale * this->aspectRatio;
        direction.y = (1.0 - 2.0 * ((y + 0.5) / this->height)) * this->scale;
    }
    else
    {
        direction.x = (2.0 * ((x + 0.5) / this->width) - 1.0) * this->scale;
        direction.y = (1.0 - 2.0 * ((y + 0.5) / this->height)) * this->scale * this->aspectRatio;
    }
    direction.z = -1.0;
    direction.rotation(this->rotation);
    return (Ray(this->position, direction));
}
