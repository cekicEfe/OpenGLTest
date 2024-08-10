#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <model/Camera.h>
#include <model/Model.h>
#include <model/Shaders.h>

#include <CoreClass/CoreClass.h>
#include <CoreClass/CoreEntity/CoreEntity.h>
#include <CoreClass/RenderFunctor/RenderFunctor.h>
#include <CoreClass/JsonExtractor/JsonExtractor.h>

#include <json/json.hpp>
#include <filesystem>
#include <imgui/imgui.h>
#include <vector>
#include "MyPaths.h"

namespace core
{

    class MainHandlerVariables
    {
    private:
        const GLuint SCR_WIDTH = 1920;
        const GLuint SCR_HEIGHT = 1080;
        Camera mainCamera;
        GLfloat lastX = SCR_WIDTH / 2.0f;
        GLfloat lastY = SCR_HEIGHT / 2.0f;
        GLboolean firstMouse = true;
        GLuint counter = 0;
        GLboolean simuFlag = false;
        GLfloat deltaTime = 0.0f;
        GLfloat lastFrame = 0.0f;
        friend class MainHandler;
    } static MainHandlerVariables;

    class MainHandler
    {
    private: 
        static std::vector<std::unique_ptr<Model::Model>> msObjectModels;
        static std::vector<std::unique_ptr<core::CoreEntity>> msEntities;
        static std::map<Model::Model*,std::vector<core::CoreEntity*>> msModelEntityMap;

        static std::vector<std::unique_ptr<nlohmann::json>> msJsonScenes;
        static std::vector<std::unique_ptr<nlohmann::json>> msJsonPrecepts;
        static std::vector<std::unique_ptr<Model::Light>> msLights;
        static std::vector<std::unique_ptr<Shader>> msShaders;

        //these hold just path
        static std::vector<std::string> msShaderPaths;
        static std::vector<std::string> msJsonPreceptPaths;
        static std::vector<std::string> msJsonScenePaths;

        static void addCoreEntity();
        static void addCoreEntity(Model::Model* entityModel);
        
        static void loadAllScenePaths();
        static void loadAllShaderPaths();
        static void loadAllJsonPrecepts();
        static void loadAllJsonPreceptPath();
        static void loadAllModels();
        

    public:
        MainHandler();
        ~MainHandler();

        static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
        static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
        static void processInput(GLFWwindow *window, GLfloat deltaTime);

        static void saveSceneAsJson(std::string fileName , GLboolean overwriteOption);
        static void loadSceneFromJson(std::string filename);

        static void DrawInstanced();
        static void DrawInstancedWithInterval(GLfloat deltaTime,GLfloat intervalMS);

        static void showGui();

        static void calculateDeltaTime();
        static GLfloat returnDeltaTime();

        static GLuint returnSCR_WIDTH();
        static GLuint returnSCR_HEIGHT();
    };

}

#endif