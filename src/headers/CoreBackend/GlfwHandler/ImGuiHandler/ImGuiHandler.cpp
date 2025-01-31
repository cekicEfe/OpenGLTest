#include "ImGuiHandler.hpp"
#include <iostream>

core::ImGuiHandler::ImGuiHandler() {}
core::ImGuiHandler::~ImGuiHandler() {}

void core::ImGuiHandler::initImGui(GLFWwindow *window) const {
  std::cout << "Initializing imgui at core::ImGuiHandler::initImGui"
            << std::endl;
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  // # Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(
      window, true); // Second param install_callback=true will install GLFW
                     // callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();
}

void core::ImGuiHandler::initLoop() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  // ImGui::ShowDemoWindow();
}

void core::ImGuiHandler::render() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void core::ImGuiHandler::terminateImgui() {
  std::cout << "Terminating imgui at core::ImGuiHandler::terminateImgui()"
            << std::endl;
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
