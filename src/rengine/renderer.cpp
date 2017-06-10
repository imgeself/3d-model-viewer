#include "renderer.h"
#include "shader.h"

#include <glm/gtc/matrix_transform.hpp>

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
  shader.use();
  
  for (Mesh &mesh : mActiveScene.mainModel->mMeshes) {
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

  shader.set("lightPos", mActiveScene.mainLight.position);
  shader.set("lightColor", mActiveScene.mainLight.color);
  shader.set("ambientStrength", mActiveScene.mainLight.ambientStrength);
}


void Renderer::render()
{
  glClearColor(0.2f,0.2f,0.2f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader.use();
  
  glm::mat4 view;
  view = glm::lookAt(mActiveScene.mainCamera.getPosition(), mActiveScene.mainCamera.getTarget(), mActiveScene.mainCamera.getUp());
  shader.set("view", view);

  shader.set("model", mActiveScene.mainModel->getModelMatrix());

  shader.set("cameraPos", mActiveScene.mainCamera.getPosition());

  glm::mat3 inversedModel = glm::mat3(glm::transpose(glm::inverse(mActiveScene.mainModel->getModelMatrix())));
  shader.set("inversedModel", inversedModel);

  for (Mesh &mesh : mActiveScene.mainModel->mMeshes) {

    for(int i = 0; i < mesh.mTextures.size(); i++) {
      Texture texture = mesh.mTextures[i];

      const char *name;
      glActiveTexture(GL_TEXTURE0 + i);
      switch (texture.getType()) {
        case DIFFUSE:
            name = "texture_diffuse";
            shader.set("hasDiffuseMap", true);
            break;
        case SPECULAR:
            name = "texture_specular";
            shader.set("hasSpecularMap", true);
            break;
      }
      
      shader.set(name, i);
      glBindTexture(GL_TEXTURE_2D, texture.getId());
    }
    
    glBindVertexArray(mesh.mVAO);
    glDrawElements(GL_TRIANGLES, mesh.mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
  }

  shader.unuse();
}  


void Renderer::resize(int width, int height)
{
  glViewport(0, 0, width, height);
  shader.use();
  glm::mat4 projection = glm::perspective(glm::radians(50.0f), (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
  shader.set("projection", projection);
  shader.unuse();
}  

void Renderer::cleanUp()
{
  shader.release();
  
  for (Mesh &mesh : mActiveScene.mainModel->mMeshes) {
    glDeleteVertexArrays(1, &mesh.mVAO);
    glDeleteBuffers(1, &mesh.mVBO);
    glDeleteBuffers(1, &mesh.mEBO);
  }

  Texture::release();
}  
