#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include <CoreClass/CoreClassPreDec.h>
#include <CoreClass/CoreEntity/CoreEntity.h>

#include <model/Camera.h>
#include <model/Model.h>
#include <model/Shaders.h>

#include <map>
#include <memory>

namespace core {
class RenderHandler {
public:
  RenderHandler();
  ~RenderHandler();

  void static DrawInstanced(
      float width, float height, Camera *camera = NULL,
      std::vector<std::unique_ptr<Shader>> *shader = NULL,
      std::vector<std::unique_ptr<Model::Light>> *lights = NULL,
      std::unordered_map<Model::Model *,
                         std::vector<std::unique_ptr<core::CoreEntity>>> *map =
          NULL);
};
} // namespace core

#endif // !RENDERFUNCTOR_H
