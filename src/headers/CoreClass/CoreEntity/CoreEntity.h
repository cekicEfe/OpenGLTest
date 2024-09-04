#ifndef COREOBJECT_H
#define COREOBJECT_H

#include <CoreClass/CoreClassPreDec.h>
#include <glm/gtc/quaternion.hpp>
#include <json/json.hpp>
#include <memory>
#include <model/Model.h>
#include <vector>

namespace core {
class CoreEntity {
public:
  CoreEntity();
  virtual ~CoreEntity();

  virtual nlohmann::json saveAsJson();
  virtual void update(GLfloat deltaTime);

  Model::Model *model = nullptr;
  glm::vec3 modelScale = glm::vec3(1.0f);
  glm::vec3 pos = glm::vec3(0.0f);
  glm::vec3 rotAxis = glm::vec3(1.0f, 0.0f, 0.0f);
  GLfloat rotDegreeRad = 0;
};
} // namespace core
#endif // !SCRIPTOBJECT
