#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/config.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Model {

public:
  Model(const char* filename);
  ~Model();

  std::vector<Mesh> mMeshes;
  void rotateHorizontally(float angle);
  void rotateVertically(float angle);
  glm::mat4 getModelMatrix();
  
private:
  glm::mat4 modelMatrix;
  Mesh loadMesh(const aiMesh*, const aiScene*);
  void iterateNode(const aiNode*, const aiScene*);
};

#endif
