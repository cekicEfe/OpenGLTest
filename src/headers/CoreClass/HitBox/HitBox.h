#ifndef TESTHITBOX_H
#define TESTHITBOX_H

#include <CoreClass/CoreClassPreDec.h>
#include <glm/glm.hpp>
#include <model/Model.h>
#include <vector>

namespace core {
class HitBox {
public:
  HitBox();
  ~HitBox();

  void GenerateDemoCube();
  void GenerateHitbox(Model::Model *pMdl);

  GLfloat XMaxLen;
  GLfloat YMaxLen;
  GLfloat ZMaxLen;

  std::vector<glm::vec3> points;
};
} // namespace core

#endif
