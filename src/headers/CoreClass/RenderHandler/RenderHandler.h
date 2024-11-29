#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include <CoreClass/CoreClassPreDec.h>
#include <CoreClass/CoreEntity/CoreEntity.h>
#include <CoreClass/GlfwHandler/WindowHandler/Window/Window.h>

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

  RenderHandler (RenderHandler &other) = delete;
  void operator= (const RenderHandler &) = delete;

  static core::RenderHandler *instance;

public:
  static const core::RenderHandler *const createInstance ();
  void deleteInstance () const;
  void DrawInstanced (
      const GLuint &SCR_WIDTH, const GLuint &SCR_HEIGHT, const Camera &camera,
      const std::vector<Model::Light> *const lights = NULL,
      const std::vector<std::unique_ptr<core::CoreEntity> > *const entities
      = NULL) const;
};
} // namespace core

#endif // !RENDERFUNCTOR_H
