#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include <CoreClass/CoreClassPreDec.h>
#include <CoreClass/CoreEntity/CoreEntity.h>

#include <model/Camera.h>
#include <model/Model.h>
#include <model/Shaders.h>

#include <map>
#include <memory>

namespace core
{
class RenderHandler
{
private:
  RenderHandler ();
  ~RenderHandler ();
  static core::RenderHandler *instance;

public:
  static core::RenderHandler const *const createInstance ();
  void deleteInstance () const;
  void DrawInstanced (const float scr_width, const float scr_height,
                      Camera *const camera = NULL,
                      const std::vector<Model::Light> *const lights = NULL,
                      const std::vector<core::CoreEntity> *const entities
                      = NULL) const;
};
} // namespace core

#endif // !RENDERFUNCTOR_H
