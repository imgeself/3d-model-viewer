#include "texture.h"
#include <gdkmm/pixbuf.h>
#include <iostream>

std::unordered_map<std::string, GLuint> Texture::mTexturePool;

Texture::Texture(std::string path, TextureType type)
{
  mType = type;
  mPath = path;
}

/*
 * We are using gdk pixbuf for image loading. Since we are linking gdk lib for gui,
 * we do not need to use any other image loading lib.
 */
void Texture::load()
{
  auto search = mTexturePool.find(mPath);
  if (search != mTexturePool.end()) {
    // We loaded texture before.
    mId = search->second;
  } else {
  
    try {
      // pixBuf is wrapped aroun GLib refptr which some kind of smart pointer.
      // don't delete pixBuf it automatically delete itself.
      auto pixBuf = Gdk::Pixbuf::create_from_file(mPath);
      glGenTextures(1, &mId);
      glBindTexture(GL_TEXTURE_2D, mId);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixBuf->get_width(),
		   pixBuf->get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pixBuf->get_pixels());
      glGenerateMipmap(GL_TEXTURE_2D);	
    
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);

      mTexturePool[mPath] = mId;

    } catch(Gdk::PixbufError error) {
      std::cout << "error at texture loading: \n" << "path: " << mPath << "\n"
		<< error.what() << "\n";
    }
    
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
