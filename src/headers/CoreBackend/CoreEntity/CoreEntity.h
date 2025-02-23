#ifndef COREOBJECT_H
#define COREOBJECT_H

#include <GraphicsBackend/Model/Model.h>
#include <glm/gtc/quaternion.hpp>
#include <json/json.hpp>
#include <memory>

namespace core {

class CoreEntity {
private:
  std::weak_ptr<const Shader> mpShader;
  std::weak_ptr<const Model::Model> mpModel;

  glm::vec3 mModelScale = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::vec3 mPos = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 mRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
  GLfloat mRotDegreeRad = 0;

public:
  CoreEntity();
  CoreEntity(const std::shared_ptr<Model::Model> &model,
             const std::shared_ptr<Shader> &shader, const glm::vec3 &modelScale,
             const glm::vec3 &pos, const glm::vec3 &rot, const GLfloat &rotrad);
  virtual ~CoreEntity();

  const Model::Model *const getModel() const;
  const Shader *const getShader() const;
  const glm::vec3 &getModelScale() const;
  const glm::vec3 &getPos() const;
  const GLfloat &getRotRad() const;
  const glm::vec3 &getRotAxis() const;
  const glm::mat4 getUniformAlignment() const;

  void setShader(const std::shared_ptr<Shader> &shader);
  void setModel(std::shared_ptr<Model::Model> const modelptr);
  void setModelScale(const glm::vec3 &modelScale);
  void setPos(const glm::vec3 &pos);
  void setRotAxis(const glm::vec3 &rotAxis);
  void setRotRad(const GLfloat &rotRad);
};

} // namespace core
#endif
