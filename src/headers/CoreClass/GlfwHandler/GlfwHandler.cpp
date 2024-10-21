#include "GlfwHandler.hpp"

//
GLuint core::GlfwHandler::SCR_WIDTH = 1920;
GLuint core::GlfwHandler::SCR_HEIGHT = 1080;
GLfloat core::GlfwHandler::lastX = SCR_WIDTH / 2;
GLfloat core::GlfwHandler::lastY = SCR_WIDTH / 2;
GLboolean core::GlfwHandler::firstMouse = true;
GLuint core::GlfwHandler::counter = 0;
GLboolean core::GlfwHandler::simuFlag = false;
Camera core::GlfwHandler::mainCamera;
GLfloat core::GlfwHandler::deltaTime = 0.0f;
GLfloat core::GlfwHandler::lastFrame = 0.0f;

GLFWwindow *core::GlfwHandler::window = nullptr;
core::GlfwHandler *core::GlfwHandler::instance = nullptr;

// Main functions to init glfw :
//
void core::GlfwHandler::initGlfw() {
  std::cout << "Initializing glfw" << std::endl;
  if (!glfwInit()) {
    std::cerr << "GLFW initialization failed!" << std::endl;
    auto out = core::ErrorHandler::ReturnOpenglError();
    throw -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // glfwWindowHint(GLFW_SAMPLES, 4);

  // creates window
  std::cout << "Creating window" << std::endl;
  this->window = glfwCreateWindow(this->SCR_WIDTH, this->SCR_HEIGHT,
                                  "Thingmabob", glfwGetPrimaryMonitor(), NULL);

  // checks if windows is created succesfully
  if (this->window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    auto out = core::ErrorHandler::ReturnOpenglError();

    throw -1;
  }

  // creates sets window callbacks
  glfwMakeContextCurrent(this->window);
  glfwSetFramebufferSizeCallback(this->window,
                                 core::GlfwHandler::framebuffer_size_callback);
  glfwSetCursorPosCallback(this->window, core::GlfwHandler::mouse_callback);
  glfwSetScrollCallback(this->window, core::GlfwHandler::scroll_callback);
  glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // checks if glad is loaded or not
  std::cout << "Initializing GLAD" << std::endl;
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    throw -1;
  }

  std::cout << "Enabling optimizing and antialising" << std::endl;
  // For optimizing
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  // For antialising
  glEnable(GL_MULTISAMPLE);
}
void core::GlfwHandler::setLoopVariables() {
  glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCullFace(GL_BACK);
}
void core::GlfwHandler::swapBuffers() {
  // for opengl bufferswap
  glfwSwapBuffers(this->window);
  glfwPollEvents();
}
void core::GlfwHandler::terminateGlfw() {
  //
  std::cout << "Terminating glfw" << std::endl;
  glfwTerminate();
  //
}
GLFWwindow *core::GlfwHandler::returnWindow() {
  std::cout << "Returning glfw window pointer" << std::endl;
  if (this->window != nullptr) {
    return this->window;
  } else {
    return nullptr;
  }
}

// To create and delete instance

core::GlfwHandler::GlfwHandler() {}
core::GlfwHandler::~GlfwHandler() {}
core::GlfwHandler *core::GlfwHandler::createInstance() {
  std::cout << "Creating glfwHandler instance" << std::endl;
  if (core::GlfwHandler::instance == nullptr) {
    std::cout << "Returning Instance" << std::endl;
    core::GlfwHandler::instance = new core::GlfwHandler();
    return instance;
  } else {
    std::cout << "Instance already exists" << std::endl;
    return nullptr;
  }
}
void core::GlfwHandler::deleteInstance() {
  std::cout << "Starting to delete glfwInstance" << std::endl;
  if (core::GlfwHandler::instance != nullptr) {
    std::cout << "glfwInstance deleted succesfully" << std::endl;
    delete this->instance;
    this->instance = nullptr;
  } else {
    std::cout << "glfwInstance is not initialized" << std::endl;
  }
}
GLboolean core::GlfwHandler::checkWindowShouldClose() {
  return glfwWindowShouldClose(core::GlfwHandler::window);
}

