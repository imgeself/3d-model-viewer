#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <memory>

struct Vertex {
  glm::vec3 pos;
  glm::vec3 nor;
};

struct Mesh {

  std::vector<Vertex> mVertices;
  std::vector<GLuint> mIndices;
  
  GLuint mVAO;
  GLuint mVBO;
  GLuint mEBO;
  
};

#endif
