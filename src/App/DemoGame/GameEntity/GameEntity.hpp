#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include "App/DemoGame/GameHitBox/GameHitBox.hpp"
#include "GraphicsBackend/Model/Model.h"
#include "glm/fwd.hpp"
#include <any>
#include <map>
#include <memory>
#include <string>

using Json = nlohmann::json;

namespace testgame
{
class GameEntity
{
private:
public:
  GameEntity ();
  virtual ~GameEntity ();
};
} // namespace testgame

#endif
