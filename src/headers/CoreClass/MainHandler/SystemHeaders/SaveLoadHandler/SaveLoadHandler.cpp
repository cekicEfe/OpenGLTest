#include "SaveLoadHandler.h"


void core::SaveLoadHandler::loadAllJsonPreceptPath(std::vector<std::string> *JsonPreceptPaths)
{
    if (JsonPreceptPaths->size() == 0)
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cJsonPreceptPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == core::cJsonExtension)
                {
                    std::cout << entry.path() << std::endl;
                    JsonPreceptPaths->push_back(std::string(entry.path().c_str()));
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at json precept: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at json precept: " << e.what() << std::endl;
        }
    }
    else
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cJsonPreceptPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == core::cJsonExtension)
                {
                    for (GLuint i = 0; i < JsonPreceptPaths->size(); i++)
                    {
                        if (JsonPreceptPaths->at(i) == std::string(entry.path()))
                        {
                            std::cout << "SAME " << std::endl;
                            break;
                        }
                        else if (i == JsonPreceptPaths->size() - 1 &&
                                 JsonPreceptPaths->at(i) != std::string(entry.path()))
                        {

                            JsonPreceptPaths->push_back(std::string(entry.path()));
                        }
                    }
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at json precept: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at json precept: " << e.what() << std::endl;
        }
    }
}

void core::SaveLoadHandler::loadAllJsonScenePaths(std::vector<std::string> *JsonScenePaths)
{
    if (JsonScenePaths->size() == 0)
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cJsonScenesPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == core::cJsonExtension)
                {
                    std::cout << entry.path() << std::endl;
                    JsonScenePaths->push_back(std::string(entry.path().c_str()));
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at json scene: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at json scene: " << e.what() << std::endl;
        }
    }
    else
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cJsonScenesPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == core::cJsonExtension)
                {
                    for (GLuint i = 0; i < JsonScenePaths->size(); i++)
                    {
                        if (JsonScenePaths->at(i) == std::string(entry.path()))
                        {
                            std::cout << "SAME " << std::endl;
                            break;
                        }
                        else if (i == JsonScenePaths->size() - 1 &&
                                 JsonScenePaths->at(i) != std::string(entry.path()))
                        {

                            JsonScenePaths->push_back(std::string(entry.path()));
                        }
                    }
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at json scene: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at json scene: " << e.what() << std::endl;
        }
    }
}

void core::SaveLoadHandler::loadAllJsonPrecepts(std::vector<std::unique_ptr<nlohmann::json>> *JsonPrecepts)
{
    // the first load
    if (JsonPrecepts->size() == 0)
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cJsonPreceptPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == core::cJsonExtension)
                {
                    std::cout << entry.path() << std::endl;
                    JsonPrecepts->emplace_back((core::JsonExtractor::loadJsonFromPath(std::string(entry.path()))));
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at loadJsonPrecept: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at loadJsonPrecept: " << e.what() << std::endl;
        }
    }
    // second load
    else
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cJsonPreceptPath))
            {
                if (entry.is_regular_file() && entry.path().extension() == core::cJsonExtension)
                {
                    for (GLuint i = 0; i < JsonPrecepts->size(); i++)
                    {
                        std::unique_ptr<nlohmann::json> jsonPtr(core::JsonExtractor::loadJsonFromPath(std::string(entry.path())));
                        if (*JsonPrecepts->at(i).get() == *jsonPtr.get())
                        {
                            std::cout << "SAME " << std::endl;
                            jsonPtr.reset();
                            break;
                        }
                        else if ((i == JsonPrecepts->size() - 1) &&
                                 (*JsonPrecepts->at(i).get() != *jsonPtr.get()))
                        {
                            JsonPrecepts->emplace_back((core::JsonExtractor::loadJsonFromPath(std::string(entry.path()))));
                            jsonPtr.reset();
                        }
                    }
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at core::SaveLoadHandler::loadAllJsonPrecepts: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at core::SaveLoadHandler::loadAllJsonPrecepts: " << e.what() << std::endl;
        }
    }
}

void core::SaveLoadHandler::loadAllShaderPaths(std::vector<std::string> *ShaderPaths)
{
    if (ShaderPaths->size() == 0)
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cShadersPath))
            {
                if ((entry.is_regular_file() && entry.path().extension() == core::cVertShaderExtension) || (entry.is_regular_file() && entry.path().extension() == core::cFragShaderExtension))
                {
                    std::cout << entry.path() << std::endl;
                    ShaderPaths->push_back(entry.path().c_str());
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at shaderlist: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at shaderlist: " << e.what() << std::endl;
        }
    }
    else
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cShadersPath))
            {
                if ((entry.is_regular_file() && entry.path().extension() == core::cVertShaderExtension) || (entry.is_regular_file() && entry.path().extension() == core::cFragShaderExtension))
                {
                    for (GLuint i = 0; i < ShaderPaths->size(); i++)
                    {
                        if (ShaderPaths->at(i) == std::string(entry.path()))
                        {
                            std::cout << "SAME " << std::endl;
                            break;
                        }
                        else if ((i == ShaderPaths->size() - 1) &&
                                 (ShaderPaths->at(i) != std::string(entry.path())))
                        {
                            ShaderPaths->push_back(std::string(entry.path()));
                        }
                    }
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at shaderList : " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at shaderList : " << e.what() << std::endl;
        }
    }
}

