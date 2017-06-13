#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

enum CameraDirection {
  FORWARD,
  BACKWARD,
  DOWNWARD,
  UPWARD,
  RIGHTWARD,
  LEFTWARD
};  

class Camera {
public:
  void move(CameraDirection dir, float speed);
  
  void reset();
  glm::vec3 getTarget();
  glm::vec3 getUp();
  glm::vec3 getPosition();
};

#endif
