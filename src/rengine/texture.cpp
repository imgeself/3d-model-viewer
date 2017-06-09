#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

std::unordered_map<std::string, GLuint> Texture::mTexturePool;

Texture::Texture(std::string path, TextureType type)
{
  mType = type;
  mPath = path;
}

void Texture::load()
{
  auto search = mTexturePool.find(mPath);
  if (search != mTexturePool.end()) {
    // We loaded texture before.
    mId = search->second;
  }

  else {
    try {
      int width, height, nrChannels;
      unsigned char *data = stbi_load(mPath.c_str(), &width, &height, &nrChannels, 0);

      GLenum channel;
      if (nrChannels == 1)
        channel = GL_RED;
      else if (nrChannels == 3)
        channel = GL_RGB;
      else if (nrChannels == 4)
        channel = GL_RGBA;

      glGenTextures(1, &mId);
      glBindTexture(GL_TEXTURE_2D, mId);
      glTexImage2D(GL_TEXTURE_2D, 0, channel, width, height, 0,
                   channel, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);	
      stbi_image_free(data);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);

      mTexturePool[mPath] = mId;

    } catch(...) {
      std::cout << "error at texture loading: \n" << "path: " << mPath << "\n";
    }
    
  }

}

void Texture::release()
{
  for (auto it : mTexturePool) {
    glDeleteTextures(1, &it.second);
  }
}

GLuint Texture::getId()
{
  return mId;
}

TextureType Texture::getType()
{
  return mType;
}

std::string Texture::getPath()
{
  return mPath;
}
