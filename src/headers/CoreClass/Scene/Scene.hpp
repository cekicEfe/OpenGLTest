#ifndef SCENE_HPP
#define SCENE_HPP

#include "CoreClass/CoreEntity/CoreEntity.h"
#include "model/Camera.h"
#include "model/Model.h"
#include "model/Shaders.h"
#include <vector>
namespace core
{
class Scene
{
private:
  std::vector<core::CoreEntity> entities;
  std::vector<Model::Model> models;
  std::vector<Model::Light> lights;
  std::vector<Shader> shaders;

  // 0th index is the main camera !!!
  std::vector<Camera> cameras;

public:
  Scene ();
  virtual ~Scene ();

  virtual const CoreEntity *const returnEntites ();
  virtual const size_t returnEntitesSize ();

  virtual const Model::Model *const returnModels ();
  virtual const size_t returnModelsSize ();

  virtual const Model::Light *const returnLights ();
  virtual const size_t returnLightsSize ();

  virtual const Shader *const returnShaders ();
  virtual const size_t returnShadersSize ();

  virtual const Camera *const returnCameras ();
  virtual const size_t returnCamerasSize ();
};
}

#endif
