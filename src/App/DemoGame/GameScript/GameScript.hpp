#ifndef GAMESCRIPT_HPP
#define GAMESCRIPT_HPP

#include "App/DemoGame/GameEntity/GameEntity.hpp"
#include <any>
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
extern "C"
{
#include <lua.h>
#include <lualib.h>
}

#ifndef EXAMPLES_ASSERT_HPP
#define EXAMPLES_ASSERT_HPP
#define m_assert(condition, message)                                          \
  do                                                                          \
    {                                                                         \
      if (!(condition))                                                       \
        {                                                                     \
          std::cerr << "Assertion `" #condition "` failed in " << __FILE__    \
                    << " line " << __LINE__ << ": " << message << std::endl;  \
          std::terminate ();                                                  \
        }                                                                     \
    }                                                                         \
  while (false)

#define c_assert(condition)                                                   \
  do                                                                          \
    {                                                                         \
      if (!(condition))                                                       \
        {                                                                     \
          std::cerr << "Assertion `" #condition "` failed in " << __FILE__    \
                    << " line " << __LINE__ << std::endl;                     \
          std::terminate ();                                                  \
        }                                                                     \
    }                                                                         \
  while (false)
#else
#define m_assert(condition, message)                                          \
  do                                                                          \
    {                                                                         \
      if (false)                                                              \
        {                                                                     \
          (void)(condition);                                                  \
          (void)sizeof (message);                                             \
        }                                                                     \
    }                                                                         \
  while (false)
#define c_assert(condition)                                                   \
  do                                                                          \
    {                                                                         \
      if (false)                                                              \
        {                                                                     \
          (void)(condition);                                                  \
        }                                                                     \
    }                                                                         \
  while (false)
#endif

namespace testgame
{

// Most reasonable thing that is the act questioning, no doubt on that.
// Dont do it here
// *Especially* here

// q: Why did you do it like this ?
// a: Dunno

// q: Why does *this* return a shared pointer to an object that cannot be
// accessed without a stratagy pattern
// a: Hopefully scripts will

// q: Why shared ptr ?
// a: To not let lua class def get "destroyed" it will be held somewhere

inline std::shared_ptr<std::any>
ShowGameEntityToLuaState (sol::state &inpt_state)
{
  std::shared_ptr<sol::usertype<GameEntity> > gameEntityToReturn;
  static bool not_defined = true;
  if (not_defined)
    {
      not_defined = false;
      gameEntityToReturn = std::make_shared<sol::usertype<GameEntity> > (
          inpt_state.new_usertype<GameEntity> (
              "GameEntity", sol::constructors<GameEntity ()> ()));

      (*gameEntityToReturn.get ())["getPos"] = &testgame::GameEntity::getPos;
      (*gameEntityToReturn.get ())["setPos"] = &testgame::GameEntity::setPos;

      return std::make_shared<std::any> (gameEntityToReturn.get ());
    }
  else
    throw std::runtime_error ("Used twice !! dont do it");
}

inline void
ShowVec3ToLuaState (sol::state &state_lua)
{
  // std::shared_ptr<sol::usertype<glm::vec3> > Vec3ToReturn;
  static bool not_defined = true;
  if (not_defined)
    {
      not_defined = false;
      auto Vec3ToReturn = std::make_shared<sol::usertype<glm::vec3> > (
          state_lua.new_usertype<glm::vec3> (
              "vec3",
              sol::constructors<glm::vec3 (),
                                glm::vec3 (float, float, float)> ()));

      (*Vec3ToReturn.get ())["x"] = &glm::vec3::x;
      (*Vec3ToReturn.get ())["y"] = &glm::vec3::y;
      (*Vec3ToReturn.get ())["z"] = &glm::vec3::z;

      // God have mercy on me, for no man will.
      // return std::make_shared<std::any> (Vec3ToReturn.get ());
    }
  else
    throw std::runtime_error (std::string ("Used twice !! dont do it"));
}

}

#endif
