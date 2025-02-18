#ifndef TESTHITBOX_H
#define TESTHITBOX_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace testgame {
class GameHitBox {
protected:
  std::vector<glm::vec3> vertices;
  std::string hitboxName;

public:
  GameHitBox();
  GameHitBox(std::string hitboxName);
  virtual ~GameHitBox();
};
} // namespace testgame

#endif
