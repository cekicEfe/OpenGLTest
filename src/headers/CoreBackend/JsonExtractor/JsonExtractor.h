#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H

#include <fstream>
#include <iostream>
#include <json/json.hpp>
#include <memory>
#include <string>

namespace core {
class JsonExtractor {
public:
  JsonExtractor();
  ~JsonExtractor();
  std::shared_ptr<nlohmann::json> loadJsonFromPath(std::string path);
};
} // namespace core

#endif
