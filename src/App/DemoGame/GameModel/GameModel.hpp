#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "GraphicsBackend/Animation/Animation.hpp"
#include "GraphicsBackend/Animator/Animator.hpp"
#include "GraphicsBackend/Model/Model.h"

namespace testgame
{

class GameModel : public Model::Model
{
private:
  std::string modelName;
  uint currentAnimationIndex;
  size_t animCount;

  // 20240412 Dont name namespaces same with class names dickwit
  // 20250506 What ? what the fuck are you on about ?
  std::vector<std::pair<std::unique_ptr< ::Model::Animation>,
                        std::unique_ptr< ::Model::Animator> > >
      animations;

public:
  GameModel (const std::string &path, const std::string &modelName,
             GLboolean gammcorrection = false, bool flip_textures = true);
  ~GameModel ();
  const std::string &getModelName () const;

  void swapAnimation (size_t anim_index);
  void useAnimation (float deltaTime);
};

} // namespace testgame

#endif
