#ifndef GAMEENTITYCREATOR_HPP
#define GAMEENTITYCREATOR_HPP

#include "App/DemoGame/GameEntity/GameEntity.hpp"
#include <filesystem>
#include <memory>
#include <sol/state.hpp>
namespace testgame
{
class GameEntityCreator
{
  std::shared_ptr<testgame::GameEntity>
  createEntity (sol::state &game_state, const std::string &script_content)
  {
    std::shared_ptr<testgame::GameEntity> entity_ptr
        = std::make_shared<testgame::GameEntity> ();

    return entity_ptr;
  }

  std::shared_ptr<testgame::GameEntity>
  createEntity (sol::state &state, const std::filesystem::path &script_path)
  {
  }
};
}

#endif
