#include "CoreEntity.h"

void core::CoreEntity::update(GLfloat deltaTime)
{
}

nlohmann::json core::CoreEntity::saveAsJson()
{
  nlohmann::json newJsonFile;

  newJsonFile["Pos vector"] = {this->mPos.x,
                               this->mPos.y,
                               this->mPos.z};

  newJsonFile["Rot vector"] = {this->mRotAxis.x,
                               this->mRotAxis.y,
                               this->mRotAxis.z};

  newJsonFile["Rot degree"] = this->mRotDegreeRad;

  if (this->mpModel != nullptr)
    newJsonFile["Model Path"] = this->mpModel->path.c_str();
  else
    newJsonFile["Model Path"] = nullptr;

  newJsonFile["Model Scale"] = {this->mModelScale.x,
                                this->mModelScale.y,
                                this->mModelScale.z};

  newJsonFile["Type"] = "CoreEntity";
  newJsonFile["Entity ID"] = std::to_string((int)this);//Dont touch this until it somehow break something (which is probable?)

  return newJsonFile;
}

core::CoreEntity::CoreEntity()
{
}

core::CoreEntity::~CoreEntity()
{
  this->mpModel = nullptr;
}
