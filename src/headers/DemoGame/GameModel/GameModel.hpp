#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "model/Model.h"
namespace testgame
{

class GameModel : public Model::Model
{
private:
  std::string modelName;

public:
  GameModel (std::string path, std::string modelName,
             GLboolean gammcorrection = false);
  ~GameModel ();
  const std::string &getModelName () const;
};

}

#endif
