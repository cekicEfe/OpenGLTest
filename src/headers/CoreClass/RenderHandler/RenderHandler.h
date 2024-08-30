#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include <CoreClass/CoreClassPreDec.h>
#include <CoreClass/CoreEntity/CoreEntity.h>

#include <model/Shaders.h>
#include <model/Camera.h>
#include <model/Model.h>

#include <memory>

namespace core
{
  class RenderHandler
  {
  private:
    RenderHandler();
    ~RenderHandler();

    void static DrawInstanced(float width,
                              float height,
                              std::vector<std::unique_ptr<Shader>>* shader = NULL,
                              Camera * camera = NULL,
                              std::vector<std::unique_ptr<Model::Light>>* lights = NULL,
                              std::vector<std::unique_ptr<core::CoreEntity>>* objects = NULL);

    friend class core::MainHandler;
  };
}

#endif // !RENDERFUNCTOR_H
