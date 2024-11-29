#ifndef OCTTREENODE_HPP
#define OCTTREENODE_HPP

#include <CoreClass/CoreEntity/CoreEntity.h>
#include <CoreClass/OctTree/OctBox.hpp>
#include <CoreClass/OctTree/OctTreeForwardDec.hpp>
#include <glm/glm.hpp>
#include <string>

namespace core
{

class OctTreeNode
{
private:
  OctTreeNode (glm::vec3 pos, GLfloat squareRadius, std::string genLeaf);

  OctBox Box;
  std::string generation; // For debug purposes only
  core::OctTree *parentTree = nullptr;
  core::OctTreeNode *parentNode = nullptr;
  core::CoreEntity *heldEntity = nullptr;

  std::array<std::unique_ptr<OctTreeNode>, 8> Directions;

  void subdivide ();
  void debug (GLint option);
  void printChildsRecursivly ();
  void insertEntity (core::CoreEntity *const entity);

public:
  OctTreeNode ();
  ~OctTreeNode ();

  friend core::OctTree;
};

};

#endif
