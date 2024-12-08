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
protected:
  std::vector<glm::vec3> vertices;
  std::string hitboxName;

public:
  HitBox ();
  HitBox (std::string hitboxName);
  virtual ~HitBox ();
};
} // namespace core

#endif
