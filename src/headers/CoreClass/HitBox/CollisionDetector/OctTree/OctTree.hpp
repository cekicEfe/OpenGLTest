#ifndef OCTTREE_HPP
#define OCTTREE_HPP

#include <CoreClass/CoreEntity/CoreEntity.h>
#include <GL/gl.h>
#include <array>
#include <memory>

namespace core {

class OctBox {
public:
  OctBox();
  OctBox(glm::vec3 pos, GLfloat sqaureRadius);
  ~OctBox();
  GLfloat sqaureRadius; // HORRIBLE NAME since its a SQAURE
                        // Since we know what a SQUARE is knowing only one side
                        // is enoughrfwe to know its shape and all
  glm::vec3 position;
};

enum OctDirection {
  P_SOUTHWEST = 0,
  P_NORTHEAST,
  P_NORTHWEST,
  P_SOUTHEAST,

  N_SOUTHWEST,
  N_NORTHEAST,
  N_NORTHWEST,
  N_SOUTHEAST,
};

class OctTreeNode {
public:
  OctTreeNode();
  OctTreeNode(glm::vec3 pos, GLfloat squareRadius);
  ~OctTreeNode();

  std::array<std::unique_ptr<OctTreeNode>, 8> Directions;

  OctBox Box;
  std::shared_ptr<core::CoreEntity> heldEntity;

  void migrateHeldEntity();
  void subdivide();
  //
};
} // namespace core

#endif
