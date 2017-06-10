#ifndef SCENE_H
#define SCENE_H

#include "model.h"
#include "shader.h"
#include "camera.h"

#include <glm/glm.hpp>

struct Light {
  glm::vec3 position;
  glm::vec3 color;

  float ambientStrength = 0.f;
};

struct Scene {
  Camera mainCamera;
  Light mainLight;
  Model *mainModel = nullptr;
};

#endif
