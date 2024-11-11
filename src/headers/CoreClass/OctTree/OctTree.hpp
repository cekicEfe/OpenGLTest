#ifndef OCTTREE_HPP
#define OCTTREE_HPP

#include <CoreClass/CoreEntity/CoreEntity.h>
#include <GL/gl.h>
#include <array>
#include <memory>

namespace core
{

class OctTreeNode;
class OctTreeNodeEntity;
class OctTreeNodeEntityReference;

//                       PY       PZ
//    /////////////////////       /
//    //                 //      /
//    //                 //     /
//    //                 //    /
//    //                 //   /
//    //                 //  /
//    //                 // /
//    //                 ///
//  NX////////////////////////////////////////PX
//                      ///
//                     / //
//                    /  //
//                   /   //
//                  /    //
//                 /     //
//                /      //
//               /       //
//              PZ       NY

enum OctDirection
{
  NXNYNZ = 0,
  NXNYPZ,
  NXPYNZ,
  NXPYPZ,

  PXNYNZ,
  PXNYPZ,
  PXPYNZ,
  PXPYPZ
};

class OctBox
{
public:
  OctBox ();
  OctBox (glm::vec3 pos, GLfloat sqaureRadius);
  ~OctBox ();

  GLfloat sqaureRadius;

  glm::vec3 position;
};

class OctTreeNodeEntity
{
private:
  std::unique_ptr<core::CoreEntity> mHeldEntity;
  core::OctTreeNode *mCurrentOctTreeNode = nullptr;
  std::vector<std::shared_ptr<OctTreeNodeEntityReference> > mReferences;

public:
  OctTreeNodeEntity (core::OctTreeNode *currentNode, core::CoreEntity *entity);
  ~OctTreeNodeEntity ();

  void setHeldEntity (core::CoreEntity *entity);
  void setCurrentOctTreeNode (core::OctTreeNode *node);

  const core::CoreEntity *const returnEntity ();
  const std::shared_ptr<OctTreeNodeEntityReference> createReference ();
  void removeReference (core::OctTreeNodeEntityReference &entityReference);
};

class OctTreeNodeEntityReference
{
private:
  core::OctTreeNodeEntity *mEntityReference = nullptr;

public:
  OctTreeNodeEntityReference (core::OctTreeNodeEntity *reference);
  ~OctTreeNodeEntityReference ();

  const core::OctTreeNodeEntity *const ReturnReference ();

  friend class core::OctTreeNodeEntity;
};

class OctTreeNode
{
private:
  void subdivide ();
  void debug (GLint option);

  OctBox Box;
  std::string generation;
  std::unique_ptr<core::OctTreeNodeEntity> heldEntity;
  core::OctTreeNode *parentNode = nullptr;
  std::array<std::unique_ptr<OctTreeNode>, 8> Directions;

public:
  OctTreeNode ();
  ~OctTreeNode ();
  OctTreeNode (glm::vec3 pos, GLfloat squareRadius, std::string genLeaf);

  void printChildsRecursivly ();
  std::vector<core::CoreEntity *const> returnEndNodes ();
  void insertEntity (core::CoreEntity *const entity);
};

} // namespace core

#endif
