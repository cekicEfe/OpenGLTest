#ifndef TESTHITBOX_H
#define TESTHITBOX_H

#include "ext/vector_float3.hpp"
#include <CoreClass/CoreClassPreDec.h>
#include <glm.hpp>
#include <model/Model.h>
#include <vector>

namespace core {
class HitBox {
public:
  HitBox();
  ~HitBox();

  void GenerateDemoCube();
  void GenerateHitbox(Model::Model *pMdl);

  std::vector<glm::vec3> points;
};
} // namespace core

#endif
