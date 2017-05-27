#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "model.h"
#include "shader.h"

#include <glm/glm.hpp>

struct Light {
  glm::vec3 position;
  glm::vec3 color;

  float ambientStrength = 0.f;
};

struct Scene {
  Light mainLight;
  std::vector<Model> mModels;
};

#endif