void core::GlfwHandler::processInput(GLFWwindow *window, GLfloat deltaTime) {
  static GLfloat waitTime = 0.0f;
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && waitTime <= 0) {
    core::GlfwHandler::simuFlag = !core::GlfwHandler::simuFlag;
    core::GlfwHandler::firstMouse = true;
    glfwSetCursorPos(window, core::GlfwHandler::SCR_WIDTH / 2,
                     core::GlfwHandler::SCR_HEIGHT / 2);
    waitTime = 0.35f;
  }
  if (core::GlfwHandler::simuFlag) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
      core::GlfwHandler::mainCamera.MovementSpeed = SPEED * 2;
    else
      core::GlfwHandler::mainCamera.MovementSpeed = SPEED;
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
      core::GlfwHandler::mainCamera.MovementSpeed = SPEED / 2;
    else
      core::GlfwHandler::mainCamera.MovementSpeed = SPEED;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      core::GlfwHandler::mainCamera.ProcessKeyboard(
          FORWARD, core::GlfwHandler::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      core::GlfwHandler::mainCamera.ProcessKeyboard(
          BACKWARD, core::GlfwHandler::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      core::GlfwHandler::mainCamera.ProcessKeyboard(
          LEFT, core::GlfwHandler::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      core::GlfwHandler::mainCamera.ProcessKeyboard(
          RIGHT, core::GlfwHandler::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
      core::GlfwHandler::mainCamera.ProcessKeyboard(
          DOWNWARD, core::GlfwHandler::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      core::GlfwHandler::mainCamera.ProcessKeyboard(
          UPWARD, core::GlfwHandler::deltaTime);
  } else {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
  // decreases wait time
  if (waitTime - deltaTime <= 0) // somehow
    waitTime = 0;
  else
    waitTime -= deltaTime;
}
void core::GlfwHandler::mouse_callback(GLFWwindow *window, double xposIn,
                                       double yposIn) {
  float ypos = static_cast<float>(yposIn);
  float xpos = static_cast<float>(xposIn);

  float xoffset = 0;
  float yoffset = 0;

  if (core::GlfwHandler::simuFlag) {
    if (core::GlfwHandler::firstMouse) {
      core::GlfwHandler::lastX = xpos;
      core::GlfwHandler::lastY = ypos;
      core::GlfwHandler::firstMouse = false;
    } else {
      xoffset = xpos - core::GlfwHandler::lastX;
      yoffset = core::GlfwHandler::lastY -
                ypos; // reversed since y-coordinates go from bottom to top

      core::GlfwHandler::lastX = xpos;
      core::GlfwHandler::lastY = ypos;
    }

    core::GlfwHandler::mainCamera.ProcessMouseMovement(xoffset, yoffset);
  }
}
void core::GlfwHandler::framebuffer_size_callback(GLFWwindow *window, int width,
                                                  int height) {
  glViewport(0, 0, width, height);
}
void core::GlfwHandler::scroll_callback(GLFWwindow *window, double xoffset,
                                        double yoffset) {
  if (core::GlfwHandler::simuFlag)
    core::GlfwHandler::mainCamera.ProcessMouseScroll(
        static_cast<float>(yoffset));
}
void core::GlfwHandler::calculateDeltaTime() {
  float currentFrame = static_cast<float>(glfwGetTime());
  core::GlfwHandler::deltaTime = currentFrame - core::GlfwHandler::lastFrame;
  core::GlfwHandler::counter++;

  if (core::GlfwHandler::deltaTime >= 1.0f / 30.0f) {
    core::GlfwHandler::lastFrame = currentFrame;
    core::GlfwHandler::counter = 0;
  }
}
GLfloat core::GlfwHandler::returnDeltaTime() {
  return core::GlfwHandler::deltaTime;
}
