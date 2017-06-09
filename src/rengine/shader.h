#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <typeinfo>
#include <GL/glew.h>

class Shader {

public:
  Shader();
  ~Shader();
  void compileShadersAndProgram();
  void use();
  void unuse();
  void release();

  // I wanted to write clean reusable template "set" function.
  // But templates in c++ give me headaches.
  // The worst thing in language !!!

  void set(const char *name, float value) {
    glUniform1f(glGetUniformLocation(mProgram, name), value);
  };
  void set(const char *name, int value) {
    glUniform1i(glGetUniformLocation(mProgram, name), value);
  };
  void set(const char *name, bool value) {
    glUniform1i(glGetUniformLocation(mProgram, name), value);
  };
  void set(const char *name, glm::vec2 value) {
    glUniform2fv(glGetUniformLocation(mProgram, name), 1, glm::value_ptr(value));
  };
  void set(const char *name, glm::vec3 value) {
    glUniform3fv(glGetUniformLocation(mProgram, name), 1, glm::value_ptr(value));
  };
  void set(const char *name, glm::vec4 value) {
    glUniform4fv(glGetUniformLocation(mProgram, name), 1, glm::value_ptr(value));    
  };
  void set(const char *name, glm::mat3 value) {
    glUniformMatrix3fv(glGetUniformLocation(mProgram, name), 1, GL_FALSE, glm::value_ptr(value));
  };
  void set(const char *name, glm::mat4 value){
    glUniformMatrix4fv(glGetUniformLocation(mProgram, name), 1, GL_FALSE, glm::value_ptr(value));
  };
private:
  GLuint mProgram;
  
};


#endif
