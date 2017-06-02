#include "renderer.h"
#include "shader.h"
#include <chrono>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint projLoc, modelLoc, viewLoc, inversedModelLoc, cameraPosLoc;
Shader shader;

Renderer::Renderer()
{
  
}

Renderer::~Renderer()
{
  
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
  glEnable(GL_DEPTH_TEST);
 
  //Shader have open gl functions. So we have to compile shaders after initilazing glew.
  shader.compileShadersAndProgram();
  
  glUseProgram(shader.mProgram);
  
 
  for (Mesh &mesh : mActiveScene.mModel->mMeshes) {
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
    
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);

    for (Texture &texture : mesh.mTextures) {
      texture.load();
    }

  }

  
  Light light;
  light.position = glm::vec3(0.0f, 1.0f, 3.0f);
  light.color = glm::vec3(1.5f);
  light.ambientStrength = 0.5f;

  mActiveScene.mainLight = light;

  //We put this code in prepare bu later we might put in render
  GLuint lightPosLoc = glGetUniformLocation(shader.mProgram, "lightPos");
  GLuint lightColorLoc = glGetUniformLocation(shader.mProgram, "lightColor");
  GLuint ambStrenLoc = glGetUniformLocation(shader.mProgram, "ambientStrength");

  glUniform3fv(lightPosLoc, 1, glm::value_ptr(mActiveScene.mainLight.position));
  glUniform3fv(lightColorLoc, 1, glm::value_ptr(mActiveScene.mainLight.color));
  glUniform1f(ambStrenLoc, mActiveScene.mainLight.ambientStrength);

  viewLoc = glGetUniformLocation(shader.mProgram, "view");
  modelLoc = glGetUniformLocation(shader.mProgram, "model");
  projLoc = glGetUniformLocation(shader.mProgram, "projection");
  inversedModelLoc = glGetUniformLocation(shader.mProgram, "inversedModel");
  cameraPosLoc = glGetUniformLocation(shader.mProgram, "cameraPos");
}


void Renderer::render()
{
  glClearColor(0.2f,0.2f,0.2f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shader.mProgram);
  
  glm::mat4 view;
  view = glm::lookAt(mActiveScene.mainCamera.getPosition(), mActiveScene.mainCamera.getTarget(), mActiveScene.mainCamera.getUp());
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mActiveScene.mModel->getModelMatrix()));

  glUniform3fv(cameraPosLoc, 1, glm::value_ptr(mActiveScene.mainCamera.getPosition()));

  glm::mat3 inversedModel = glm::mat3(glm::transpose(glm::inverse(mActiveScene.mModel->getModelMatrix())));
  glUniformMatrix3fv(inversedModelLoc, 1, GL_FALSE, glm::value_ptr(inversedModel));

  for (Mesh &mesh : mActiveScene.mModel->mMeshes) {

    for(int i = 0; i < mesh.mTextures.size(); i++) {
      Texture texture = mesh.mTextures[i];

      const char *name;
      glActiveTexture(GL_TEXTURE0 + i);
      switch (texture.getType()) {
      case DIFFUSE:
	name = "texture_diffuse";
	break;
      case SPECULAR:
	name = "texture_specular";
	break;
      }
      
      glUniform1i(glGetUniformLocation(shader.mProgram, name), i);
      glBindTexture(GL_TEXTURE_2D, texture.getId());
    }
    
    glBindVertexArray(mesh.mVAO);
    glDrawElements(GL_TRIANGLES, mesh.mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
  }

  glUseProgram(0);
}  


void Renderer::resize(int width, int height)
{
  glViewport(0, 0, width, height);
  glUseProgram(shader.mProgram);
  glm::mat4 projection = glm::perspective(glm::radians(50.0f), (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
  glUseProgram(0);
}  

void Renderer::cleanUp()
{
  glDeleteProgram(shader.mProgram);
  
  for (Mesh &mesh : mActiveScene.mModel->mMeshes) {
    glDeleteVertexArrays(1, &mesh.mVAO);
    glDeleteBuffers(1, &mesh.mVBO);
    glDeleteBuffers(1, &mesh.mEBO);
  }

  Texture::release();
}  
