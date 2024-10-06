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
// OctTreeNode Static Variables :
//
std::vector<core::OctTreeNode *> core::OctTreeNode::octEndNodes;

//
// OctTreeNode Methods :
//
core::OctTreeNode::OctTreeNode() {}
core::OctTreeNode::OctTreeNode(glm::vec3 pos, GLfloat squareRadius) {
  this->Box.position = pos;
  this->Box.sqaureRadius = squareRadius;
}
core::OctTreeNode::~OctTreeNode() {}

// Subdivides current oct tree node to 8 nodes
void core::OctTreeNode::subdivide() {
  //
  glm::vec3 dummyPos = this->Box.position;
  GLfloat dummyRadius = this->Box.sqaureRadius / 2;

  dummyPos =
      this->Box.position + glm::vec3(-dummyRadius, dummyRadius, dummyRadius);
  this->Directions.at(NXPYPZ).reset(
      new core::OctTreeNode(dummyPos, dummyRadius));
  dummyPos =
      this->Box.position + glm::vec3(dummyRadius, dummyRadius, dummyRadius);
  this->Directions.at(PXPYPZ).reset(
      new core::OctTreeNode(dummyPos, dummyRadius));
  dummyPos =
      this->Box.position + glm::vec3(-dummyRadius, -dummyRadius, dummyRadius);
  this->Directions.at(NXNYPZ).reset(
      new core::OctTreeNode(dummyPos, dummyRadius));
  dummyPos =
      this->Box.position + glm::vec3(dummyRadius, -dummyRadius, dummyRadius);
  this->Directions.at(PXNYPZ).reset(
      new core::OctTreeNode(dummyPos, dummyRadius));
  dummyPos =
      this->Box.position + glm::vec3(-dummyRadius, dummyRadius, -dummyRadius);
  this->Directions.at(NXPYNZ).reset(
      new core::OctTreeNode(dummyPos, dummyRadius));
  dummyPos =
      this->Box.position + glm::vec3(dummyRadius, dummyRadius, -dummyRadius);
  this->Directions.at(PXPYNZ).reset(
      new core::OctTreeNode(dummyPos, dummyRadius));
  dummyPos =
      this->Box.position + glm::vec3(-dummyRadius, -dummyRadius, -dummyRadius);
  this->Directions.at(NXNYNZ).reset(
      new core::OctTreeNode(dummyPos, dummyRadius));
  dummyPos =
      this->Box.position + glm::vec3(dummyRadius, -dummyRadius, -dummyRadius);
  this->Directions.at(PXNYNZ).reset(
      new core::OctTreeNode(dummyPos, dummyRadius));

  //
}
