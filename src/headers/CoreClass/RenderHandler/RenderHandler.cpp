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
    const Model::Light *const lights, const size_t lights_size,
    const core::CoreEntity *const entities, const size_t entities_size) const
{
  if (lights != NULL && entities != NULL && (lights_size > 0)
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
            batchLeaderShader->setInt ("light_count", lights_size);
            batchLeaderShader->setMat4 ("projection", projection);
            batchLeaderShader->setMat4 ("view", view);

            for (GLuint j = 0; j < lights_size; j++)
              {
                batchLeaderShader->setVec3 ("light_positions["
                                                + std::to_string (i) + "]",
                                            lights[i].light_pos);
                batchLeaderShader->setVec3 ("light_colors["
                                                + std::to_string (i) + "]",
                                            lights[i].light_color);
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

          if (i != entities_size - 1)
            {
              if (batchLeaderModel == entities[i].getModel ()
                  && batchLeaderShader == entities[i].getShader ())
                {
                  modelMatrices.push_back (entities[i].getUniformAlignment ());
                }
              else
                {
                  draw ();
                  modelMatrices.clear ();

                  batchLeaderModel = entities[i].getModel ();
                  batchLeaderShader = entities[i].getShader ();
                  modelMatrices.push_back (entities[i].getUniformAlignment ());
                }
            }
          else
            {
              if (batchLeaderModel == entities[i].getModel ()
                  && batchLeaderShader == entities[i].getShader ())
                {
                  modelMatrices.push_back (entities[i].getUniformAlignment ());

                  draw ();
                  modelMatrices.clear ();
                }
              else
                {
                  draw ();
                  modelMatrices.clear ();
                  modelMatrices.push_back (entities[i].getUniformAlignment ());

                  draw ();
                  modelMatrices.clear ();
                }
            }
        }
    }
}
