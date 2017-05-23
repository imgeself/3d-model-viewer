#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indicies, Shader shader)
{
  this->vertices = vertices;
  this->indicies = indicies;

  this->shader = shader;
  prepareMesh();
}

Mesh::~Mesh()
{
  releaseMesh();
}

void Mesh::draw()
{
  glBindVertexArray(this->VAO);
  glDrawElements(GL_TRIANGLES, this->indicies.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}  

void Mesh::prepareMesh()
{
  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);
  glGenBuffers(1, &this->EBO);

  glBindVertexArray(this->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicies.size() * sizeof(GLuint), &this->indicies[0], GL_STATIC_DRAW);

  // Vertex Positions
  glEnableVertexAttribArray(0);	
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (GLvoid*)0);
  // Vertex Normals
  glEnableVertexAttribArray(1);	
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (GLvoid*)offsetof(Vertex, nor));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  
  glBindVertexArray(0);

}

void Mesh::releaseMesh()
{
  glDeleteBuffers(1, &this->VBO);
  glDeleteBuffers(1, &this->EBO);
  glDeleteVertexArrays(1, &this->VAO);
}  
