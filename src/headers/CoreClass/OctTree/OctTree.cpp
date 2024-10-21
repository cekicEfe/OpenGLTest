#include "OctTree.hpp"
#include "CoreClass/CoreEntity/CoreEntity.h"
#include <iostream>
#include <memory>

core::OctBox::OctBox() {}
core::OctBox::~OctBox() {}
core::OctBox::OctBox(glm::vec3 pos, GLfloat sqaureRadius) {
  this->sqaureRadius = sqaureRadius;
  this->position = pos;
}

core::OctTreeNode::OctTreeNode() {}
core::OctTreeNode::OctTreeNode(glm::vec3 pos, GLfloat squareRadius) {
  this->Box.position = pos;
  this->Box.sqaureRadius = squareRadius;
}
core::OctTreeNode::~OctTreeNode() {}

// Subdivides current oct tree node to 8 nodes
void core::OctTreeNode::subdivide() {
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
  for (auto &elem : this->Directions) {
    elem->parentNode = this;
  }
}

void core::OctTreeNode::debug(GLint choice) {
  enum choices { PRINT_CHILDREN_POS = 1 };
  if (choice == PRINT_CHILDREN_POS) {
    for (auto &elem : this->Directions) {
      if (elem.get() != nullptr) {
        std::cout << &elem << "pos vector :" << std::endl;
        std::cout << "x:" << elem->Box.position.x
                  << "y:" << elem->Box.position.y
                  << "z:" << elem->Box.position.z << std::endl;
        std::cout << "square radius :" << elem->Box.sqaureRadius << std::endl
                  << std::endl;
      } else {
        std::cout << "Empty direction" << std::endl;
      }
    }
  } else {
    std::cout << "No valid option" << std::endl;
  }
}

// Broken
void core::OctTreeNode::insertEntity(core::CoreEntity *entity) {

  glm::vec3 relativePos = entity->movComponent.pos - this->Box.position;
  GLint xdir = relativePos.x <= 0 ? 0 : 4;
  GLint ydir = relativePos.y <= 0 ? 0 : 2;
  GLint zdir = relativePos.z <= 0 ? 0 : 1;
  GLint dir = (xdir + ydir + zdir);

  GLboolean isEmptyNode = true;
  for (auto &elem : this->Directions) {
    if (elem == nullptr) {
      continue;
    } else {
      isEmptyNode = false;
      break;
    }
  }

  if (isEmptyNode) {
    this->subdivide();
    this->Directions.at(dir).get()->heldEntities.push_back(entity);
  } else {
  }
}

//
