#include "GameModel.hpp"
#include "App/DemoGame/GameModel/GameModel.hpp"
#include "GraphicsBackend/Animation/Animation.hpp"
#include "GraphicsBackend/Animator/Animator.hpp"
#include <memory>
#include <stdexcept>

testgame::GameModel::GameModel (const std::string &model_path,
                                const std::string &name,
                                GLboolean gamma_correction, bool flip_textures)
    : Model::Model (model_path, gamma_correction, flip_textures)
{
  this->modelName = name;
  this->currentAnimationIndex = 0;
  uint count = this->GetAnimCount ();

  // For some god forsaken reason
  if (count <= 0)
    {
      std::cout << "This model has no anims to load" << std::endl;
    }
  else
    {
      this->animations.resize (count);
      uint h = 0;
      for (auto &i : this->animations)
        {
          i.first
              = std::make_unique< ::Model::Animation> (model_path, this, h);
          i.second = std::make_unique< ::Model::Animator> (i.first.get ());
          h++;
        }
    }
}

testgame::GameModel::~GameModel ()
{
}

const std::string &
testgame::GameModel::getModelName () const
{
  return this->modelName;
}

void
testgame::GameModel::swapAnimation (size_t i)
{
  if (i > this->GetAnimCount () && this->GetAnimCount () > 0)
    {
      throw std::invalid_argument ("Selected anim index is out of bounds");
    }
  else
    {
      this->animations.at (currentAnimationIndex).second->ResetAnimation ();
      this->currentAnimationIndex = i;
    }
}

void
testgame::GameModel::useAnimation (float deltaTime)
{
  this->animations.at (this->currentAnimationIndex)
      .second->UpdateAnimation (deltaTime);
}
