#include "OctTree.hpp"
#include "CoreClass/CoreEntity/CoreEntity.h"
#include <iostream>
#include <memory>

////////////////////
// OctBox methods //
////////////////////

core::OctBox::OctBox() {}
core::OctBox::~OctBox() {}
core::OctBox::OctBox(glm::vec3 pos, GLfloat sqaureRadius) {
  this->sqaureRadius = sqaureRadius;
  this->position = pos;
}

///////////////////////////////
// OctTreeNodeEntity methods //
///////////////////////////////

core::OctTreeNodeEntity::OctTreeNodeEntity(core::OctTreeNode *currentNode,
                                           core::CoreEntity *entity) {
  this->mCurrentOctTreeNode = currentNode;
  this->mHeldEntity.reset(entity);
}
core::OctTreeNodeEntity::~OctTreeNodeEntity() {
  for (auto &elem : this->mReferences) {
    if (elem.get()->ReturnReference() == this)
      elem.get()->mEntityReference = nullptr;
  }
}

const 
core::CoreEntity *const core::OctTreeNodeEntity::returnEntity() {
  return this->mHeldEntity.get();
}

void 
core::OctTreeNodeEntity::setHeldEntity(core::CoreEntity *entity) {
  this->mHeldEntity.reset(entity);
}

void 
core::OctTreeNodeEntity::setCurrentOctTreeNode(core::OctTreeNode *node) {
  this->mCurrentOctTreeNode = node;
}

const std::shared_ptr<core::OctTreeNodeEntityReference>
core::OctTreeNodeEntity::createReference() {
  return std::make_shared<core::OctTreeNodeEntityReference>(
      this->mHeldEntity.get());
}

////////////////////////////////////////
// OctTreeNodeEntityReference methods //
////////////////////////////////////////

core::OctTreeNodeEntityReference::OctTreeNodeEntityReference(
    core::OctTreeNodeEntity *reference) {
  this->mEntityReference = reference;
}

core::OctTreeNodeEntityReference::~OctTreeNodeEntityReference() {}

const core::OctTreeNodeEntity *const
core::OctTreeNodeEntityReference::ReturnReference() {
  return this->mEntityReference;
}

/////////////////////////
// OctTreeNode methods //
/////////////////////////

core::OctTreeNode::OctTreeNode() {}
core::OctTreeNode::OctTreeNode(glm::vec3 pos, GLfloat squareRadius,
                               std::string genLeaf) {
  this->Box.position = pos;
  this->Box.sqaureRadius = squareRadius;
  this->generation.append(genLeaf);
}
core::OctTreeNode::~OctTreeNode() {}

// Subdivides current oct tree node to 8 nodes
void 
core::OctTreeNode::subdivide() {
  glm::vec3 dummyPos = this->Box.position;
  GLfloat dummyRadius = this->Box.sqaureRadius / 2;

  // Its useless to think about here unless you expect a problem from here
  // All it does is creates objects at this->Directions at makes ptrs to point
  // them
  for (int x = 0; x <= 4; x += 4) {
    for (int y = 0; y <= 2; y += 2) {
      for (int z = 0; z <= 1; z += 1) {

        dummyPos =
            this->Box.position + glm::vec3(dummyRadius * (z == 0 ? -1 : +1),
                                           dummyRadius * (y == 0 ? -1 : +1),
                                           dummyRadius * (x == 0 ? -1 : +1));

        this->Directions.at(x + y + z).reset(new core::OctTreeNode(
            dummyPos, dummyRadius / 2,
            this->generation + char('G' + (z == 0 ? 0 : -4) +
                                    (y == 0 ? 0 : -2) + (x == 0 ? 0 : 1))));
      }
    }
  }

  for (auto &elem : this->Directions) {
    elem->parentNode = this;
    elem->heldEntity = nullptr;
  }
}

// Debugs a node
void 
core::OctTreeNode::debug(GLint choice) {
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

// Inserts an entity to the tree
void 
core::OctTreeNode::insertEntityToEmptyLeaf(
    core::CoreEntity *const entity) {

  GLboolean isSubdivided = false;
  for (auto &elem : this->Directions) {
    if (elem.get() != nullptr) {
      isSubdivided = true;
      break;
    }
  }
  
  if (isSubdivided) {
    glm::vec3 relativePos = entity->movComponent.pos - this->Box.position;
    GLint xdir = relativePos.x <= 0 ? 0 : 4;
    GLint ydir = relativePos.y <= 0 ? 0 : 2;
    GLint zdir = relativePos.z <= 0 ? 0 : 1;
    GLint dir = (xdir + ydir + zdir);

    this->Directions.at(dir)->insertEntityToEmptyLeaf(entity);
  } else {
    if (this->heldEntity == nullptr) {
      this->heldEntity = entity;
    } else if (this->heldEntity != nullptr) {
      if (this->heldEntity == entity) {
        std::cout << "Duplicate entity" << std::endl;
      } else if (this->heldEntity->movComponent.pos ==
                 entity->movComponent.pos) {
        std::cout << "Entities are at the same place" << std::endl;
      } else if (((this->heldEntity->movComponent.pos -
                   entity->movComponent.pos)
                      .length() > 0.0001)) {
        this->subdivide();
        auto ptr = this->heldEntity;
        this->heldEntity = nullptr;

        glm::vec3 relativePos = ptr->movComponent.pos - this->Box.position;
        GLint xdir = relativePos.x <= 0 ? 0 : 4;
        GLint ydir = relativePos.y <= 0 ? 0 : 2;
        GLint zdir = relativePos.z <= 0 ? 0 : 1;
        GLint dir = (xdir + ydir + zdir);

        this->Directions.at(dir)->insertEntityToEmptyLeaf(ptr);

        relativePos = entity->movComponent.pos - this->Box.position;
        xdir = relativePos.x <= 0 ? 0 : 4;
        ydir = relativePos.y <= 0 ? 0 : 2;
        zdir = relativePos.z <= 0 ? 0 : 1;
        dir = (xdir + ydir + zdir);

        this->Directions.at(dir)->insertEntityToEmptyLeaf(entity);
      }
    }
  }
}
// Prints child nodes recursivly
void 
core::OctTreeNode::printChildsRecursivly() {
  GLboolean isEmpty = true;
  for (auto &elem : this->Directions) {
    if (elem.get() != nullptr) {
      isEmpty = true;
      elem.get()->printChildsRecursivly();
    }
  }
  if (isEmpty) {
    if (this->heldEntity != nullptr)
      std::cout << this->generation << " <-- entity here " << std::endl;
    else
      std::cout << this->generation << std::endl;
  }
}
