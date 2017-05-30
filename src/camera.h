#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
public:
  void moveForward(float speed = 1);
  void moveBackward(float speed = 1);

  glm::vec3 getTarget();
  glm::vec3 getUp();
  glm::vec3 getPosition();
};

#endif
