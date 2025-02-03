#ifndef GAMECAMERA_HPP
#define GAMECAMERA_HPP

#include "GraphicsBackend/Camera/Camera.h"

namespace testgame {

enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UPWARD,
  DOWNWARD,
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 1.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 15.0f;
const float FAR_SIGHT = 1000.0f;
const float CLOSE_SIGHT = 0.1f;
const float MAX_ZOOM = 45.0f; // 45.0f
const float MIN_ZOOM = 1.0f;  // 1.0f

class GameCamera : public Camera {
private:
  float MovementSpeed;
  float MouseSensitivity;

public:
  GameCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
             glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
             float pitch = PITCH, bool isStopped = true);
  ~GameCamera();

  void ProcessKeyboard(Camera_Movement direction, float deltaTime);
  void ProcessMouseMovement(float xoffset, float yoffset,
                            GLboolean constrainPitch = true);
  void ProcessMouseScroll(float yoffset);

  void setSpeed(GLfloat speed);
  GLfloat getSpeed() const;
};

} // namespace testgame

#endif
