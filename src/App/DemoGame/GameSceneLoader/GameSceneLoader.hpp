#ifndef GAMESCENELOADER_HPP
#define GAMESCENELOADER_HPP

#include "json.hpp"
#include <App/DemoGame/GameScript/GameScript.hpp>
#include <cinttypes>
#include <string>

using Json = nlohmann::json;

namespace testgame {

class GameSceneLoader {
private:
public:
  static std::map<std::string, std::any> JsonToVars(const Json &jsonObj) {
    std::map<std::string, std::any> out;
    for (auto &j : jsonObj.items()) {
      if (j.value().type() == Json::value_t::object)
        out[j.key()] = JsonToVars(j.value());
      else if (j.value().type() == Json::value_t::string)
        out[j.key()] = j.value().get<std::string>();
      else if (j.value().type() == Json::value_t::boolean)
        out[j.key()] = j.value().get<bool>();
      else if (j.value().type() == Json::value_t::number_float)
        out[j.key()] = j.value().get<float>();
      else if (j.value().type() == Json::value_t::number_integer)
        out[j.key()] = j.value().get<int>();
    }
    return out;
  }
};

} // namespace testgame

#endif
