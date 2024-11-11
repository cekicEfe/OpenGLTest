#ifndef COREOBJECT_H
#define COREOBJECT_H

#include "glm/fwd.hpp"
#include <CoreClass/CoreClassPreDec.h>
#include <CoreClass/HitBox/HitBox.h>
#include <glm/gtc/quaternion.hpp>
#include <json/json.hpp>
#include <memory>
#include <model/Model.h>
#include <vector>

namespace core
{

// Responsible for transition of entity
class MovementComponent
{
public:
  glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
  glm::vec3 speed = { 0.0f, 0.0f, 0.0f };
  glm::vec3 acc = { 0.0f, 0.0f, 0.0f };
};

// Responsible for rotation of entity
class RotationComponent
{
public:
  // Dont forget to normalize after modifying!!!
  glm::vec3 RotationAxis = { 0.0f, 1.0f, 0.0f };
  glm::vec3 RotationAxisRotationSpeed = { 0.0f, 0.0f, 0.0f };
  glm::vec3 RotationAxisRotationAcc = { 0.0f, 0.0f, 0.0f };

  // in radians
  GLfloat RotationDegreeDueAxis = 0;
  GLfloat RotationSpeedDueAxis = 0;
  GLfloat RotationAccDueAxis = 0;
};

class CoreEntity
{
private:
  Shader *mpShader = nullptr;

  Model::Model *mpModel = nullptr;
  glm::vec3 mModelScale = glm::vec3 (1.0f, 1.0f, 1.0f);

  core::HitBox *mpHitbox = nullptr;
  glm::vec3 mHitboxScale = glm::vec3 (1.0f, 1.0f, 1.0f);

  core::MovementComponent mMovComponent;
  core::RotationComponent mRotComponent;

public:
  CoreEntity ();
  CoreEntity (Model::Model &model, glm::vec3 modelScale, core::HitBox &hitbox,
              glm::vec3 hitboxScale, Shader &shader,
              core::MovementComponent mvcomp, core::RotationComponent rtcomp);
  virtual ~CoreEntity ();

  virtual void update (GLfloat deltaTime);

  const Shader *const getShader () const;
  const Model::Model *const getModel () const;
  const glm::vec3 *const getModelScale () const;
  const core::HitBox *const getHitbox () const;
  const glm::vec3 *const getHitboxScale () const;
  const core::MovementComponent *const getMovementComp () const;
  const core::RotationComponent *const getRotationComp () const;

  void setShader (Shader *const shader);
  void setModel (Model::Model *const modelptr);
  void setModelScale (const glm::vec3 &modelScale);
  void setHitbox (core::HitBox *const hitboxptr);
  void setHitboxScale (const glm::vec3 &hitboxscale);
  void setMovementComp (const core::MovementComponent &mvcomp);
  void setRotationComp (const core::RotationComponent &rtcomp);
};
} // namespace core
#endif