void core::SaveLoadHandler::loadAllModels(std::vector<std::unique_ptr<Model::Model>> *ObjectModels)
{
    // the first load
    if (ObjectModels->size() == 0)
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cModelsPath))
            {
                if ((entry.is_regular_file() && entry.path().extension() == core::cModelObjExtension) ||
                    (entry.is_regular_file() && entry.path().extension() == core::cModelFBXExtension))
                {
                    std::cout << entry.path() << std::endl;
                    ObjectModels->push_back(std::make_unique<Model::Model>(std::string(entry.path())));
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at loadModels: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at loadModels: " << e.what() << std::endl;
        }
    }
    // second load
    else
    {
        try
        {
            for (const auto &entry : std::filesystem::recursive_directory_iterator(core::cModelsPath))
            {
                if ((entry.is_regular_file() && entry.path().extension() == core::cModelObjExtension) ||
                    (entry.is_regular_file() && entry.path().extension() == core::cModelFBXExtension))
                {
                    for (GLuint i = 0; i < ObjectModels->size(); i++)
                    {
                        if (ObjectModels->at(i).get()->directory == std::string(entry.path().parent_path()))
                        {
                            std::cout << "SAME " << std::endl;
                            break;
                        }
                        else if ((i == ObjectModels->size() - 1) &&
                                 (ObjectModels->at(i).get()->directory != std::string(entry.path().parent_path())))
                        {
                            ObjectModels->push_back(std::make_unique<Model::Model>(std::string(entry.path())));
                        }
                    }
                }
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Filesystem error at loadModels: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "General error at loadModels: " << e.what() << std::endl;
        }
    }
}

