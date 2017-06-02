#include "shader.h"

/*
 * Since we are using only two shaders for this program, we can hardcode them in here.
 */
const GLchar *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoords;

out vec4 oColor;
out vec3 oNormal;
out vec3 oFragPos;
out vec2 oTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 inversedModel;

void main()
{
gl_Position = projection * view * model * vec4(pos, 1.0f);

oColor = color;
oFragPos = vec3(model * vec4(pos, 1.0f));
oNormal = inversedModel * normal;
oTexCoords = texCoords;
}
)";

const GLchar *fragmentShaderSource = R"(
#version 330 core
in vec4 oColor;
in vec3 oNormal;
in vec3 oFragPos;
in vec2 oTexCoords;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float ambientStrength;

uniform vec3 cameraPos;

uniform bool hasDiffuseMap;
uniform sampler2D texture_diffuse;

uniform bool hasSpecularMap;
uniform sampler2D texture_specular;

float specularStrength = 0.5f;

void main()
{

vec3 norm = normalize(oNormal);
vec3 lightDir = normalize(lightPos - oFragPos);
float diff = max(dot(norm, lightDir), ambientStrength);

vec3 diffuse = diff * lightColor;
if (hasDiffuseMap) {
  diffuse *= vec3(texture(texture_diffuse, oTexCoords));
}

vec3 viewDir = normalize(cameraPos - oFragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir),0.0),64);

vec3 specular = specularStrength * spec * lightColor;
if (hasSpecularMap) {
  specular *= vec3(texture(texture_specular, oTexCoords));
}

color = vec4 ((diffuse + specular) * oColor.xyz, oColor.w);
}
)";

Shader::Shader()
{
    
}

void Shader::compileShadersAndProgram()
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

void Shader::use()
{
  glUseProgram(mProgram);
}

void Shader::unuse()
{
  glUseProgram(0);
}

void Shader::release()
{
  glDeleteProgram(mProgram);
}  
