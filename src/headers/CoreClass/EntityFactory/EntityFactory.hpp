#ifndef ENTITYFACTORY_HPP
#define ENTITYFACTORY_HPP

#include <CoreClass/CoreEntity/CoreEntity.h>
#include <CoreClass/HitBox/HitBox.h>
#include <CoreClass/OctTree/OctTree.hpp>
#include <model/Shaders.h>
#include <vector>

namespace core {
class EntityFactory {
public:
  std::vector<core::CoreEntity> entities;
  std::vector<core::HitBox> hitboxes;
  std::vector<Model::Model> models;
  std::vector<Shader> shaders;

  void emplace_backEntity(Model::Model *pmdl, Shader *shdr, core::HitBox *hitbx,
                          glm::vec3 modelscale, glm::vec3 hitboxscale,
                          core::MovementComponent mvcmp,
                          core::RotationComponent rtcmp);
  void emplace_backShader(std::string vertexPath, std::string fragPath);
  void emplace_backModel(std::string modelPath);
  void emplace_backHitbox();
};
} // namespace core

#endif
