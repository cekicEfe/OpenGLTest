#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

namespace Model {

class Material {
public:
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  GLfloat shininess;
};

} // namespace Model

#endif
