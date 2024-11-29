#ifndef OCTTREEPREDEC_HPP
#define OCTTREEPREDEC_HPP

namespace core
{
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

class OctBox;
class OctTree;
class OctTreeNode;

}

#endif
