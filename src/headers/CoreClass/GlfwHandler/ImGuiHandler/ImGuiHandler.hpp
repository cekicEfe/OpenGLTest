#ifndef IMGUI_HANDLER
#define IMGUI_HANDLER

#include <CoreClass/CoreClassPreDec.h>
#include <GLFW/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

namespace core
{

class ImGuiHandler
{
private:
  ImGuiHandler ();
  ~ImGuiHandler ();

  ImGuiHandler (ImGuiHandler &other) = delete;
  void operator= (const ImGuiHandler &) = delete;

  void initImGui (GLFWwindow *window) const;
  void initLoop ();
  void render ();
  void terminateImgui ();

public:
  friend class core::GlfwHandler;
};
} // namespace core

#endif
