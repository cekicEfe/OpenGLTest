#include "GameModel.hpp"
#include "App/DemoGame/GameModel/GameModel.hpp"

testgame::GameModel::GameModel (const std::string &model,
                                const std::string &name,
                                GLboolean gammacorrection)
    : Model::Model (model, gammacorrection)
{
  this->modelName = name;
}

testgame::GameModel::~GameModel ()
{
}

const std::string &
testgame::GameModel::getModelName () const
{
  return this->modelName;
}
