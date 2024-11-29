#ifndef COREOBJECT_H
#define COREOBJECT_H

#include <CoreClass/CoreClassPreDec.h>
#include <CoreClass/HitBox/HitBox.h>
#include <glm/gtc/quaternion.hpp>
#include <json/json.hpp>
#include <model/Model.h>

namespace core
{

class CoreEntity
{
private:
  Shader *mpShader = nullptr;

  Model::Model *mpModel = nullptr;
  glm::vec3 mModelScale = glm::vec3 (1.0f, 1.0f, 1.0f);

  core::HitBox *mpHitbox = nullptr;
  glm::vec3 mHitboxScale = glm::vec3 (1.0f, 1.0f, 1.0f);

  glm::vec3 mPos;
  glm::quat mQuatRot;

public:
  CoreEntity ();
  CoreEntity (Model::Model &model, glm::vec3 modelScale, core::HitBox &hitbox,
              glm::vec3 hitboxScale, Shader &shader, glm::quat rot,
              glm::vec3 pos);
  virtual ~CoreEntity () = 0;

  virtual void update (GLfloat deltaTime) = 0;

  const Shader *const getShader () const;
  const Model::Model *const getModel () const;
  const glm::vec3 *const getModelScale () const;
  const core::HitBox *const getHitbox () const;
  const glm::vec3 *const getHitboxScale () const;
  const glm::vec3 *const getPos () const;
  const glm::quat *const getRot () const;

  void setShader (Shader *const shader);
  void setModel (Model::Model *const modelptr);
  void setModelScale (const glm::vec3 &modelScale);
  void setHitbox (core::HitBox *const hitboxptr);
  void setHitboxScale (const glm::vec3 &hitboxscale);
  void setPos (const glm::vec3 &pos);
  void setRot (const glm::quat &quat);
};

} // namespace core
#endif
