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
  GLfloat sqaureRadius;
  glm::vec3 position;
};

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

enum OctDirection {
  NXNYNZ = 0,
  NXNYPZ,
  NXPYNZ,
  NXPYPZ,

  PXNYNZ,
  PXNYPZ,
  PXPYNZ,
  PXPYPZ
};

class OctTreeNode {
public:
  OctTreeNode();
  ~OctTreeNode();
  OctTreeNode(glm::vec3 pos, GLfloat squareRadius);

  core::OctTreeNode *parentNode = NULL;
  std::vector<core::CoreEntity *> heldEntities;
  std::array<std::unique_ptr<OctTreeNode>, 8> Directions;

  OctBox Box;

  // Must be used at node 0
  void insertEntity(core::CoreEntity *entity);

  void resolveEntityCramp();
  void debug(GLint option);
  void subdivide();
};
} // namespace core

#endif
