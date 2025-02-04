#include "CoreEntity.h"

core::CoreEntity::CoreEntity() {}

core::CoreEntity::CoreEntity(Model::Model &model, glm::vec3 modelScale,
                             Shader &shader, glm::vec3 rtcomp, GLfloat rotrad,
                             glm::vec3 mvcomp) {
  this->mpModel = &model;
  this->mModelScale = modelScale;
  this->mpShader = &shader;
  this->mPos = mvcomp;
  this->mRotAxis = rtcomp;
  this->mRotDegreeRad = rotrad;
}

core::CoreEntity::~CoreEntity() {}

const Shader *const core::CoreEntity::getShader() const {
  return this->mpShader;
}

const Model::Model *const core::CoreEntity::getModel() const {
  return this->mpModel;
}

const glm::vec3 &core::CoreEntity::getModelScale() const {
  return this->mModelScale;
}

const glm::vec3 &core::CoreEntity::getPos() const { return this->mPos; }

const glm::vec3 &core::CoreEntity::getRotAxis() const { return this->mRotAxis; }

const GLfloat &core::CoreEntity::getRotRad() const {
  return this->mRotDegreeRad;
}

void core::CoreEntity::setShader(Shader *const shader) {
  this->mpShader = shader;
}

void core::CoreEntity::setModel(Model::Model *const modelptr) {
  this->mpModel = modelptr;
}

void core::CoreEntity::setModelScale(const glm::vec3 &modelScale) {
  this->mModelScale = modelScale;
}

void core::CoreEntity::setPos(const glm::vec3 &mvcomp) { this->mPos = mvcomp; }

void core::CoreEntity::setRotAxis(const glm::vec3 &rtaxis) {
  this->mRotAxis = rtaxis;
}

void core::CoreEntity::setRotRad(const GLfloat &rotRad) {
  this->mRotDegreeRad = rotRad;
}

const glm::mat4 core::CoreEntity::getUniformAlignment() const {
  glm::mat4 modelMatrix = glm::mat4(1.0);
  modelMatrix = glm::translate(modelMatrix, this->mPos);
  modelMatrix = glm::scale(modelMatrix, this->mModelScale);
  modelMatrix = glm::rotate(modelMatrix, this->mRotDegreeRad, this->mRotAxis);
  return modelMatrix;
}
//
