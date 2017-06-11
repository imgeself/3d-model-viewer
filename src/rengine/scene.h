#ifndef SCENE_H
#define SCENE_H

#include "model.h"
#include "camera.h"

#include <glm/glm.hpp>

struct Light {
  glm::vec3 position{0.0f, 1.0f, 3.0f};
  glm::vec3 color{1.0f};

  float intensity = 1.0f;
  float ambientStrength = 0.3f;
  float specularStrength = 0.5f;
};

struct Scene {
  Camera mainCamera;
  Light mainLight;
  Model mainModel;
};

#endif
