#ifndef TESTHITBOX_H
#define TESTHITBOX_H

#include <CoreClass/CoreClassPreDec.h>
#include <glm/glm.hpp>
#include <model/Model.h>
#include <vector>

namespace core
{
class HitBox
{
private:
  std::vector<glm::vec3> vertices;

public:
  HitBox ();
  virtual ~HitBox () = 0;
};
} // namespace core

#endif
