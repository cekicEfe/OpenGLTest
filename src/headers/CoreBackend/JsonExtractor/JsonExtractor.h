#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
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
