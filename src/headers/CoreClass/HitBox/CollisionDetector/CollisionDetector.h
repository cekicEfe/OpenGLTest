#ifndef COLDET_H
#define COLDET_H

#include <CoreClass/CoreEntity/CoreEntity.h>

namespace core {
class CollisionDetector {
public:
  static void Detect(std::vector<std::unique_ptr<CoreEntity>> entities);
};
} // namespace core

#endif