void core::SaveLoadHandler::saveSceneAsJson(std::string inputFileName,
                                            GLboolean overwriteOption,
                                            std::vector<std::unique_ptr<Model::Model>> *ObjectModels,
                                            std::vector<std::unique_ptr<Shader>> *Shaders,
                                            std::vector<std::unique_ptr<core::CoreEntity>> *Entities,
                                            std::vector<std::unique_ptr<Model::Light>> *Lights)
{
    std::string fullPath = cJsonScenesPath + inputFileName + cJsonExtension;

    // Stops if filename exists takes overwriteOption as parameter
    if (std::filesystem::exists(fullPath) && overwriteOption == false)
    {
        std::cerr << "File already exists (core::SaveLoadHandler::saveSceneAsJson) !" << std::endl;
        throw std::invalid_argument("FILE::EXIST");
    }

    std::filesystem::path filePath = fullPath;

    // Deletes if filename exist uses overwriteoption as parameter
    if (std::filesystem::exists(fullPath) && overwriteOption == true)
    {
        try
        {
            if (std::filesystem::remove(filePath))
            {
                std::cout << "File deleted successfully.\n";
            }
            else
            {
                std::cout << "File does not exist.\n";
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }

    // Saves the file
    std::ofstream file(fullPath);
    if (file.is_open())
    {
        GLuint count = 0;
        nlohmann::json newJsonFile;

        // Saves models here
        for (GLuint i = 0; i < ObjectModels->size(); i++)
        {
            nlohmann::json modelJson;
            modelJson["Path"] = ObjectModels->at(i).get()->path;
            newJsonFile["Models"].push_back(modelJson);
            count = i + 1;
        }
        newJsonFile["Model Count"] = count;
        count = 0;

        // Saves Shaders Here
        for (GLuint i = 0; i < Shaders->size(); i++)
        {
            nlohmann::json shaderJson;
            shaderJson["FragPath"] = Shaders->at(i).get()->fragmentPath.c_str();
            shaderJson["VertPath"] = Shaders->at(i).get()->vertexPath.c_str();
            newJsonFile["Shaders"].push_back(shaderJson);
            count = i + 1;
        }
        newJsonFile["Shader Count"] = count;
        count = 0;

        // Saves Entities here
        for (GLuint i = 0; i < Entities->size(); i++)
            newJsonFile["Entities"].push_back(Entities->at(i).get()->saveAsJson()), count = i + 1;
        newJsonFile["Entity Count"] = count;
        count = 0;

        // Saves Lights here
        for (GLuint i = 0; i < Lights->size(); i++)
            newJsonFile["Lights"].push_back(Lights->at(i).get()->saveAsJson()), count = i + 1;
        newJsonFile["Light Count"] = count;
        count = 0;

        std::string jsonString = newJsonFile.dump(1);
        file << jsonString;
        file.close();
    }
    else
    {
        std::cerr << "Could not create file (core::SaveLoadHandler::saveSceneAsJson)" << std::endl;
        throw std::invalid_argument("SYSTEM::ERROR");
    }
}

void core::SaveLoadHandler::loadSceneFromJson(std::string filename,
                                    std::vector<std::unique_ptr<Model::Model>> *ObjectModels,
                                    std::vector<std::unique_ptr<Shader>> *Shaders,
                                    std::vector<std::unique_ptr<core::CoreEntity>> *Entities,
                                    std::vector<std::unique_ptr<Model::Light>> *Lights)
{
    nlohmann::json *newJsonPtr = core::JsonExtractor::loadJsonFromPath(core::cJsonScenesPath + filename + cJsonExtension);
    nlohmann::json newJson = *newJsonPtr;
    
    std::cout << core::cJsonScenesPath + filename + cJsonExtension << std::endl;
    std::cout << newJson.dump(4);

    delete newJsonPtr;
    newJsonPtr = nullptr;

    Shaders->clear();
    Lights->clear();
    ObjectModels->clear();
    Entities->clear();

    GLuint entityCount = newJson["Entity Count"].get<GLuint>();
    GLuint modelCount = newJson["Model Count"].get<GLuint>();
    GLuint lightCount = newJson["Light Count"].get<GLuint>();
    GLuint shaderCount = newJson["Shader Count"].get<GLuint>();

    std::cout << "Loading shaders" << std::endl;
    for (GLuint i = 0; i < shaderCount; i++)
    {
        std::string vertPath = newJson["Shaders"][i]["VertPath"].get<std::string>();
        std::string fragPath = newJson["Shaders"][i]["FragPath"].get<std::string>();
        Shader *newShader = new Shader(vertPath.c_str(), fragPath.c_str());
        Shaders->push_back(std::unique_ptr<Shader>(newShader));
        newShader = nullptr;
    }

    std::cout << "Loading lights" << std::endl;
    for (GLuint i = 0; i < lightCount; i++)
    {
        Model::Light *newLight = new Model::Light();

        newLight->light_color.x = newJson["Lights"][i]["Light Color"][0].get<GLfloat>();
        newLight->light_color.y = newJson["Lights"][i]["Light Color"][1].get<GLfloat>();
        newLight->light_color.z = newJson["Lights"][i]["Light Color"][2].get<GLfloat>();

        newLight->light_pos.x = newJson["Lights"][i]["Light Position"][0].get<GLfloat>();
        newLight->light_pos.y = newJson["Lights"][i]["Light Position"][1].get<GLfloat>();
        newLight->light_pos.z = newJson["Lights"][i]["Light Position"][2].get<GLfloat>();

        newLight->ambient = newJson["Lights"][i]["Ambient"].get<GLfloat>();
        newLight->diffuse = newJson["Lights"][i]["Diffuse"].get<GLfloat>();
        newLight->specular = newJson["Lights"][i]["Specular"].get<GLfloat>();

        Lights->push_back(std::unique_ptr<Model::Light>(newLight));
        newLight = nullptr;
    }

    std::cout << "Loading models" << std::endl;
    for (GLuint i = 0; i < modelCount; i++)
    {
        Model::Model *newModel = new Model::Model(newJson["Models"][i]["Path"].get<std::string>());
        ObjectModels->push_back(std::unique_ptr<Model::Model>(newModel));
        newModel = nullptr;
    }

    std::cout << "Loading entities" << std::endl;
    for (GLuint i = 0; i < entityCount; i++)
    {
        core::CoreEntity *newEntity = new CoreEntity();
        newEntity->mPos.x = newJson["Entities"][i]["Pos vector"][0].get<GLfloat>();
        newEntity->mPos.y = newJson["Entities"][i]["Pos vector"][1].get<GLfloat>();
        newEntity->mPos.z = newJson["Entities"][i]["Pos vector"][2].get<GLfloat>();

        newEntity->mRotAxis.x = newJson["Entities"][i]["Rot vector"][0].get<GLfloat>();
        newEntity->mRotAxis.y = newJson["Entities"][i]["Rot vector"][1].get<GLfloat>();
        newEntity->mRotAxis.z = newJson["Entities"][i]["Rot vector"][2].get<GLfloat>();

        newEntity->mRotDegreeRad = newJson["Entities"][i]["Rot degree"].get<GLfloat>();

        newEntity->mModelScale.x = newJson["Entities"][i]["Model Scale"][0].get<GLfloat>();
        newEntity->mModelScale.y = newJson["Entities"][i]["Model Scale"][1].get<GLfloat>();
        newEntity->mModelScale.z = newJson["Entities"][i]["Model Scale"][2].get<GLfloat>();

        for (GLuint j = 0; j < ObjectModels->size(); j++)
        {
            if (newJson["Entities"][i]["Model Path"].get<std::string>() == ObjectModels->at(j).get()->path)
            {
                newEntity->mpModel = ObjectModels->at(j).get();
                break;
            }
            else
            {
                continue;
            }
        }
        Entities->push_back(std::unique_ptr<core::CoreEntity>(newEntity));
        newEntity = nullptr;
    }
    std::cout << "Loaded save succelsadqfully !" << std::endl;
}
