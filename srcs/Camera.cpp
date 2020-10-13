#include "Camera.h"

Camera::Camera() :
    _position(0.0, 0.0, 3.0)
{
    this->setWidth(480);
    this->setHeight(360);
    this->setFOV(60);
}

void Camera::setWidth(int width)
{
    this->_width = width;
    this->_aspectRatio = std::max(this->_width, this->_height) / static_cast<double>(std::min(this->_width, this->_height));
    this->_inv = this->_width < this->_height;
}

void Camera::setHeight(int height)
{
    this->_height= height;
    this->_aspectRatio = std::max(this->_width, this->_height) / static_cast<double>(std::min(this->_width, this->_height));
    this->_inv = this->_width < this->_height;
}

void Camera::setFOV(int FOV)
{
    this->_FOV = FOV;
    this->_scale = std::tan(this->_FOV/2.0 * M_PI / 180.0);
}

Ray Camera::initRay(double x, double y) const
{
    Vector3d direction;

    if (!_inv)
    {
        direction.x = (2.0 * ((x + 0.5) / this->_width) - 1.0) * this->_scale * this->_aspectRatio;
        direction.y = (1.0 - 2.0 * ((y + 0.5) / this->_height)) * this->_scale;
    }
    else
    {
        direction.x = (2.0 * ((x + 0.5) / this->_width) - 1.0) * this->_scale;
        direction.y = (1.0 - 2.0 * ((y + 0.5) / this->_height)) * this->_scale * this->_aspectRatio;
    }
    direction.z = -1.0;
    return (Ray(this->_position, direction.rotation(this->_rotation)));
}
