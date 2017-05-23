#ifndef MESH_H
#define MESH_H

#include "shader.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

struct Vertex {
  glm::vec3 pos;
  glm::vec3 nor;
};

struct Texture {
  GLuint id;
  char *type;
}; 


class Mesh {

public:
  Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indicies, Shader shader);
  ~Mesh();

  void draw();

private:
  std::vector<Vertex> vertices;
  std::vector<GLuint> indicies;
  
  Shader shader;
  
  GLuint VAO, VBO, EBO;
  void prepareMesh();
  void releaseMesh();
};

#endif
