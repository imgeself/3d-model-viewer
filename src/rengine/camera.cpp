#include "camera.h"

glm::vec3 pos(0.0f, 0.0f, 2.5f);
glm::vec3 forward(0.0f, 0.0f, -1.0f);
glm::vec3 up(0.0f, 1.0f, 0.0f);
glm::vec3 right(1.0f, 0.0f, 0.0f);

void Camera::move(CameraDirection dir, float speed)
{
  switch (dir) {
      case FORWARD:
        pos += forward * speed;
        break;
      case BACKWARD:
        pos -= forward * speed;
        break;
      case UPWARD:
        pos += up * speed;
        break;
      case DOWNWARD:
        pos -= up * speed;
        break;
      case RIGHTWARD:
        pos += glm::normalize(glm::cross(forward, up)) * speed;
        break;
      case LEFTWARD:
        pos -= glm::normalize(glm::cross(forward, up)) * speed;
        break;
      default:
        break;
  }
}  

void Camera::reset()
{
    pos = glm::vec3(0.0f, 0.0f, 2.5f);
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

