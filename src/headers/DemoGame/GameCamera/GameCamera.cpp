#include "GameCamera.hpp"

testgame::GameCamera::GameCamera (glm::vec3 position, glm::vec3 up, float yaw,
                                  float pitch, bool stopCamera)
    : Camera (position, up, yaw, pitch)
{
  this->stopCamera = stopCamera;
}

testgame::GameCamera::~GameCamera ()
{
}

void
testgame::GameCamera::setStatus (bool status)
{
  this->stopCamera = status;
}

bool
testgame::GameCamera::returnStatus () const
{
  return this->stopCamera;
}
