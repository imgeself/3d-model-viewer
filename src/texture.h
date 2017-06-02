#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>

enum TextureType {
  DIFFUSE,
  SPECULAR
};

class Texture {
private:  
  GLuint mId;
  TextureType mType;
  std::string mPath;
  static std::unordered_map<std::string, GLuint> mTexturePool;

public:
  Texture(std::string path, TextureType type);
  void load();
  GLuint getId();
  TextureType getType();
  std::string getPath();
};

#endif
