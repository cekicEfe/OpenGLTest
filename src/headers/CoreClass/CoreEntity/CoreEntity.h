#ifndef COREOBJECT_H
#define COREOBJECT_H

#include <CoreClass/CoreClassPreDec.h>
#include <CoreClass/HitBox/HitBox.h>
#include <glm/gtc/quaternion.hpp>
#include <json/json.hpp>
#include <memory>
#include <model/Model.h>
#include <vector>

namespace core {

// Responsible for transition of entity
class MovementComponent {
public:
  glm::vec3 pos = {0.0f, 0.0f, 0.0f};
  glm::vec3 speed = {0.0f, 0.0f, 0.0f};
  glm::vec3 acc = {0.0f, 0.0f, 0.0f};
};

// Responsible for rotation of entity
class RotationComponent {
public:
  // Dont forget to normalize after modifying!!!
  glm::vec3 RotationAxis = {0.0f, 1.0f, 0.0f};
  glm::vec3 RotationAxisRotationSpeed = {0.0f, 0.0f, 0.0f};
  glm::vec3 RotationAxisRotationAcc = {0.0f, 0.0f, 0.0f};

  // in radians
  GLfloat RotationDegreeDueAxis = 0;
  GLfloat RotationSpeedDueAxis = 0;
  GLfloat RotationAccDueAxis = 0;
};

class CoreEntity {
public:
  CoreEntity();
  virtual ~CoreEntity();

  Model::Model *pModel = nullptr;
  glm::vec3 modelScale = glm::vec3(1.0f, 1.0f, 1.0f);
  core::HitBox *pHitbox = nullptr;
  glm::vec3 hitboxScale = glm::vec3(1.0f, 1.0f, 1.0f);
  Shader *pShader = nullptr;

  core::MovementComponent movComponent;
  core::RotationComponent rotComponent;

  virtual void update(GLfloat deltaTime);
};
} // namespace core
#endif // !SCRIPTOBJECT
