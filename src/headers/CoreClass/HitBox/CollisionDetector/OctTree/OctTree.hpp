#ifndef OCTTREE_HPP
#define OCTTREE_HPP

#include "ext/vector_float3.hpp"
#include <CoreClass/CoreEntity/CoreEntity.h>
#include <GL/gl.h>
#include <memory>

namespace core {

class OctBox {
public:
  OctBox();
  ~OctBox();
  GLuint sqaureRadius; // HORRIBLE NAME since its a SQAURE
  glm::vec3 position;
};

class OctTreeNode {
public:
  OctTreeNode();
  ~OctTreeNode();
  //			N
  //			//
  //			//
  //			//
  //			//   --
  //			//  7/
  //			// //
  //			////
  //			///
  // W////////////////////////////////////E
  //		       ///
  //		      ////
  //		     //	//
  //		    //	//
  //		   //	//
  //		  ++	//
  //			//
  //			//
  //			S

  std::unique_ptr<OctTreeNode> p_west;
  std::unique_ptr<OctTreeNode> p_east;
  std::unique_ptr<OctTreeNode> p_south;
  std::unique_ptr<OctTreeNode> p_north;

  std::unique_ptr<OctTreeNode> n_west;
  std::unique_ptr<OctTreeNode> n_east;
  std::unique_ptr<OctTreeNode> n_south;
  std::unique_ptr<OctTreeNode> n_north;

  OctBox Box;
  std::shared_ptr<core::CoreEntity> heldEntity;

  void migrateHeldEntity();
  void subdivide();
  //
};
} // namespace core

#endif
