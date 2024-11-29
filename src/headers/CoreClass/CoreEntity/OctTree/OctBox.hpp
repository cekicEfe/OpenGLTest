#ifndef OCTBOX_HPP
#define OCTBOX_HPP

#include <GL/gl.h>
#include <glm/glm.hpp>

namespace core
{

class OctBox
{
public:
  OctBox ();
  OctBox (glm::vec3 pos, GLfloat sqaureRadius);
  ~OctBox ();

  glm::vec3 position;
  GLfloat sqaureRadius;
};

}

#endif
