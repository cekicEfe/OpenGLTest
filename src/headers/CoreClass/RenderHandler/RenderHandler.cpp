#include "RenderHandler.h"
#include <glm/glm.hpp>

core::RenderHandler::RenderHandler ()
{
  std::cout << "Called RenderHandler Constructor" << std::endl;
}

core::RenderHandler::~RenderHandler ()
{
  std::cout << "Called RenderHandler DEconstructor" << std::endl;
}

void
core::RenderHandler::DrawInstanced (
    const GLuint &SCR_WIDTH, const GLuint &SCR_HEIGHT, const Camera *camera,
    const std::vector<Model::Light> *const lights,
    const core::CoreEntity *const entities, const size_t entities_size) const
{
  if (lights != NULL && entities != NULL && (lights->size () > 0)
      && (entities_size > 0))
    {
      for (size_t i = 0; i < entities_size; i++)
        {
          static const Model::Model *batchLeaderModel
              = entities[i].getModel ();
          static const Shader *batchLeaderShader = entities[i].getShader ();
          static std::vector<glm::mat4> modelMatrices;

          static auto draw = [&] () {
            glm::mat4 projection = glm::perspective (
                glm::radians (45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT,
                CLOSE_SIGHT, FAR_SIGHT);

            glm::mat4 view = camera->GetViewMatrix ();

            batchLeaderShader->setInt ("texture_diffuse1", 0);
            batchLeaderShader->setFloat ("time", glfwGetTime ());
            batchLeaderShader->setInt ("light_count", lights->size ());
            batchLeaderShader->setMat4 ("projection", projection);
            batchLeaderShader->setMat4 ("view", view);

            for (GLuint j = 0; j < lights->size (); j++)
              {
                batchLeaderShader->setVec3 ("light_positions["
                                                + std::to_string (i) + "]",
                                            lights->at (i).light_pos);
                batchLeaderShader->setVec3 ("light_colors["
                                                + std::to_string (i) + "]",
                                            lights->at (i).light_color);
              }

            GLuint buffer;
            glGenBuffers (1, &buffer);
            glBindBuffer (GL_ARRAY_BUFFER, buffer);
            glBufferData (GL_ARRAY_BUFFER,
                          modelMatrices.size () * sizeof (glm::mat4),
                          &modelMatrices[0], GL_STATIC_DRAW);

            for (GLuint j = 0; j < batchLeaderModel->Meshes.size (); j++)
              {
                GLuint VAO = batchLeaderModel->Meshes[j].vao.id;
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
            batchLeaderShader->use ();
            for (GLuint g = 0; g < batchLeaderModel->Meshes.size (); g++)
              {
                if (batchLeaderModel->HasTexture ())
                  {
                    glActiveTexture (GL_TEXTURE0);
                    glBindTexture (GL_TEXTURE_2D,
                                   batchLeaderModel->Textures.at (0).ID);
                  }
                glBindVertexArray (batchLeaderModel->Meshes.at (g).vao.id);
                glDrawElementsInstanced (
                    GL_TRIANGLES,
                    static_cast<GLuint> (
                        batchLeaderModel->Meshes.at (g).indices.size ()),
                    GL_UNSIGNED_INT, 0, modelMatrices.size ());
                glBindVertexArray (0);
              }
            glDeleteBuffers (1, &buffer);
          };

          // changed here !!!
          if (i != entities_size - 1)
            {
              if (batchLeaderModel == entities[i].getModel ()
                  && batchLeaderShader == entities[i].getShader ())
                {
                  glm::mat4 modelMatrix = glm::mat4 (1.0);
                  modelMatrix
                      = glm::translate (modelMatrix, entities[i].getPos ());
                  modelMatrix
                      = glm::scale (modelMatrix, entities[i].getModelScale ());
                  auto &rot = entities[i].getRot ();
                  // modelMatrix
                  //     = glm::rotate (modelMatrix, rot.w, { rot.x, rot.y,
                  //     rot.z
                  //     });
                  modelMatrices.push_back (modelMatrix);
                }
              else
                {
                  draw ();
                  modelMatrices.clear ();

                  batchLeaderModel = entities[i].getModel ();
                  batchLeaderShader = entities[i].getShader ();

                  glm::mat4 modelMatrix = glm::mat4 (1.0);
                  modelMatrix
                      = glm::translate (modelMatrix, entities[i].getPos ());
                  modelMatrix
                      = glm::scale (modelMatrix, entities[i].getModelScale ());
                  auto &rot = entities[i].getRot ();
                  // modelMatrix
                  //     = glm::rotate (modelMatrix, rot.w, { rot.x, rot.y,
                  //     rot.z
                  //     });
                  modelMatrices.push_back (modelMatrix);
                }
            }
          else
            {
              if (batchLeaderModel == entities[i].getModel ()
                  && batchLeaderShader == entities[i].getShader ())
                {
                  glm::mat4 modelMatrix = glm::mat4 (1.0);
                  modelMatrix
                      = glm::translate (modelMatrix, entities[i].getPos ());
                  modelMatrix
                      = glm::scale (modelMatrix, entities[i].getModelScale ());
                  auto &rot = entities[i].getRot ();
                  // modelMatrix
                  //     = glm::rotate (modelMatrix, rot.w, { rot.x, rot.y,
                  //     rot.z
                  //     });
                  modelMatrices.push_back (modelMatrix);

                  draw ();
                  modelMatrices.clear ();
                }
              else
                {
                  draw ();
                  modelMatrices.clear ();

                  glm::mat4 modelMatrix = glm::mat4 (1.0);
                  modelMatrix
                      = glm::translate (modelMatrix, entities[i].getPos ());
                  modelMatrix
                      = glm::scale (modelMatrix, entities[i].getModelScale ());
                  auto &rot = entities[i].getRot ();
                  // modelMatrix
                  //     = glm::rotate (modelMatrix, rot.w, { rot.x, rot.y,
                  //     rot.z
                  //     });
                  modelMatrices.push_back (modelMatrix);

                  draw ();
                  modelMatrices.clear ();
                }
            }
        }

      /*
        for (size_t i = 0; i < entities[i].size (); i++)
          {
            static const Model::Model *batchLeadermodel
                = entities[i].at (i).get ()->getModel ();
            static const Shader *batchLeadershader
                = entities[i].at (i).get ()->getShader ();
            static bool initBatch = true;
            static std::vector<glm::mat4> modelMatrices;

            if (initBatch)
              {

                batchLeadermodel = entities[i].at (i).get ()->getModel ();
                batchLeadershader = entities[i].at (i).get ()->getShader ();
                modelMatrices.clear ();

                glm::mat4 projection = glm::perspective (
                    glm::radians (45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT,
                    CLOSE_SIGHT, FAR_SIGHT);

                glm::mat4 view = camera.GetViewMatrix ();

                batchLeadershader->setInt ("texture_diffuse1", 0);
                batchLeadershader->setFloat ("time", glfwGetTime ());
                batchLeadershader->setInt ("light_count", lights->size ());
                batchLeadershader->setMat4 ("projection", projection);
                batchLeadershader->setMat4 ("view", view);

                for (GLuint i = 0; i < lights->size (); i++)
                  {
                    batchLeadershader->setVec3 ("light_positions["
                                                    + std::to_string (i) + "]",
                                                lights->at (i).light_pos);
                    batchLeadershader->setVec3 ("light_colors["
                                                    + std::to_string (i) + "]",
                                                lights->at (i).light_color);
                  }
                initBatch = false;
              }

            else if (((batchLeadermodel != entities[i].at (i).get ()->getModel
        ())
                      || (batchLeadershader
                          != entities[i].at (i).get ()->getShader ())
                      || (i + 1 == entities[i].size ()))
                     && !initBatch)
              {
                glm::mat4 modelMatrix = glm::mat4 (1.0);
                modelMatrix = glm::translate (
                    modelMatrix, entities[i].at (i).get ()->getPos ());
                modelMatrix = glm::scale (
                    modelMatrix, entities[i].at (i).get ()->getModelScale ());
                auto &rot = entities[i].at (i).get ()->getRot ();
                // modelMatrix
                //     = glm::rotate (modelMatrix, rot.w, { rot.x, rot.y, rot.z
                //     });
                modelMatrices.push_back (modelMatrix);

                GLuint buffer;
                glGenBuffers (1, &buffer);
                glBindBuffer (GL_ARRAY_BUFFER, buffer);
                glBufferData (GL_ARRAY_BUFFER,
                              modelMatrices.size () * sizeof (glm::mat4),
                              modelMatrices.data (), GL_STATIC_DRAW);

                for (GLuint j = 0;
                     j < entities[i].at (i).get ()->getModel ()->Meshes.size
        (); j++)
                  {
                    GLuint VAO
                        = entities[i].at (i).get ()->getModel
        ()->Meshes[j].vao.id; glBindVertexArray (VAO);

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
                batchLeadershader->use ();
                for (GLuint g = 0;
                     g < entities[i].at (i).get ()->getModel ()->Meshes.size
        (); g++)
                  {
                    if (entities[i].at (i).get ()->getModel ()->HasTexture ())
                      {
                        glActiveTexture (GL_TEXTURE0);
                        glBindTexture (GL_TEXTURE_2D, entities[i].at (i)
                                                          .get ()
                                                          ->getModel ()
                                                          ->Textures.at (0)
                                                          .ID);
                      }
                    glBindVertexArray (entities[i].at (i)
                                           .get ()
                                           ->getModel ()
                                           ->Meshes.at (g)
                                           .vao.id);
                    glDrawElementsInstanced (
                        GL_TRIANGLES,
                        static_cast<GLuint> (entities[i].at (i)
                                                 .get ()
                                                 ->getModel ()
                                                 ->Meshes.at (g)
                                                 .indices.size ()),
                        GL_UNSIGNED_INT, 0, modelMatrices.size ());
                    glBindVertexArray (0);
                  }
                glDeleteBuffers (1, &buffer);
                initBatch = true;
              }
            else
              {
                glm::mat4 modelMatrix = glm::mat4 (1.0);
                modelMatrix = glm::translate (
                    modelMatrix, entities[i].at (i).get ()->getPos ());
                modelMatrix = glm::scale (
                    modelMatrix, entities[i].at (i).get ()->getModelScale ());
                auto &rot = entities[i].at (i).get ()->getRot ();
                // modelMatrix
                //     = glm::rotate (modelMatrix, rot.w, { rot.x, rot.y, rot.z
                //     });
                modelMatrices.push_back (modelMatrix);
              }
          }
      */
    }
}
