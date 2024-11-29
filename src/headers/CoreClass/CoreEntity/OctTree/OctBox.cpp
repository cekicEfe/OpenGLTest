#include "OctBox.hpp"

////////////////////
// OctBox methods //
////////////////////

core::OctBox::OctBox ()
{
}
core::OctBox::~OctBox ()
{
}
core::OctBox::OctBox (glm::vec3 pos, GLfloat sqaureRadius)
{
  this->sqaureRadius = sqaureRadius;
  this->position = pos;
}
