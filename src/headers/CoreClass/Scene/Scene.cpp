#include "Scene.hpp"

core::Scene::Scene ()
{
}

core::Scene::~Scene ()
{
}

const core::CoreEntity *const
core::Scene::returnEntites ()
{
  return this->entities.data ();
}

const size_t
core::Scene::returnEntitesSize ()
{
  return this->entities.size ();
}

const Model::Model *const
core::Scene::returnModels ()
{
  return this->models.data ();
}

const size_t
core::Scene::returnModelsSize ()
{
  return this->models.size ();
}

const Model::Light *const
core::Scene::returnLights ()
{
  return this->lights.data ();
}

const size_t
core::Scene::returnLightsSize ()
{
  return this->lights.size ();
}

const Shader *const
core::Scene::returnShaders ()
{
  return this->shaders.data ();
}

const size_t
core::Scene::returnShadersSize ()
{
  return this->shaders.size ();
}

const Camera *const
core::Scene::returnCameras ()
{
  return this->cameras.data ();
}

const size_t
core::Scene::returnCamerasSize ()
{
  return this->cameras.size ();
}
