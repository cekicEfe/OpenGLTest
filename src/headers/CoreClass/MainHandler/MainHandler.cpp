#include "MainHandler.h"

std::vector<std::unique_ptr<core::CoreEntity>> core::MainHandler::msEntities;
std::vector<std::unique_ptr<Model::Model>> core::MainHandler::msObjectModels;
std::map<Model::Model *, std::vector<core::CoreEntity *>> core::MainHandler::msModelEntityMap;

std::vector<std::string> core::MainHandler::msJsonScenePaths;
std::vector<std::string> core::MainHandler::msJsonPreceptPaths;
std::vector<std::string> core::MainHandler::msShaderPaths;

std::vector<std::unique_ptr<Model::Light>> core::MainHandler::msLights;
std::vector<std::unique_ptr<Shader>> core::MainHandler::msShaders;

std::vector<std::unique_ptr<nlohmann::json>> core::MainHandler::msJsonScenes;
std::vector<std::unique_ptr<nlohmann::json>> core::MainHandler::msJsonPrecepts;



// Gui related functions
void core::MainHandler::showGui()
{
    if (!MainHandlerVariables.simuFlag)
    {
        ImGui::Begin("Main Menu");

        ImGui::BeginGroup();
        if (ImGui::CollapsingHeader("Entity Config"))
        {
            ImGui::Indent();
            if (ImGui::CollapsingHeader("Entity Creation"))
            {
                ImGui::Indent();

                if (ImGui::Button("Add Entity To Back"))
                {
                    core::MainHandler::addCoreEntity();
                }

                static int localEntityChoice = -1;

                ImGui::InputInt("Input Entity to destroy", &localEntityChoice);

                if (ImGui::Button("Delete Entity"))
                {
                    if (core::MainHandler::msEntities.size() > 0 && core::MainHandler::msEntities.size() >= localEntityChoice && localEntityChoice > 0)
                    {
                        core::MainHandler::msEntities.erase(core::MainHandler::msEntities.begin() + localEntityChoice - 1);
                    }
                }

                ImGui::BeginGroup();
                if (ImGui::CollapsingHeader("Entity List") && core::MainHandler::msEntities.size() > 0)
                {
                    ImGui::Indent();
                    for (size_t i = 0; i < core::MainHandler::msEntities.size(); i++)
                    {
                        std::string headerLabel = "Entity " + std::to_string(i + 1);

                        if (ImGui::CollapsingHeader(headerLabel.c_str()))
                        {
                            static int localChoice = 0;
                            ImGui::InputInt(("Input new model id for " + headerLabel).c_str(), &localChoice);
                            if (ImGui::Button(("Assign new model to " + headerLabel).c_str()) && localChoice <= core::MainHandler::msObjectModels.size() && localChoice > 0)
                            {
                                core::MainHandler::msEntities.at(i).get()->mpModel = core::MainHandler::msObjectModels.at(localChoice - 1).get();
                            }

                            auto ptr = core::MainHandler::msEntities.at(i).get();
                            ImGui::BulletText("objects address : %p", ptr);
                            ImGui::BulletText("objects position : x:%f y:%f z:%f ", ptr->mPos.x, ptr->mPos.y, ptr->mPos.z);
                            if (ptr->mpModel != nullptr)
                                ImGui::BulletText("objects models address : %p", ptr->mpModel);
                            if (ptr->mpModel != nullptr)
                                ImGui::BulletText("objects models directory : %s", ptr->mpModel->directory.c_str());

                            ImGui::SliderFloat((headerLabel + " position x").c_str(), &core::MainHandler::msEntities.at(i).get()->mPos.x, -100.0f, 100.0f);
                            ImGui::SliderFloat((headerLabel + " position y").c_str(), &core::MainHandler::msEntities.at(i).get()->mPos.y, -100.0f, 100.0f);
                            ImGui::SliderFloat((headerLabel + " position z").c_str(), &core::MainHandler::msEntities.at(i).get()->mPos.z, -100.0f, 100.0f);
                            ImGui::SliderFloat((headerLabel + " rot degree ").c_str(), &core::MainHandler::msEntities.at(i).get()->mRotDegreeRad, -2 * glm::pi<GLfloat>(), 2 * glm::pi<GLfloat>());
                        }
                    }
                }
                ImGui::EndGroup();

                if (ImGui::Button("Load ALL Model Files"))
                {
                    core::SaveLoadHandler::loadAllModels(&core::MainHandler::msObjectModels);
                }

                ImGui::BeginGroup();
                if (ImGui::CollapsingHeader("Entity Models") && core::MainHandler::msObjectModels.size() > 0)
                {
                    ImGui::Indent();
                    for (size_t i = 0; i < core::MainHandler::msObjectModels.size(); i++)
                    {
                        std::string headerLabel = "Model " + std::to_string(i + 1);

                        if (ImGui::CollapsingHeader(headerLabel.c_str()))
                        {
                            ImGui::BulletText("Model address : %p", core::MainHandler::msObjectModels.at(i).get());
                            ImGui::BulletText("Model directory : %s", core::MainHandler::msObjectModels.at(i).get()->directory.c_str());
                        }
                    }
                }
                ImGui::EndGroup();
            }
        }
        ImGui::EndGroup();

        ImGui::BeginGroup();
        if (ImGui::CollapsingHeader("Main Shader Config"))
        {
            ImGui::Indent();
            ImGui::BeginGroup();
            if (ImGui::Button("Load ALL shader paths"))
            {
                core::SaveLoadHandler::loadAllShaderPaths(&core::MainHandler::msShaderPaths);
            }
            ImGui::EndGroup();

            ImGui::BeginGroup();
            if (ImGui::CollapsingHeader("Shader related files") && core::MainHandler::msShaderPaths.size() > 0)
            {
                ImGui::Indent();
                ImGui::BeginGroup();
                for (GLuint i = 0; i < msShaderPaths.size(); i++)
                {
                    ImGui::BulletText("%d %s", i + 1, msShaderPaths.at(i).c_str());
                }
                ImGui::EndGroup();
            }
            ImGui::EndGroup();

            ImGui::BeginGroup();
            if (ImGui::CollapsingHeader("Shader creation menu"))
            {
                static int sVertIndex = 0;
                static int sFragIndex = 0;
                static std::string vertShaderPath;
                static std::string fragShaderPath;

                ImGui::Indent();
                ImGui::BeginGroup();
                ImGui::InputInt("Input vertshader index", &sVertIndex);
                ImGui::InputInt("Input fragshader index", &sFragIndex);
                if (ImGui::Button("Make Shader"))
                {
                    if ((sVertIndex - 1 < core::MainHandler::msShaderPaths.size() && sVertIndex - 1 >= 0 && core::MainHandler::msShaderPaths.size() > 0) && (sFragIndex - 1 < core::MainHandler::msShaderPaths.size() && sFragIndex - 1 >= 0 && core::MainHandler::msShaderPaths.size() > 0))
                    {
                        vertShaderPath = core::MainHandler::msShaderPaths.at(sVertIndex - 1);
                        fragShaderPath = core::MainHandler::msShaderPaths.at(sFragIndex - 1);
                        core::MainHandler::msShaders.push_back(std::make_unique<Shader>(vertShaderPath.c_str(), fragShaderPath.c_str()));
                    }
                }
                ImGui::EndGroup();

                ImGui::BeginGroup();
                if (ImGui::Button("Pop Shaders from Back"))
                {
                    if (core::MainHandler::msShaders.size() > 0)
                        core::MainHandler::msShaders.pop_back();
                }
                ImGui::EndGroup();

                ImGui::BeginGroup();
                if (ImGui::CollapsingHeader("Shader List") && core::MainHandler::msShaders.size() > 0)
                {
                    ImGui::Indent();
                    for (GLuint i = 0; i < core::MainHandler::msShaders.size(); i++)
                    {
                        ImGui::BulletText("Shader address : %p", core::MainHandler::msShaders.at(i).get());
                    }
                }
                ImGui::EndGroup();
            }
            ImGui::EndGroup();
        }
        ImGui::EndGroup();

        ImGui::BeginGroup();
        if (ImGui::CollapsingHeader("Light Config"))
        {
            ImGui::Indent();
            if (ImGui::Button("Create Point Light"))
            {
                core::MainHandler::msLights.push_back(std::make_unique<Model::Light>());
            }
            static int localLightChoice = -1;
            ImGui::InputInt("Input Light to destroy", &localLightChoice);
            if (ImGui::Button("Delete Light"))
            {
                if ((core::MainHandler::msLights.size() > 0) && localLightChoice > 0 && core::MainHandler::msLights.size() >= localLightChoice)
                {
                    core::MainHandler::msLights.erase(core::MainHandler::msLights.begin() + (localLightChoice - 1));
                    localLightChoice = -1;
                }
            }

            ImGui::BeginGroup();
            if (ImGui::CollapsingHeader("Light List") && core::MainHandler::msLights.size() > 0)
            {
                ImGui::Indent();
                for (GLuint i = 0; i < core::MainHandler::msLights.size(); i++)
                {
                    std::string headerLabel = "Light " + std::to_string(i + 1);
                    if (ImGui::CollapsingHeader(headerLabel.c_str()))
                    {
                        ImGui::SliderFloat((headerLabel + " Position x").c_str(), &core::MainHandler::msLights.at(i).get()->light_pos.x, -100.0f, 100.0f);
                        ImGui::SliderFloat((headerLabel + " Position y").c_str(), &core::MainHandler::msLights.at(i).get()->light_pos.y, -100.0f, 100.0f);
                        ImGui::SliderFloat((headerLabel + " Position z").c_str(), &core::MainHandler::msLights.at(i).get()->light_pos.z, -100.0f, 100.0f);
                        ImGui::SliderFloat((headerLabel + " Color r ").c_str(), &core::MainHandler::msLights.at(i).get()->light_color.x, 0.0f, 1.0f);
                        ImGui::SliderFloat((headerLabel + " Color g ").c_str(), &core::MainHandler::msLights.at(i).get()->light_color.y, 0.0f, 1.0f);
                        ImGui::SliderFloat((headerLabel + " Color b ").c_str(), &core::MainHandler::msLights.at(i).get()->light_color.z, 0.0f, 1.0f);
                    }
                }
            }
            ImGui::EndGroup();
        }
        ImGui::EndGroup();

        /*
        ImGui::BeginGroup();
        if (ImGui::CollapsingHeader("Json precept config"))
        {
            ImGui::Indent();
            ImGui::BeginGroup();
            if (ImGui::CollapsingHeader("Json precept path config"))
            {
                ImGui::Indent();

                ImGui::BeginGroup();
                if (ImGui::Button("Load ALL Json Precept paths"))
                {
                    core::SaveLoadHandler::loadAllJsonPreceptPath(&core::MainHandler::msJsonPreceptPaths);
                }
                ImGui::EndGroup();

                ImGui::BeginGroup();
                if (ImGui::CollapsingHeader("Loaded Json Precept Paths") && core::MainHandler::msJsonPreceptPaths.size() > 0)
                {
                    ImGui::Indent();
                    ImGui::BeginGroup();
                    for (GLuint i = 0; i < core::MainHandler::msJsonPreceptPaths.size(); i++)
                    {
                        std::string headerLabel = core::MainHandler::msJsonPreceptPaths.at(i);
                        ImGui::BulletText(headerLabel.c_str());
                    }
                    ImGui::EndGroup();
                }
                ImGui::EndGroup();
            }
            ImGui::EndGroup();
        }
        ImGui::EndGroup();
        */

        ImGui::BeginGroup();
        if (ImGui::CollapsingHeader("Save/Load config"))
        {
            ImGui::Indent();

            ImGui::Text("Load config :");
            
            //Loads saved paths
            if (ImGui::Button("Load all save paths"))
                core::SaveLoadHandler::loadAllJsonScenePaths(&core::MainHandler::msJsonScenePaths);
            
            //Shows all loaded paths
            ImGui::BeginGroup();
            if (ImGui::CollapsingHeader("Saved paths"))
            {
                ImGui::Indent();
                //loaded paths
                for (GLuint i = 0; i < core::MainHandler::msJsonScenePaths.size(); i++)
                    ImGui::BulletText(core::MainHandler::msJsonScenePaths.at(i).c_str());
            }
            ImGui::EndGroup();

            //Filename var 
            static char fileName[100];
            ImGui::InputText("Enter file name to load from", fileName , 100);
            //Loads a save with parameters
            if(ImGui::Button("Load save file") && strcmp(fileName,"") && std::filesystem::exists(cJsonScenesPath+fileName+cJsonExtension))
            {
                core::SaveLoadHandler::loadSceneFromJson(fileName,
                                                        &core::MainHandler::msObjectModels,
                                                        &core::MainHandler::msShaders,
                                                        &core::MainHandler::msEntities,
                                                        &core::MainHandler::msLights);
                strcpy(fileName,"");
            }


            ImGui::Text("Save config :");
            static char saveNameToSave[100];
            ImGui::InputText("Enter file name to save",saveNameToSave,IM_ARRAYSIZE(saveNameToSave));
            static bool optionOverwrite = false;
            ImGui::Checkbox("Overwrite ?",&optionOverwrite);
            if(ImGui::Button("Save as json"))
            {
                core::SaveLoadHandler::saveSceneAsJson(saveNameToSave,optionOverwrite,&core::MainHandler::msObjectModels,
                                                        &core::MainHandler::msShaders,
                                                        &core::MainHandler::msEntities,
                                                        &core::MainHandler::msLights
                );
                optionOverwrite = false;
                strcpy(saveNameToSave,"");
            }

        }
        ImGui::EndGroup();

        ImGui::End();
    }
}



