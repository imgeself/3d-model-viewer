#include "shader.h"

/*
 * Since we are using only two shaders for this program, we can hardcode them in here.
 */
const GLchar *vertexShaderSource = R"(
#version 300
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

void main()
{
gl_Position(position, 1.0f);
}
)";

const GLchar *fragmentShaderSource = R"(
#version 300
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
  
  this->program = glCreateProgram();
  glAttachShader(this->program, vertexShader);
  glAttachShader(this->program, fragmentShader);
  glLinkProgram(this->program);

  glGetProgramiv(this->program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->program, 512, NULL, info);
    std::cout << "Error at linking shader program:\n" << info << "\n";
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);  
    
}

Shader::~Shader()
{

}
