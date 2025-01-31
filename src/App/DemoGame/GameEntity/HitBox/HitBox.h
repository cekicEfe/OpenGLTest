#ifndef TESTHITBOX_H
#define TESTHITBOX_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace testgame {
class HitBox {
protected:
  std::vector<glm::vec3> vertices;
  std::string hitboxName;

public:
  HitBox();
  HitBox(std::string hitboxName);
  virtual ~HitBox();
};
} // namespace testgame

#endif
