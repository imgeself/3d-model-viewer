#ifndef RENDERER_H
#define RENDERER_H

#include "scene.h"
#include <memory>

class Renderer {

public:
  ~Renderer();
  static Renderer& getInstance()
  {
    static Renderer instance;
    return instance;
  };
  void prepare();
  void cleanUp();
  void render();
  void resize(int width, int height);
  void setActiveScene(Scene &scene);
  
private:
  Renderer();
  Scene mActiveScene;
};

#endif
