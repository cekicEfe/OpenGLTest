#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H

#include <CoreClass/CoreClassPreDec.h>
#include <fstream>
#include <iostream>
#include <json/json.hpp>
#include <string>

namespace core {
class JsonExtractor {
public:
  static nlohmann::json *loadJsonFromPath(std::string path);
};
} // namespace core

#endif
