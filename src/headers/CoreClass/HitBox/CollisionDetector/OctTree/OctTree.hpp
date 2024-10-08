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

  std::array<std::unique_ptr<OctTreeNode>, 8> Directions; // AKA children

  std::vector<core::CoreEntity> *heldEntities;
  core::OctTreeNode *parentNode;

  OctBox Box;

  void insertEntity(core::CoreEntity *entity);
  void debug(GLint option);
  void subdivide();
  //
};
} // namespace core

#endif
