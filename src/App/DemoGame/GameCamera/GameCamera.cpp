#include "GameCamera.hpp"
#include <stdexcept>

testgame::GameCamera::GameCamera(glm::vec3 position, glm::vec3 up, float yaw,
                                 float pitch, bool stopCamera)
    : Camera(position, up, yaw, pitch), MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY) {}

testgame::GameCamera::~GameCamera() {}

void testgame::GameCamera::ProcessKeyboard(testgame::Camera_Movement direction,
                                           GLfloat deltaTime) {
  float velocity = MovementSpeed * deltaTime;
  if (direction == FORWARD)
    Position += Front * velocity;
  if (direction == BACKWARD)
    Position -= Front * velocity;
  if (direction == LEFT)
    Position -= Right * velocity;
  if (direction == RIGHT)
    Position += Right * velocity;

  if (direction == DOWNWARD)
    Position -= WorldUp * velocity;
  if (direction == UPWARD)
    Position += WorldUp * velocity;
}

void testgame::GameCamera::ProcessMouseMovement(float xoffset, float yoffset,
                                                GLboolean constrainPitch) {
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  Yaw += xoffset;
  Pitch += yoffset;

  // make sure that when pitch is out of bounds, screen doesn't get flipped
  if (constrainPitch) {
    if (Pitch > 89.0f)
      Pitch = 89.0f;
    if (Pitch < -89.0f)
      Pitch = -89.0f;
  }

  // update Front, Right and Up Vectors using the updated Euler angles
  updateCameraVectors();
}

void testgame::GameCamera::ProcessMouseScroll(float yoffset) {
  Zoom -= (float)yoffset;
  if (Zoom < MIN_ZOOM)
    Zoom = MIN_ZOOM;
  if (Zoom > MAX_ZOOM)
    Zoom = MAX_ZOOM;
}

void testgame::GameCamera::setSpeed(GLfloat speed) {
  this->MovementSpeed = speed;
}

GLfloat testgame::GameCamera::getSpeed() const { return this->MovementSpeed; }
