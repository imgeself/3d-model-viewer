#include "shader.h"

/*
 * Since we are using only two shaders for this program, we can hardcode them in here.
 */
const GLchar *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 model;

void main()
{
gl_Position = model * vec4(pos, 1.0f);
}
)";

const GLchar *fragmentShaderSource = R"(
#version 330 core
out vec4 color;

void main()
{
color = vec4(1.0f);
}
)";

Shader::Shader()
{
  GLint success;
  GLchar info[512];
  
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, info);
    std::cout << "Error at compiling vertex shader:\n" << info << "\n";
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, info);
    std::cout << "Error at compiling fragment shader:\n" << info << "\n";
  }
  
  mProgram = glCreateProgram();
  glAttachShader(mProgram, vertexShader);
  glAttachShader(mProgram, fragmentShader);
  glLinkProgram(mProgram);

  glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(mProgram, 512, NULL, info);
    std::cout << "Error at linking shader program:\n" << info << "\n";
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);  
    
}

Shader::~Shader()
{

}
