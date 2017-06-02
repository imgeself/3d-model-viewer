#include "model.h"
#include "mesh.h"
#include <iostream>
#include <vector>

Model::Model(std::string filename)
{ 
  Assimp::Importer import;
  import.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE,1);
  const aiScene* scene = import.ReadFile(filename, aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes | aiProcess_PreTransformVertices | aiProcess_Triangulate | aiProcess_FlipUVs);
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
  {
    std::cout << "Error at loading model: " << import.GetErrorString() << "\n";
    return;
  }

  mCurrentFolder = filename.substr(0, filename.find_last_of("/"));

  iterateNode(scene->mRootNode, scene);
}

Model::~Model()
{

}

void Model::iterateNode(const aiNode *node, const aiScene *scene)
{

  for (int i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
    mMeshes.push_back(loadMesh(mesh, scene));			
  }

  for (int i = 0; i < node->mNumChildren; i++) {
    iterateNode(node->mChildren[i], scene);
  }

}

Mesh Model::loadMesh(const aiMesh *asMesh, const aiScene *scene)
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

    if (asMesh->mColors[0]) {
      glm::vec4 vect4;
      vect4.x = asMesh->mColors[0][i].r;
      vect4.y = asMesh->mColors[0][i].g;
      vect4.z = asMesh->mColors[0][i].b;
      vect4.w = asMesh->mColors[0][i].a;

      vertex.color = vect4;
    } else {
      vertex.color = glm::vec4(1.0f);
    }

    if (asMesh->mTextureCoords[0]) {
      glm::vec2 vect2;
      vect2.x = asMesh->mTextureCoords[0][i].x;
      vect2.y = asMesh->mTextureCoords[0][i].y;
      vertex.texCoords = vect2;
    } else {
      vertex.texCoords = glm::vec2(0.0f, 0.0f);
    }  
    
    vertices.push_back(vertex);
  }

  std::vector<GLuint> indices;

  for (int i = 0; i < asMesh->mNumFaces; i++) {
    aiFace face = asMesh->mFaces[i];
    for (int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  std::vector<Texture> textures;

  if (asMesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[asMesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = getTextures(material, DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = getTextures(material, SPECULAR);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  }
  
  

  Mesh mesh;
  mesh.mVertices = vertices;
  mesh.mIndices = indices;
  mesh.mTextures = textures;

  return mesh;
  
}

std::vector<Texture> Model::getTextures(const aiMaterial *material, TextureType textureType)
{
  aiTextureType type;
  switch (textureType) {
  case DIFFUSE:
    type = aiTextureType_DIFFUSE;
    break;
  case SPECULAR:
    type = aiTextureType_SPECULAR;
    break;
  }

  std::vector<Texture> textures;
  for (int i = 0; i < material->GetTextureCount(type); i++) {
    aiString aiStr;
    material->GetTexture(type, i, &aiStr);

    // aiString and std string no compatible. We convert aiString to c string then convert to std string.
    std::string path = mCurrentFolder + "/" + std::string(aiStr.C_Str());
    Texture texture(path.c_str(), textureType);
    textures.push_back(texture);
    
  }

  return textures;
}  

void Model::rotateHorizontally(float angle)
{
  mModelMatrix = glm::rotate(mModelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Model::rotateVertically(float angle)
{
  mModelMatrix = glm::rotate(mModelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));  
}  

glm::mat4 Model::getModelMatrix()
{
  return mModelMatrix;
}  
