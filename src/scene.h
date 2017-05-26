#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "model.h"
#include "shader.h"

struct Scene {
  std::vector<Model> mModels;
};

#endif
