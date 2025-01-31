#ifndef COREOBJECT_H
#define COREOBJECT_H

#include <GraphicsBackend/Model/Model.h>
#include <glm/gtc/quaternion.hpp>
#include <json/json.hpp>

namespace core {

class CoreEntity {
protected:
  const Shader *mpShader = nullptr;
  const Model::Model *mpModel = nullptr;

  glm::vec3 mModelScale = glm::vec3(1.0f, 1.0f, 1.0f);

  glm::vec3 mPos = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 mRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
  GLfloat mRotDegreeRad = 0;

public:
  CoreEntity();
  CoreEntity(Model::Model &model, glm::vec3 modelScale, Shader &shader,
             glm::vec3 rot, GLfloat rotrad, glm::vec3 pos);
  virtual ~CoreEntity();

  const Shader *const getShader() const;
  const Model::Model *const getModel() const;
  const glm::vec3 &getModelScale() const;
  const glm::vec3 &getPos() const;
  const GLfloat &getRotRad() const;
  const glm::vec3 &getRotAxis() const;
  const glm::mat4 getUniformAlignment() const;

  void setShader(Shader *const shader);
  void setModel(Model::Model *const modelptr);
  void setModelScale(const glm::vec3 &modelScale);
  void setPos(const glm::vec3 &pos);
  void setRotAxis(const glm::vec3 &rotAxis);
  void setRotRad(const GLfloat &rotRad);
};

} // namespace core
#endif
