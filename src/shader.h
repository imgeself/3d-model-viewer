#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <GL/glew.h>

class Shader {

public:
  Shader();
  ~Shader();

  GLuint program;
};

#endif
