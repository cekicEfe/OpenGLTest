#ifndef TESTHITBOX_H
#define TESTHITBOX_H

#include <CoreClass/CoreClassPreDec.h>
#include <CoreClass/CoreEntity/CoreEntity.h>

namespace core {
class HitBox {
public:
  CoreEntity *mConnectedEntity = nullptr;

  glm::vec3 mTopPos;
  glm::vec3 mBotPos;
  glm::vec3 mFrontPos;
  glm::vec3 mRearPos;
  glm::vec3 mLeftPos;
  glm::vec3 mRightPos;

  void AttachEntity(CoreEntity *entity);
  void GenerateHitbox();
};
} // namespace core

#endif
