#ifndef SAVABLEOBJECT_HPP
#define SAVABLEOBJECT_HPP

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

namespace core
{
class SavableObject
{
public:
  SavableObject ();
  virtual ~SavableObject () = 0;
  virtual nlohmann::json SaveAsJson () = 0;
  virtual void LoadAsJson (nlohmann::json const &json) = 0;
};
}

#endif
