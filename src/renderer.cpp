#include "renderer.h"
#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
{
  
}

Renderer::~Renderer()
{
  //glDeleteProgram(mShader.mProgram);
  
  for (Model &model : mActiveScene.mModels) {
    for (Mesh &mesh : model.mMeshes) {
      glDeleteVertexArrays(1, &mesh.mVAO);
      glDeleteBuffers(1, &mesh.mVBO);
      glDeleteBuffers(1, &mesh.mEBO);
    }
  }
  
}

void Renderer::setActiveScene(Scene &scene)
{
  mActiveScene = scene;
}  

void Renderer::prepare()
{

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::cout <<  "Error at initializing glew.\n" << glewGetErrorString(err) << "\n";
  }
 
  Shader shader;
  glUseProgram(shader.mProgram);

  for (Model &model : mActiveScene.mModels) {
    for (Mesh &mesh : model.mMeshes) {
      glGenVertexArrays(1, &mesh.mVAO);
      glGenBuffers(1, &mesh.mVBO);
      glGenBuffers(1, &mesh.mEBO);

      glBindVertexArray(mesh.mVAO);

      glBindBuffer(GL_ARRAY_BUFFER, mesh.mVBO);
      glBufferData(GL_ARRAY_BUFFER, mesh.mVertices.size() * sizeof(Vertex), &mesh.mVertices[0], GL_STATIC_DRAW);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.mEBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.mIndices.size() * sizeof(GLuint), &mesh.mIndices[0], GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));

      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
      
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, nor));

      glBindVertexArray(0);

    }
  }

}

void Renderer::render()
{
  glClearColor(0.2f,0.2f,0.2f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //glUseProgram(mShader.mProgram);
  
  for (Model &model : mActiveScene.mModels) {
    for (Mesh &mesh : model.mMeshes) {
      glBindVertexArray(mesh.mVAO);
      glDrawElements(GL_TRIANGLES, mesh.mIndices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }
  }

  //glUseProgram(0);
}  
  
void Renderer::resize(int width, int height)
{
  glViewport(0, 0, width, height);
}  
