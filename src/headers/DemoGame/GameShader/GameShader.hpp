#ifndef GAMESHADER_HPP
#define GAMESHADER_HPP

#include "model/Shaders.h"

namespace testgame
{

class GameShader : public Shader
{
private:
  std::string shaderName;

public:
  GameShader (const char *vertShader, const char *fragShader,
              std::string shaderName);
  ~GameShader ();
  const std::string &getShaderName () const;
};

}

#endif