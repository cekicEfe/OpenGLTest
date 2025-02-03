#ifndef RENDERHANDLER_H
#define RENDERHANDLER_H

#include "CoreBackend/GlfwHandler/WindowHandler/Window/Window.h"
#include <CoreBackend/CoreEntity/CoreEntity.h>
#include <GraphicsBackend/Camera/Camera.h>
#include <GraphicsBackend/Light/Light.hpp>
#include <GraphicsBackend/Model/Model.h>
#include <GraphicsBackend/Shader/Shaders.h>

namespace core
{
class RenderHandler
{
public:
  RenderHandler ();
  ~RenderHandler ();

  void RenderTest (const core::Window &window, const Camera *camera = NULL,
                   const Model::Light *const lights = NULL,
                   const size_t lights_size = 0,
                   const core::CoreEntity *const entities = nullptr,
                   const size_t entities_size = 0) const;
  /*
  void DrawInstanced(const GLuint &SCR_WIDTH, const GLuint &SCR_HEIGHT,
                     const Camera *camera = NULL,
                     const Model::Light *const lights = NULL,
                     const size_t lights_size = 0,
                     const core::CoreEntity *const entities = nullptr,
                     const size_t entities_size = 0) const;
  */
};
} // namespace core

#endif // !RENDERFUNCTOR_H
