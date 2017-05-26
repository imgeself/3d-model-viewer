#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {

public:
  Model(const char* filename);
  ~Model();

  std::vector<Mesh> mMeshes;

private:
  Mesh loadMesh(aiMesh*, const aiScene*);
  void iterateNode(aiNode*, const aiScene*);
};

#endif
