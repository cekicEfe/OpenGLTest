#include "HitBox.h"
#include "ext/vector_float3.hpp"

// Generates a Hitbox by sort throughghhg nodes which kind of sucks
core::HitBox::HitBox() {}
core::HitBox::~HitBox() {}

void core::HitBox::GenerateHitbox(Model::Model *pModel) {}
void core::HitBox::GenerateDemoCube() {
  //
  for (GLuint i = 0; i < 2; i++) {
    for (GLuint j = 0; j < 2; j++) {
      for (GLuint k = 0; k < 2; k++) {
        //
        this->points.push_back(glm::vec3(1.0f * (i % 2 ? -1 : +1),
                                         1.0f * (j % 2 ? -1 : +1),
                                         1.0f * (k % 2 ? -1 : +1)));
        //
      }
    }
  }
  //
}
