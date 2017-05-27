#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/config.h>

class Model {

public:
  Model(const char* filename);
  ~Model();

  std::vector<Mesh> mMeshes;

private:
  Mesh loadMesh(const aiMesh*, const aiScene*);
  void iterateNode(const aiNode*, const aiScene*);
};

#endif
