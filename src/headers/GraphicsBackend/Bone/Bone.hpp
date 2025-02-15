#ifndef BONE_HPP
#define BONE_HPP

#include "glm/glm.hpp"
#include <string>
namespace Model {
struct Bone {
  std::string name;
  std::string info;
  glm::mat4 offset;
  uint id;
};

} // namespace Model

#endif
