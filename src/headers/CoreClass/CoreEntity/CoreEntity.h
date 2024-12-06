#ifndef COREOBJECT_H
#define COREOBJECT_H

#include <CoreClass/CoreClassPreDec.h>
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

  glm::vec3 mPos = glm::vec3 (0.0f, 0.0f, 0.0f);
  glm::quat mQuatRot = glm::quat (1.0f, { 0.0f, 0.0f, 0.0f });

public:
  CoreEntity ();
  CoreEntity (Model::Model &model, glm::vec3 modelScale, Shader &shader,
              glm::quat rot, glm::vec3 pos);
  virtual ~CoreEntity ();

  virtual void update (GLfloat deltaTime);

  const Shader *const getShader () const;
  const Model::Model *const getModel () const;
  const glm::vec3 &getModelScale () const;
  const glm::vec3 &getPos () const;
  const glm::quat &getRot () const;

  void setShader (Shader *const shader);
  void setModel (Model::Model *const modelptr);
  void setModelScale (const glm::vec3 &modelScale);
  void setPos (const glm::vec3 &pos);
  void setRot (const glm::quat &quat);
};

} // namespace core
#endif
