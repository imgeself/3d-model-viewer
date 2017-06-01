#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

enum TextureType {
  DIFFUSE
};

class Texture {
private:  
  GLuint mId;
  TextureType mType;
  std::string mPath;

public:
  Texture(std::string path, TextureType type);
  void load();
  GLuint getId();
  TextureType getType();
  std::string getPath();
};

#endif
