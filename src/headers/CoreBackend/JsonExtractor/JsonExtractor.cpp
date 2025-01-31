#include "JsonExtractor.h"

core::JsonExtractor::JsonExtractor() {}

core::JsonExtractor::~JsonExtractor() {}

std::shared_ptr<nlohmann::json>
core::JsonExtractor::loadJsonFromPath(std::string path) {
  std::ifstream file(path.c_str());

  // Check if the file was opened successfully
  if (!file.is_open()) {
    std::cerr << "Failed to open file at JsonExtractor::loadJsonFromPath: "
              << path << std::endl;
    return nullptr;
  }

  // Parse the JSON file into a json object
  std::shared_ptr<nlohmann::json> jsonObject(new nlohmann::json);
  try {
    file >> *jsonObject;
  } catch (nlohmann::json::parse_error &e) {
    std::cerr << "Parse error at JsonExtractor::loadJsonFromPath: " << e.what()
              << std::endl;
    jsonObject.reset();
    file.close();
    return nullptr;
  }

  file.close();
  return jsonObject;
}
