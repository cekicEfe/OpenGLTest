#ifndef GAMECAMERA_HPP
#define GAMECAMERA_HPP

#include "model/Camera.h"

namespace testgame
{

class GameCamera : public Camera
{
private:
  bool stopCamera;

public:
  GameCamera (glm::vec3 position = glm::vec3 (0.0f, 0.0f, 0.0f),
              glm::vec3 up = glm::vec3 (0.0f, 1.0f, 0.0f), float yaw = YAW,
              float pitch = PITCH, bool isStopped = true);
  ~GameCamera ();

  /*
    we use this to determine that
    the camera should be changed or not
    true for no
    false for yes
    (kinda sucks but man);
  */
  void setStatus (bool status);
  bool returnStatus () const;
};

}

#endif
