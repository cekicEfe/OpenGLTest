#include "GameModel.hpp"
#include "App/DemoGame/GameModel/GameModel.hpp"

testgame::GameModel::GameModel(const std::string &model,
                               const std::string &name,
                               GLboolean gammacorrection, bool flip_textures)
    : Model::Model(model, gammacorrection, flip_textures) {
  this->modelName = name;
}

testgame::GameModel::~GameModel() {}

const std::string &testgame::GameModel::getModelName() const {
  return this->modelName;
}
