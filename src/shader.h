#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <GL/glew.h>

class Shader {

public:
  Shader();
  ~Shader();
  void compileShadersAndProgram();

  GLuint mProgram;
};

#endif
