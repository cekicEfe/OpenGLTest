#ifndef COLDET_H
#define COLDET_H

#include <CoreClass/CoreEntity/CoreEntity.h>
#include <CoreClass/HitBox/CollisionDetector/OctTree/OctTree.hpp>
#include <CoreClass/HitBox/HitBox.h>

namespace core {
class CollisionDetector {
public:
  static void CheckCell();
};
} // namespace core

#endif
