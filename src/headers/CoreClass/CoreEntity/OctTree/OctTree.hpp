#ifndef OCTTREE_HPP
#define OCTTREE_HPP

#include <CoreClass/CoreEntity/CoreEntity.h> //For CoreEntity
#include <CoreClass/OctTree/OctBox.hpp>      //For OctBox
#include <CoreClass/OctTree/OctTreeNode.hpp> //For OctTreeNode

#include <GL/gl.h>
#include <array>
#include <cmath>
#include <memory>
#include <vector>

namespace core
{

class OctTree
{
private:
  OctBox box;
  std::string genName;
  core::OctTreeNode rootNode;
  std::vector<core::CoreEntity> heldEntities;

public:
  OctTree (GLfloat radius, glm::vec3 pos, std::string genName);
  ~OctTree ();

  void find (const core::CoreEntity *const entity);
  void update (const core::CoreEntity *const entity, GLfloat deltaTime);
  void updateAll (GLfloat deltaTime);

  void push_back (core::CoreEntity *const entity);
  void check (core::CoreEntity *const entity);
  void deleteEntity (core::CoreEntity *const entity);
  core::CoreEntity *releaseEntity (core::CoreEntity *const entity);
};

} // namespace core

#endif
