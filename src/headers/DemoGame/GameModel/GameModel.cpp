#include "GameModel.hpp"
#include "DemoGame/GameModel/GameModel.hpp"
#include "model/Model.h"

testgame::GameModel::GameModel (std::string model, std::string name,
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
