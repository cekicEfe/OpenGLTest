#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

enum VERTEX_INCLUDES {
  POSITION,
  NORMAL,
  TEXTURE,
  COLOR
  // TANGENT,
  // B_TANGENT,
  // BONE,
  // WEIGHT,
};

namespace Model {

struct Vertex {
  glm::vec3 position;
  glm::vec4 color;
  glm::vec3 normal;
  glm::vec2 texture;
  // glm::vec3 tangent;
  // glm::vec3 biTangent;
  //  int boneIds[4]; // 4 is the max bone influence
  //  float weights[4];
};

} // namespace Model

#endif
