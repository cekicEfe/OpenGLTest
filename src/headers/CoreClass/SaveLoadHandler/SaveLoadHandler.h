#ifndef SAVELOADHANDLER_H
#define SAVELOADHANDLER_H

#include <CoreClass/CoreEntity/CoreEntity.h>
#include <CoreClass/JsonExtractor/JsonExtractor.h>

#include <filesystem>
#include <iostream>
#include <json/json.hpp>
#include <memory>
#include <model/Model.h>
#include <string>
#include <vector>

namespace core {
class SaveLoadHandler {
public:
  /*
    static void loadAllJsonScenePaths(std::vector<std::string> *JsonScenePaths);

    static void
    loadAllJsonPreceptPath(std::vector<std::string> *JsonPreceptPaths);

    static void loadAllShaderPaths(std::vector<std::string> *ShaderPaths);

    static void loadAllJsonPrecepts(
        std::vector<std::unique_ptr<nlohmann::json>> *JsonPrecepts);

    static void
    loadAllModels(std::vector<std::unique_ptr<Model::Model>> *ObjectModels);

    static void
    saveSceneAsJson(std::string fileName, GLboolean overwriteOption,
                    std::vector<std::unique_ptr<Model::Model>> *ObjectModels,
                    std::vector<std::unique_ptr<Shader>> *Shaders,
                    std::vector<std::unique_ptr<core::CoreEntity>> *Entities,
                    std::vector<std::unique_ptr<Model::Light>> *Lights);

    static void
    loadSceneFromJson(std::string filename,
                      std::vector<std::unique_ptr<Model::Model>> *ObjectModels,
                      std::vector<std::unique_ptr<Shader>> *Shaders,
                      std::vector<std::unique_ptr<core::CoreEntity>> *Entities,
                      std::vector<std::unique_ptr<Model::Light>> *Lights);
                      */
};
} // namespace core

#endif
