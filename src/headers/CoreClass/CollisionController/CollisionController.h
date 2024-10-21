#ifndef COLDET_H
#define COLDET_H

#include <CoreClass/CoreEntity/CoreEntity.h>
#include <CoreClass/HitBox/HitBox.h>
#include <CoreClass/OctTree/OctTree.hpp>

namespace core {
class CollisionController {
public:
  static void CheckCell(const core::OctTreeNode *const mainNode);
  static void (*resolver)(core::CoreEntity *const, core::CoreEntity *const);
};
} // namespace core

#endif
