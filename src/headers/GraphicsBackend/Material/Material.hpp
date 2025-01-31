#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <GLFW/glfw3.h>

namespace Model {

class Material {
public:
  GLfloat ambient;
  GLfloat diffuse;
  GLfloat specular;
  GLfloat shininess;
};

} // namespace Model

#endif
