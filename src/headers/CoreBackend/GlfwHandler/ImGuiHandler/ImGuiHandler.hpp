#ifndef IMGUI_HANDLER
#define IMGUI_HANDLER

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace core {

class ImGuiHandler {
private:
public:
  ImGuiHandler();
  ~ImGuiHandler();

  void initImGui(GLFWwindow *window) const;
  void initLoop();
  void render();
  void terminateImgui();
};
} // namespace core

#endif
