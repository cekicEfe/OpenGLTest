#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GLFW/glfw3.h>
#include <GraphicsBackend/Material/Material.hpp>
#include <string>

namespace Model {

class Texture {
public:
  GLuint ID;

  Material material;

  std::string type;
  std::string path;
};

} // namespace Model

#endif
