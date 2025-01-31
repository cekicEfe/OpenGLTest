#include "GameShader.hpp"

testgame::GameShader::GameShader(const char *vertShader, const char *fragShader,
                                 std::string shaderName)
    : Shader(vertShader, fragShader) {
  this->shaderName = shaderName;
}

testgame::GameShader::~GameShader() {}

const std::string &testgame::GameShader::getShaderName() const {
  return this->shaderName;
}
