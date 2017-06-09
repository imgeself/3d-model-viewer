#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/config.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Model {

public:
  Model(std::string filename);
  ~Model();

  std::vector<Mesh> mMeshes;
  void rotateHorizontally(float angle);
  void rotateVertically(float angle);
  glm::mat4 getModelMatrix();
  
private:
  std::string mCurrentFolder;
  glm::mat4 mModelMatrix;
  Mesh loadMesh(const aiMesh*, const aiScene*);
  void iterateNode(const aiNode*, const aiScene*);
  std::vector<Texture> getTextures(const aiMaterial *material, TextureType textureType);
};

#endif
