#include "model.h"
#include "mesh.h"
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

#define AI_CONFIG_PP_PTV_NORMALIZE   "PP_PTV_NORMALIZE"


Model::Model(const char *filename)
{
  Assimp::Importer import;
  const aiScene* scene = import.ReadFile(filename, aiProcess_OptimizeMeshes | aiProcess_PreTransformVertices | aiProcess_Triangulate);
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
  {
    std::cout << "Error at loading model: " << import.GetErrorString() << "\n";
    return;
  }

  iterateNode(scene->mRootNode, scene);
}

Model::~Model()
{

}

void Model::iterateNode(aiNode *node, const aiScene *scene)
{

  for (int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
    this->mMeshes.push_back(loadMesh(mesh, scene));			
  }

  for (int i = 0; i < node->mNumChildren; i++) {
    iterateNode(node->mChildren[i], scene);
  }

}

Mesh Model::loadMesh(aiMesh *asMesh, const aiScene *scene)
{
  std::vector<Vertex> vertices;

  for (int i = 0; i < asMesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 vect3;
    vect3.x = asMesh->mVertices[i].x;
    vect3.y = asMesh->mVertices[i].y;
    vect3.z = asMesh->mVertices[i].z;
    vertex.pos = vect3;

    vect3.x = asMesh->mNormals[i].x;
    vect3.y = asMesh->mNormals[i].y;
    vect3.z = asMesh->mNormals[i].z;
    vertex.nor = vect3;

    vertices.push_back(vertex);
  }

  std::vector<GLuint> indices;

  for (int i = 0; i < asMesh->mNumFaces; i++) {
    aiFace face = asMesh->mFaces[i];
    for (int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  Mesh mesh;
  mesh.mVertices = vertices;
  mesh.mIndices = indices;

  return mesh;
  
}  