// Runtime related functions
void core::MainHandler::addCoreEntity()
{
    CoreEntity *newCoreEntity = new CoreEntity();
    core::MainHandler::msEntities.emplace_back(newCoreEntity);
}

void core::MainHandler::addCoreEntity(Model::Model *entityModel)
{
    CoreEntity *newCoreEntity = new CoreEntity();
    newCoreEntity->mpModel = entityModel;
    core::MainHandler::msEntities.push_back(std::unique_ptr<CoreEntity>(newCoreEntity));
    newCoreEntity = nullptr;
}



// System related functions
void core::MainHandler::processInput(GLFWwindow *window, GLfloat deltaTime)
{
    // wait time for pressing esc
    static GLfloat waitTime = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && waitTime <= 0)
    {
        MainHandlerVariables.simuFlag = !MainHandlerVariables.simuFlag;
        MainHandlerVariables.firstMouse = true;
        glfwSetCursorPos(window, MainHandlerVariables.SCR_WIDTH / 2, MainHandlerVariables.SCR_HEIGHT / 2);
        waitTime = 0.35f;
    }
    if (MainHandlerVariables.simuFlag)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            MainHandlerVariables.mainCamera.MovementSpeed = SPEED * 2;
        else
            MainHandlerVariables.mainCamera.MovementSpeed = SPEED;
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
            MainHandlerVariables.mainCamera.MovementSpeed = SPEED / 2;
        else
            MainHandlerVariables.mainCamera.MovementSpeed = SPEED;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            MainHandlerVariables.mainCamera.ProcessKeyboard(FORWARD, MainHandlerVariables.deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            MainHandlerVariables.mainCamera.ProcessKeyboard(BACKWARD, MainHandlerVariables.deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            MainHandlerVariables.mainCamera.ProcessKeyboard(LEFT, MainHandlerVariables.deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            MainHandlerVariables.mainCamera.ProcessKeyboard(RIGHT, MainHandlerVariables.deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            MainHandlerVariables.mainCamera.ProcessKeyboard(DOWNWARD, MainHandlerVariables.deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            MainHandlerVariables.mainCamera.ProcessKeyboard(UPWARD, MainHandlerVariables.deltaTime);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    // decreases wait time
    if (waitTime - deltaTime <= 0) // somehow
        waitTime = 0;
    else
        waitTime -= deltaTime;
}

void core::MainHandler::DrawInstanced()
{
    core::RenderFunctor::DrawInstanced(
        core::MainHandlerVariables.SCR_WIDTH,
        core::MainHandlerVariables.SCR_HEIGHT,
        &core::MainHandler::msShaders,
        &core::MainHandlerVariables.mainCamera,
        &core::MainHandler::msLights,
        &core::MainHandler::msEntities);
}

void core::MainHandler::DrawInstancedWithInterval(GLfloat deltaTime, GLfloat intervalMS)
{
    static GLfloat remainingTimeMicroSecond = intervalMS;
    if (remainingTimeMicroSecond >= 0)
    {
        remainingTimeMicroSecond -= deltaTime;
    }
    else
    {
        core::MainHandler::DrawInstanced();
        remainingTimeMicroSecond = intervalMS;
    }
}

void core::MainHandler::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void core::MainHandler::mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float ypos = static_cast<float>(yposIn);
    float xpos = static_cast<float>(xposIn);

    float xoffset = 0;
    float yoffset = 0;

    if (MainHandlerVariables.simuFlag)
    {
        if (MainHandlerVariables.firstMouse)
        {
            MainHandlerVariables.lastX = xpos;
            MainHandlerVariables.lastY = ypos;
            MainHandlerVariables.firstMouse = false;
        }
        else
        {
            xoffset = xpos - MainHandlerVariables.lastX;
            yoffset = MainHandlerVariables.lastY - ypos; // reversed since y-coordinates go from bottom to top

            MainHandlerVariables.lastX = xpos;
            MainHandlerVariables.lastY = ypos;
        }

        MainHandlerVariables.mainCamera.ProcessMouseMovement(xoffset, yoffset);
    }
}

void core::MainHandler::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    if (MainHandlerVariables.simuFlag)
        MainHandlerVariables.mainCamera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void core::MainHandler::calculateDeltaTime()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    MainHandlerVariables.deltaTime = currentFrame - MainHandlerVariables.lastFrame;
    MainHandlerVariables.counter++;

    if (MainHandlerVariables.deltaTime >= 1.0f / 30.0f)
    {
        MainHandlerVariables.lastFrame = currentFrame;
        MainHandlerVariables.counter = 0;
    }
}

GLfloat core::MainHandler::returnDeltaTime()
{
    return MainHandlerVariables.deltaTime;
}

GLuint core::MainHandler::returnSCR_WIDTH()
{
    return core::MainHandlerVariables.SCR_WIDTH;
}

GLuint core::MainHandler::returnSCR_HEIGHT()
{
    return core::MainHandlerVariables.SCR_HEIGHT;
}
