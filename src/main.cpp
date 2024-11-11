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
#include <CoreClass/OctTree/OctTree.hpp>

#include <iostream>
#include <time.h>

int
main (int argc, char **argv)
{
  core::GlfwHandler *glfwHandler = core::GlfwHandler::createInstance ();
  try
    {
      glfwHandler->initGlfw ();
    }
  catch (...)
    {
      std::cout << "Program exited unexpectedly" << std::endl;
      return -1;
    }
  GLFWwindow *window = glfwHandler->returnWindow ();

  IMGUI_CHECKVERSION ();
  ImGui::CreateContext ();
  ImGuiIO &io = ImGui::GetIO ();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL (
      window, true); // Second param install_callback=true will install GLFW
                     // callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init ();

  // For random things
  srand (time (NULL));

  // Demo
  // No entity should have a pos vec component magnitute bigger than 20 !!!
  core::OctTreeNode test (glm::vec3 (0.0f, 0.0f, 0.0f), 20, "Origin//");

  core::CoreEntity entity1;
  core::MovementComponent mvcomp;
  mvcomp.pos = { 1.0, 3.0f, 15.0f };
  entity1.setMovementComp (mvcomp);

  core::CoreEntity entity2;
  mvcomp.pos = { 3.0f, 5.0f, 1.0f };
  entity2.setMovementComp (mvcomp);

  core::CoreEntity entity3;
  mvcomp.pos = { 5.0f, -5.0f, -5.0f };
  entity3.setMovementComp (mvcomp);

  core::CoreEntity entity4;
  mvcomp.pos = { 11.0f, 12.0f, -13.0f };
  entity4.setMovementComp (mvcomp);

  test.insertEntity (&entity1);
  test.insertEntity (&entity2);
  test.insertEntity (&entity3);
  test.insertEntity (&entity4);
  test.printChildsRecursivly ();
  // End of Demo

  // Main loop
  while (!glfwHandler->checkWindowShouldClose ())
    {
      static GLfloat localDeltaTime = 0;
      glfwHandler->calculateDeltaTime ();
      localDeltaTime = glfwHandler->returnDeltaTime ();

      glfwHandler->processInput (window, localDeltaTime);

      // Show demo window! :)
      ImGui_ImplOpenGL3_NewFrame ();
      ImGui_ImplGlfw_NewFrame ();
      ImGui::NewFrame ();
      ImGui::ShowDemoWindow ();

      // Close program
      {
        ImGui::Begin ("Close program");
        if (ImGui::Button ("Close"))
          {
            // Here lies a warcrime
            goto END_PROGRAM;
          }
        ImGui::End ();
      }

      // Render should be made after here
      glfwHandler->setLoopVariables ();

      ImGui::Render ();
      ImGui_ImplOpenGL3_RenderDrawData (ImGui::GetDrawData ());

      glfwHandler->swapBuffers ();
      glfwHandler->pollEvents ();
    }

END_PROGRAM:
  ImGui_ImplOpenGL3_Shutdown ();
  ImGui_ImplGlfw_Shutdown ();
  ImGui::DestroyContext ();

  glfwHandler->terminateGlfw ();
  glfwHandler->deleteInstance ();
  std::cout << "Good bye" << std::endl;

  return 0;
}
