#ifndef CAMERA_H
#define CAMERA_H

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/trigonometric.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

// An abstract camera class that processes input and calculates the
// corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {
protected:
  // camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  float Zoom = 15.0f;
  float CloseSight = 0.1f;
  float FarSight = 1000.f;

  // euler Angles
  float Yaw;
  float Pitch;
  // constructor with vectors
public:
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90,
         float pitch = 0.0)
      : Front(glm::vec3(0.0f, 0.0f, -1.0f)) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
  }

  // returns the view matrix calculated using Euler Angles and the LookAt
  // Matrix
  glm::vec3 GetPos() const { return this->Position; }

  void SetPos(glm::vec3 pos) { this->Position = pos; }

  glm::vec3 GetFront() const { return this->Front; }

  glm::mat4 GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
  }

  glm::mat4 GetProjection(GLfloat aspect) const {
    return glm::perspective(glm::radians(this->Zoom), aspect, CloseSight,
                            FarSight);
  }

  const float &getCloseSight() const { return this->CloseSight; }

  const float &getFarSight() const { return this->FarSight; }

  const float &getZoom() const { return this->Zoom; }

  void setCloseSight(float close_sight) {
    if (close_sight < this->FarSight)
      this->CloseSight = close_sight;
    else
      throw std::invalid_argument(
          "Camera : given close_sight value is bigger than far sight value");
  }

  void setFarSight(float far_sight) {
    if (far_sight > this->CloseSight)
      this->FarSight = far_sight;
    else
      throw std::invalid_argument(
          "Camera : given far_sight value is smaller than close sight value");
  }

  void setZoom(float zoom) {
    if (zoom > 1.0f)
      this->Zoom = zoom;
    else
      throw std::invalid_argument("Camera : given zoom value is not valid");
  }

protected:
  // calculates the front vector from the Camera's (updated) Euler Angles
  void updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(
        Front, WorldUp)); // normalize the vectors, because their length gets
                          // closer to 0 the more you look up or down which
                          // results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
  }
};
#endif
