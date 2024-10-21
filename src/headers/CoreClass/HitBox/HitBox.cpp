#include "HitBox.h"

// Generates a Hitbox by sort throughghhg nodes which kind of sucks
core::HitBox::HitBox() {}
core::HitBox::~HitBox() {}

void core::HitBox::GenerateHitbox(Model::Model *pModel) {}
void core::HitBox::GenerateDemoCube() {
  for (GLuint i = 0; i < 2; i++) {
    for (GLuint j = 0; j < 2; j++) {
      for (GLuint k = 0; k < 2; k++) {
        this->points.push_back(glm::vec3(0.5f * (i % 2 ? -1 : +1),
                                         0.5f * (j % 2 ? -1 : +1),
                                         0.5f * (k % 2 ? -1 : +1)));
        this->XMaxLenRadius = 0.5f;
        this->YMaxLenRadius = 0.5f;
        this->ZMaxLenRadius = 0.5f;
      }
    }
  }
}
