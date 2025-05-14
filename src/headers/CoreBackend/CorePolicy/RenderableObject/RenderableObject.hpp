#ifndef RENDERABLEOBJECT_HPP
#define RENDERABLEOBJECT_HPP

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>

namespace core
{
class RenderableObject
{
public:
  RenderableObject ();
  virtual ~RenderableObject () = 0;

  virtual void ReadyShader () = 0;
  virtual void RenderBasic () = 0;
};
}

#endif
