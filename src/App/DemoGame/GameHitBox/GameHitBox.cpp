#include "GameHitBox.hpp"

// Generates a Hitbox by sorting through nodes
testgame::GameHitBox::GameHitBox() {}

testgame::GameHitBox::~GameHitBox() {}

testgame::GameHitBox::GameHitBox(std::string hitboxName) {
  this->hitboxName = hitboxName;
}
