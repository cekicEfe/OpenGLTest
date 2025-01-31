#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "GraphicsBackend/Model/Model.h"

namespace testgame {

class GameModel : public Model::Model {
private:
  std::string modelName;

public:
  GameModel(const std::string &path, const std::string &modelName,
            GLboolean gammcorrection = false);
  ~GameModel();
  const std::string &getModelName() const;
};

} // namespace testgame

#endif
