#include "CoreClass/RenderHandler/RenderHandler.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_transform.hpp"
#include <glm/glm.hpp>

core::RenderHandler *core::RenderHandler::instance = nullptr;

core::RenderHandler::RenderHandler ()
{
  std::cout << "Called RenderHandler Constructor" << std::endl;
}

core::RenderHandler::~RenderHandler ()
{
  std::cout << "Called RenderHandler DEconstructor" << std::endl;
  this->instance = nullptr;
}

core::RenderHandler const *const
core::RenderHandler::createInstance ()
{
  if (core::RenderHandler::instance == nullptr)
    {
      std::cout << "Creating a renderHandler Instance" << std::endl;
      core::RenderHandler::instance = new core::RenderHandler ();
      return instance;
    }
  else
    {
      std::cout << "A renderHandler already exists" << std::endl;
      return nullptr;
    }
}

void
core::RenderHandler::deleteInstance () const
{
  if (core::RenderHandler::instance == nullptr)
    {
      std::cout << "No renderHandler exists to delete" << std::endl;
    }
  else
    {
      std::cout << "Deleting render handler" << std::endl;
      delete core::RenderHandler::instance;
      core::RenderHandler::instance = nullptr;
    }
}

void
core::RenderHandler::DrawInstanced (
    const GLuint &SCR_WIDTH, const GLuint &SCR_HEIGHT, const Camera &camera,
    const std::vector<Model::Light> *const lights,
    const std::vector<std::unique_ptr<core::CoreEntity> > *const entities)
    const
{
  if (lights != NULL && entities != NULL && (lights->size () > 0)
      && (entities->size () > 0))
    {

      for (size_t i = 0; i < entities->size (); i++)
        {

          static const Model::Model *model
              = entities->at (i).get ()->getModel ();
          static const Shader *shader = entities->at (i).get ()->getShader ();
          static bool initBatch = true;
          static std::vector<glm::mat4> modelMatrices;

          if (initBatch)
            {
              glm::mat4 projection = glm::perspective (
                  glm::radians (45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT,
                  CLOSE_SIGHT, FAR_SIGHT);

              glm::mat4 view = camera.GetViewMatrix ();

              shader->setInt ("texture_diffuse1", 0);
              shader->setFloat ("time", glfwGetTime ());
              shader->setInt ("light_count", lights->size ());
              shader->setMat4 ("projection", projection);
              shader->setMat4 ("view", view);

              for (GLuint i = 0; i < lights->size (); i++)
                {
                  shader->setVec3 ("light_positions[" + std::to_string (i)
                                       + "]",
                                   lights->at (i).light_pos);
                  shader->setVec3 ("light_colors[" + std::to_string (i) + "]",
                                   lights->at (i).light_color);
                }

              model = entities->at (i).get ()->getModel ();
              shader = entities->at (i).get ()->getShader ();
              modelMatrices.clear ();

              initBatch = false;
            }

          if (model != entities->at (i + 1).get ()->getModel ()
              || shader != entities->at (i + 1).get ()->getShader ()
              || i + 1 == entities->size ())
            {

              glm::mat4 modelMatrix = glm::mat4 (1.0);
              modelMatrix = glm::translate (
                  modelMatrix, *entities->at (i).get ()->getPos ());
              modelMatrix = glm::scale (
                  modelMatrix, *entities->at (i).get ()->getModelScale ());
              auto &rot = *entities->at (i).get ()->getRot ();
              modelMatrix
                  = glm::rotate (modelMatrix, rot.w, { rot.x, rot.y, rot.z });
              modelMatrices.push_back (modelMatrix);

              GLuint buffer;
              glGenBuffers (1, &buffer);
              glBindBuffer (GL_ARRAY_BUFFER, buffer);
              glBufferData (GL_ARRAY_BUFFER,
                            modelMatrices.size () * sizeof (glm::mat4),
                            &modelMatrices[0], GL_STATIC_DRAW);

              for (GLuint j = 0;
                   j < entities->at (i).get ()->getModel ()->Meshes.size ();
                   j++)
                {
                  GLuint VAO
                      = entities->at (i).get ()->getModel ()->Meshes[j].vao.id;
                  glBindVertexArray (VAO);

                  glEnableVertexAttribArray (4);
                  glVertexAttribPointer (4, 4, GL_FLOAT, GL_FALSE,
                                         sizeof (glm::mat4), (void *)0);
                  glEnableVertexAttribArray (5);
                  glVertexAttribPointer (5, 4, GL_FLOAT, GL_FALSE,
                                         sizeof (glm::mat4),
                                         (void *)(1 * sizeof (glm::vec4)));
                  glEnableVertexAttribArray (6);
                  glVertexAttribPointer (6, 4, GL_FLOAT, GL_FALSE,
                                         sizeof (glm::mat4),
                                         (void *)(2 * sizeof (glm::vec4)));
                  glEnableVertexAttribArray (7);
                  glVertexAttribPointer (7, 4, GL_FLOAT, GL_FALSE,
                                         sizeof (glm::mat4),
                                         (void *)(3 * sizeof (glm::vec4)));

                  glVertexAttribDivisor (4, 1);
                  glVertexAttribDivisor (5, 1);
                  glVertexAttribDivisor (6, 1);
                  glVertexAttribDivisor (7, 1);

                  glBindVertexArray (0);
                }

              // Draws objects here
              shader->use ();
              for (GLuint g = 0;
                   g < entities->at (i).get ()->getModel ()->Meshes.size ();
                   g++)
                {
                  if (entities->at (i).get ()->getModel ()->HasTexture ())
                    {
                      glActiveTexture (GL_TEXTURE0);
                      glBindTexture (GL_TEXTURE_2D, entities->at (i)
                                                        .get ()
                                                        ->getModel ()
                                                        ->Textures.at (0)
                                                        .ID);
                    }
                  glBindVertexArray (entities->at (i)
                                         .get ()
                                         ->getModel ()
                                         ->Meshes.at (g)
                                         .vao.id);
                  glDrawElementsInstanced (
                      GL_TRIANGLES,
                      static_cast<GLuint> (entities->at (i)
                                               .get ()
                                               ->getModel ()
                                               ->Meshes.at (g)
                                               .indices.size ()),
                      GL_UNSIGNED_INT, 0, modelMatrices.size ());
                  glBindVertexArray (0);
                }
              shader->stop ();

              glDeleteBuffers (1, &buffer);
              initBatch = true;
            }
          else
            {
              glm::mat4 modelMatrix = glm::mat4 (1.0);
              modelMatrix = glm::translate (
                  modelMatrix, *entities->at (i).get ()->getPos ());
              modelMatrix = glm::scale (
                  modelMatrix, *entities->at (i).get ()->getModelScale ());
              auto &rot = *entities->at (i).get ()->getRot ();
              modelMatrix
                  = glm::rotate (modelMatrix, rot.w, { rot.x, rot.y, rot.z });
              modelMatrices.push_back (modelMatrix);
            }
        }
    }
}
