#include <glad/glad.h>
//
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <model/Camera.h>
#include <model/Model.h>
#include <model/Shaders.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

#include <CoreClass/ErrorHandler/ErrorHandler.hpp>
#include <CoreClass/MainHandler/MainHandler.h>

#include <iostream>
#include <time.h>

int main(int argc, char **argv) {
  // initilizes glfw
  if (!glfwInit()) {
    std::cerr << "GLFW initialization failed!" << std::endl;
    auto out = core::ErrorHandler::OutOpenglError();
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // For antialising
  // glfwWindowHint(GLFW_SAMPLES, 4);

  // creates window
  GLFWwindow *window =
      glfwCreateWindow(core::MainHandler::returnSCR_WIDTH(),
                       core::MainHandler::returnSCR_HEIGHT(), "Thingmabob",
                       glfwGetPrimaryMonitor(), NULL);

  // checks if windows is created succesfully
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    auto out = core::ErrorHandler::OutOpenglError();

    glfwTerminate();
    return -1;
  }

  // creates sets window callbacks
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window,
                                 core::MainHandler::framebuffer_size_callback);
  glfwSetCursorPosCallback(window, core::MainHandler::mouse_callback);
  glfwSetScrollCallback(window, core::MainHandler::scroll_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // checks if glad is loaded or not
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // initializes Imgui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(
      window, true); // Second param install_callback=true will install GLFW
                     // callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();

  // sets rand seed
  srand(time(NULL));

  // Enables important optimization thingamabob
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  // For antialising
  glEnable(GL_MULTISAMPLE);

  while (!glfwWindowShouldClose(window)) {
    // for delta time
    static GLfloat localDeltaTime = 0;
    core::MainHandler::calculateDeltaTime();
    localDeltaTime = core::MainHandler::returnDeltaTime();

    // Checks for input
    core::MainHandler::processInput(window, localDeltaTime);
    // Show demo window! :)
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();

    // Show gui
    core::MainHandler::showGui();

    {
      ImGui::Begin("delete window");
      if (ImGui::Button("here")) {
        glfwDestroyWindow(window);
        // closes imgui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // closes glfw
        glfwTerminate();
        return 0;
      }
      ImGui::End();
    }

    // opengl related settings
    glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_BACK);

    // Render Things Check what it renders
    core::MainHandler::DrawInstanced();

    {
      static int call_count = 1;
      if (call_count == 1) {
        core::MainHandler::coreDemo();
        call_count = 0;
      }
    }

    // renders ImGui widgets
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // for opengl bufferswap
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // closes imgui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  // closes glfw
  glfwTerminate();
  return 0;
}
