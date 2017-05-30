#include "camera.h"

glm::vec3 pos(0.0f, 0.0f, 2.5f);
glm::vec3 forward(0.0f, 0.0f, -1.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);

void Camera::moveForward(float speed)
{
  pos += forward * speed;
}

void Camera::moveBackward(float speed)
{
  pos -= forward * speed;
}

glm::vec3 Camera::getTarget()
{
  return pos + forward;
}

glm::vec3 Camera::getUp()
{
  return up;
}

glm::vec3 Camera::getPosition()
{
  return pos;
}

