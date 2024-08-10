#ifndef RENDERFUNCTOR_H
#define RENDERFUNCTOR_H

#include <CoreClass/CoreClass.h>
#include <CoreClass/CoreEntity/CoreEntity.h>

#include <model/Shaders.h>
#include <model/Camera.h>
#include <model/Model.h>

#include <memory>

namespace core
{
  class RenderFunctor
  {
  private:
    RenderFunctor();
    ~RenderFunctor();

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
