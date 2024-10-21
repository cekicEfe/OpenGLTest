#include <glad/glad.h>
//
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
#include <CoreClass/GlfwHandler/GlfwHandler.hpp>
#include <CoreClass/MathConstants/MathContstants.hpp>

#include <iostream>
#include <time.h>

int main(int argc, char **argv) {

  core::GlfwHandler *glfwHandler = core::GlfwHandler::createInstance();
  try {
    glfwHandler->initGlfw();
  } catch (...) {
    std::cout << "Program exited unexpectedly" << std::endl;
    return -1;
  }
  GLFWwindow *window = glfwHandler->returnWindow();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(
      window, true); // Second param install_callback=true will install GLFW
                     // callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();

  srand(time(NULL));

  // Main loop
  while (!glfwHandler->checkWindowShouldClose()) {

    static GLfloat localDeltaTime = 0;
    glfwHandler->calculateDeltaTime();
    localDeltaTime = glfwHandler->returnDeltaTime();

    glfwHandler->processInput(window, localDeltaTime);

    // Show demo window! :)
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();

    // Close window
    {
      ImGui::Begin("delete window");
      if (ImGui::Button("here")) {
        glfwDestroyWindow(window);

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwTerminate();
        return 0;
      }
      ImGui::End();
    }

    glfwHandler->setLoopVariables();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwHandler->swapBuffers();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwHandler->terminateGlfw();
  glfwHandler->deleteInstance();

  return 0;
}
