#ifndef RENDERER_H
#define RENDERER_H

#include "scene.h"

class Renderer {

public:
  ~Renderer();
  static Renderer& getInstance()
  {
    static Renderer instance;
    return instance;
  };
  void prepare();
  void render();
  void resize(int width, int height);
  void setActiveScene(Scene &scene);
  
private:
  Renderer();
  Scene mActiveScene;
};

#endif
