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

//                       PY       PZ
//                       //       /
//                       //      /
//                       //     /
//                       //    /
//                       //   /
//                       //  /
//                       // /
//                       ///
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
  NXPYPZ = 0,
  PXPYPZ,
  NXNYPZ,
  PXNYPZ,

  NXPYNZ,
  PXPYNZ,
  NXNYNZ,
  PXNYNZ
};

class OctTreeNode {
public:
  OctTreeNode();
  OctTreeNode(glm::vec3 pos, GLfloat squareRadius);
  ~OctTreeNode();

  static std::vector<OctTreeNode *> octEndNodes;
  std::array<std::unique_ptr<OctTreeNode>, 8> Directions; // AKA children

  std::shared_ptr<core::CoreEntity> heldEntity;
  std::shared_ptr<core::OctTreeNode> parentNode;

  OctBox Box;

  void migrateHeldEntity();
  void subdivide();
  //
};
} // namespace core

#endif
