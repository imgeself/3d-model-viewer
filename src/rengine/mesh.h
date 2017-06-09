#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>

#include "texture.h"

struct Vertex {
  glm::vec3 pos;
  glm::vec4 color;
  glm::vec2 texCoords;
  glm::vec3 nor;
};

struct Mesh {

  std::vector<Vertex> mVertices;
  std::vector<GLuint> mIndices;
  std::vector<Texture> mTextures;
  
  GLuint mVAO;
  GLuint mVBO;
  GLuint mEBO;
  
};

#endif
