#include "OctTree.hpp"
#include <memory>

//
// OctBox Methods :
//
core::OctBox::OctBox() {}
core::OctBox::~OctBox() {}
core::OctBox::OctBox(glm::vec3 pos, GLfloat sqaureRadius) {
  this->sqaureRadius = sqaureRadius;
  this->position = pos;
}

//
// OctTreeNode Methods :
//

core::OctTreeNode::OctTreeNode() {}
core::OctTreeNode::OctTreeNode(glm::vec3 pos, GLfloat squareRadius) {
  this->Box.position = pos;
  this->Box.sqaureRadius = squareRadius;
}
core::OctTreeNode::~OctTreeNode() {}
void core::OctTreeNode::subdivide() {
  //
  glm::vec3 dummyPos = this->Box.position;
  GLfloat dummyRadius = this->Box.sqaureRadius / 2;

  for (size_t i = 0; i < 4; i++) {
    if (i < 2) {
      dummyPos = this->Box.position +
                 glm::vec3(i % 2 ? dummyRadius : -dummyRadius, dummyRadius,
                           i % 2 ? -dummyRadius : dummyRadius);
    }
    if (i >= 2) {
      dummyPos = this->Box.position +
                 glm::vec3(i % 2 ? dummyRadius : -dummyRadius, dummyRadius,
                           i % 2 ? dummyRadius : -dummyRadius);
    }
    this->Directions.at(i).reset(new OctTreeNode(dummyPos, dummyRadius));

    dummyPos = this->Box.position;
  }
  for (size_t i = 4; i < 8; i++) {
    if (i < 6) {
      dummyPos = this->Box.position +
                 glm::vec3(i % 2 ? dummyRadius : -dummyRadius, -dummyRadius,
                           i % 2 ? -dummyRadius : dummyRadius);
    }
    if (i >= 6) {
      dummyPos = this->Box.position +
                 glm::vec3(i % 2 ? dummyRadius : -dummyRadius, -dummyRadius,
                           i % 2 ? dummyRadius : -dummyRadius);
    }
    this->Directions.at(i).reset(new OctTreeNode(dummyPos, dummyRadius));

    dummyPos = this->Box.position;
  }
  //
}
