#include "GameHandler.hpp"
#include "model/Camera.h"

using namespace testgame;

GameCamera GameHandler::mainCamera;

GameHandler::GameHandler ()
{
}

GameHandler::~GameHandler ()
{
}

const testgame::GameEntity *const
GameHandler::returnEntities () const
{
  return this->entities.data ();
}

const size_t
GameHandler::returnEntitiesSize () const
{
  return this->entities.size ();
}

const Model::Light *const
GameHandler::returnLights () const
{
  return this->lights.data ();
}

const size_t
GameHandler::returnLightsSize () const
{
  return this->lights.size ();
}

Camera const *const
GameHandler::returnCamera () const
{
  return &this->mainCamera;
}

void
GameHandler::update (GLfloat deltaTime)
{
}

void
GameHandler::mouse_callback (GLFWwindow *window, double xposIn, double yposIn)
{
  static double lastX = 0;
  static double lastY = 0;

  float ypos = static_cast<float> (yposIn);
  float xpos = static_cast<float> (xposIn);

  float xoffset = 0;
  float yoffset = 0;

  xoffset = xpos - lastX;
  yoffset = lastY - ypos; // reversed since y-coordinates go
                          // from bottom to top
  lastX = xpos;
  lastY = ypos;
  if (!mainCamera.returnStatus ())
    mainCamera.ProcessMouseMovement (xoffset, yoffset);
};

void
GameHandler::defaultFramebufferSizeCallback (GLFWwindow *, int width,
                                             int height)
{
  glViewport (0, 0, width, height);
};

void
GameHandler::processInput (GLFWwindow *window, GLfloat deltaTime)
{
  if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      if (mainCamera.returnStatus () == true)
        {
          mainCamera.setStatus (!mainCamera.returnStatus ());
          glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
      else
        {
          mainCamera.setStatus (!mainCamera.returnStatus ());
          glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
  if (glfwGetKey (window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    mainCamera.MovementSpeed = SPEED * 2;
  else
    mainCamera.MovementSpeed = SPEED;
  if (glfwGetKey (window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    mainCamera.MovementSpeed = SPEED / 2;
  else
    mainCamera.MovementSpeed = SPEED;
  if (glfwGetKey (window, GLFW_KEY_W) == GLFW_PRESS)
    mainCamera.ProcessKeyboard (FORWARD, deltaTime);
  if (glfwGetKey (window, GLFW_KEY_S) == GLFW_PRESS)
    mainCamera.ProcessKeyboard (BACKWARD, deltaTime);
  if (glfwGetKey (window, GLFW_KEY_A) == GLFW_PRESS)
    mainCamera.ProcessKeyboard (LEFT, deltaTime);
  if (glfwGetKey (window, GLFW_KEY_D) == GLFW_PRESS)
    mainCamera.ProcessKeyboard (RIGHT, deltaTime);
  if (glfwGetKey (window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    mainCamera.ProcessKeyboard (DOWNWARD, deltaTime);
  if (glfwGetKey (window, GLFW_KEY_SPACE) == GLFW_PRESS)
    mainCamera.ProcessKeyboard (UPWARD, deltaTime);
};

void
GameHandler::scrollCallback (GLFWwindow *window, double xoffset,
                             double yoffset)
{
  mainCamera.ProcessMouseScroll (static_cast<float> (yoffset));
};

GLfloat
GameHandler::calculateDeltaTime ()
{
  static GLfloat deltaTime = 0;
  static GLfloat lastFrame = 0;

  GLfloat currentFrame = static_cast<float> (glfwGetTime ());
  deltaTime = currentFrame - lastFrame;

  if (deltaTime >= 1.0f / 30.0f)
    {
      lastFrame = currentFrame;
    }

  return deltaTime;
}
