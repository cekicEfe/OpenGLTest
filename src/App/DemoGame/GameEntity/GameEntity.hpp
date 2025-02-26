#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include "App/DemoGame/GameHitBox/GameHitBox.hpp"
#include "CoreBackend/CoreEntity/CoreEntity.h"
#include "GraphicsBackend/Model/Model.h"
#include "glm/fwd.hpp"
#include <any>
#include <map>
#include <memory>
#include <sol/forward.hpp>
#include <string>

using Json = nlohmann::json;

namespace testgame
{
class GameEntity : public core::CoreEntity
{
private:
  std::weak_ptr<testgame::GameHitBox> mpHitbox;
  glm::vec3 mHitboxScale = { 1.0f, 1.0f, 1.0f };
  // script name / script itself
  std::map<std::string, std::weak_ptr<std::string> > scripts;

public:
  GameEntity ();
  virtual ~GameEntity ();

  void useScript (const std::string &scriptName, sol::state &luaState);

  const testgame::GameHitBox *const getHitBox () const;
  void setHitbox (const std::shared_ptr<testgame::GameHitBox> &hitbox);

  const glm::vec3 &getHitBoxScale () const;
  void setHitboxScale (const glm::vec3 &HBscale);

  virtual void update (GLfloat deltaTime);
};
} // namespace testgame

#endif
