#ifndef TESTHITBOX_H
#define TESTHITBOX_H

#include <CoreClass/CoreClassPreDec.h>
#include <glm/glm.hpp>
#include <model/Model.h>
#include <vector>

namespace testgame
{
class HitBox
{
private:
  std::vector<glm::vec3> vertices;

public:
  HitBox ();
  virtual ~HitBox ();
};
} // namespace core

#endif
