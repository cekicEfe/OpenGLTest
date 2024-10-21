#include "CoreEntity.h"
#include "CoreClass/MathConstants/MathContstants.hpp"

void core::CoreEntity::update(GLfloat deltaTime) {
  this->movComponent.speed += this->movComponent.acc * deltaTime;
  this->movComponent.pos += this->movComponent.speed * deltaTime;
  this->movComponent.acc = {0.0f, 0.0f, 0.0f};

  //  this->rotComponent.rotSpeed += this->rotComponent.rotAcc * deltaTime;
  //  this->rotComponent.rotPos += this->rotComponent.rotSpeed * deltaTime;
  /*
    // this is cursed sadly
    this->rotComponent.rotPos.x <= -core::constants::core_pi
        ? this->rotComponent.rotPos.x += 2 * core::constants::core_pi
        : this->rotComponent.rotPos.x;
    this->rotComponent.rotPos.x >= core::constants::core_pi
        ? this->rotComponent.rotPos.x -= 2 * core::constants::core_pi
        : this->rotComponent.rotPos.x;

    this->rotComponent.rotPos.y <= -core::constants::core_pi
        ? this->rotComponent.rotPos.y += 2 * core::constants::core_pi
        : this->rotComponent.rotPos.y;
    this->rotComponent.rotPos.y >= core::constants::core_pi
        ? this->rotComponent.rotPos.y -= 2 * core::constants::core_pi
        : this->rotComponent.rotPos.y;

    this->rotComponent.rotPos.z <= -core::constants::core_pi
        ? this->rotComponent.rotPos.z += 2 * core::constants::core_pi
        : this->rotComponent.rotPos.z;
    this->rotComponent.rotPos.z >= core::constants::core_pi
        ? this->rotComponent.rotPos.z -= 2 * core::constants::core_pi
        : this->rotComponent.rotPos.z;
  */
}
core::CoreEntity::CoreEntity() {}
core::CoreEntity::~CoreEntity() {}
