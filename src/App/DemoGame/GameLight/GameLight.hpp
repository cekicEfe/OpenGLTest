#ifndef GAMELIGHT_HPP
#define GAMELIGHT_HPP

#include "GraphicsBackend/Light/Light.hpp"

namespace testgame {
class GameLight : public Model::Light {
public:
  GameLight();
  ~GameLight();
};
} // namespace testgame

#endif
