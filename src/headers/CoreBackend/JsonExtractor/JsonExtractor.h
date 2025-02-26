#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <json/json.hpp>
#include <memory>
#include <string>

namespace core
{
class JsonExtractor
{
public:
  JsonExtractor ();
  ~JsonExtractor ();
  std::shared_ptr<nlohmann::json>
  loadJsonFromPath (std::filesystem::path path);
};
} // namespace core

#endif
