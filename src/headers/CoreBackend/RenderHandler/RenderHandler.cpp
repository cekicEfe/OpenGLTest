#include "RenderHandler.h"
#include "CoreBackend/CoreEntity/CoreEntity.h"
#include "CoreBackend/GlfwHandler/WindowHandler/Window/Window.h"
#include "GraphicsBackend/Buffers/VBO/VBO.h"
#include <cstddef>
#include <glm/glm.hpp>
#include <utility>

core::RenderHandler::RenderHandler ()
{
}

core::RenderHandler::~RenderHandler ()
{
}

void
core::RenderHandler::RenderTest (const core::Window &window,
                                 const Camera *camera,
                                 const Model::Light *const lights,
                                 const size_t lights_size,
                                 const core::CoreEntity *const entities,
                                 const size_t entities_size) const
{
  // //
  // const GLuint SCR_WIDTH = window.getScrWidth ();
  // const GLuint SCR_HEIGHT = window.getScrHeight ();

  // if (lights != NULL && entities != NULL && (lights_size > 0)
  //     && (entities_size > 0))
  //   {
  //     std::vector<std::pair<std::vector<glm::mat4>,
  //                           std::pair<const Model::Model *, const Shader *>
  //                           > >
  //         modelBatches;

  //     for (size_t i = 0; i < entities_size; i++)
  //       {
  //         if (modelBatches.empty ())
  //           {
  //             modelBatches.push_back (
  //                 { { entities[i].getUniformAlignment () },
  //                   { entities[i].getModel (), entities[i].getShader () }
  //                   });
  //             continue;
  //           }
  //         for (size_t j = 0; j < modelBatches.size (); j++)
  //           {
  //             if (entities[i].getModel () != nullptr
  //                 || entities[i].getShader () != nullptr)
  //               {
  //                 if ((entities[i].getModel () ==
  //                 modelBatches[j].second.first)
  //                     && (entities[i].getShader ()
  //                         == modelBatches[j].second.second))
  //                   {
  //                     modelBatches[j].first.push_back (
  //                         entities[i].getUniformAlignment ());
  //                     break;
  //                   }
  //                 else if (j == modelBatches.size () - 1)
  //                   {
  //                     modelBatches.push_back (
  //                         { { entities[i].getUniformAlignment () },
  //                           { entities[i].getModel (),
  //                             entities[i].getShader () } });
  //                   }
  //                 else
  //                   {
  //                     continue;
  //                   }
  //               }
  //           }
  //       }

  //     for (size_t i = 0; i < modelBatches.size (); i++)
  //       {
  //         auto &batch_model = modelBatches[i].second.first;
  //         auto &batch_shader = modelBatches[i].second.second;
  //         auto &matrices = modelBatches[i].first;

  //         static size_t d = 0;
  //         d++;
  //         std::cout << "Callcount : " << d << std::endl;

  //         VBO vbo;
  //         vbo.Bind ();
  //         vbo.BufferData (&matrices);

  //         for (GLuint j = 0; j < batch_model->Meshes.size (); j++)
  //           {
  //             auto &vao = batch_model->Meshes[j].vao;
  //             vao.Bind ();

  //             auto size = sizeof (glm::mat4);

  //             void *addr = (void *)0;
  //             vbo.PointData (4, 4, size, addr);

  //             addr = (void *)(1 * sizeof (glm::vec4));
  //             vbo.PointData (5, 4, size, addr);

  //             addr = (void *)(2 * sizeof (glm::vec4));
  //             vbo.PointData (6, 4, size, addr);

  //             addr = (void *)(3 * sizeof (glm::vec4));
  //             vbo.PointData (7, 4, size, addr);

  //             // GLuint VAO = batch_model->Meshes[j].vao.GetID ();
  //             // glBindVertexArray (VAO);

  //             // glEnableVertexAttribArray (4);
  //             // glVertexAttribPointer (4, 4, GL_FLOAT, GL_FALSE,
  //             //                        sizeof (glm::mat4), (void *)0);
  //             // glEnableVertexAttribArray (5);
  //             // glVertexAttribPointer (5, 4, GL_FLOAT, GL_FALSE,
  //             //                        sizeof (glm::mat4),
  //             //                        (void *)(1 * sizeof (glm::vec4)));
  //             // glEnableVertexAttribArray (6);
  //             // glVertexAttribPointer (6, 4, GL_FLOAT, GL_FALSE,
  //             //                        sizeof (glm::mat4),
  //             //                        (void *)(2 * sizeof (glm::vec4)));
  //             // glEnableVertexAttribArray (7);
  //             // glVertexAttribPointer (7, 4, GL_FLOAT, GL_FALSE,
  //             //                        sizeof (glm::mat4),
  //             //                        (void *)(3 * sizeof (glm::vec4)));

  //             glVertexAttribDivisor (4, 1);
  //             glVertexAttribDivisor (5, 1);
  //             glVertexAttribDivisor (6, 1);
  //             glVertexAttribDivisor (7, 1);
  //             vao.Unbind ();
  //             // glBindVertexArray (0);
  //           }

  //         glm::mat4 projection = glm::perspective (
  //             glm::radians (camera->getZoom ()),
  //             (float)SCR_WIDTH / (float)SCR_HEIGHT, camera->getCloseSight
  //             (), camera->getFarSight ());

  //         glm::mat4 view = camera->GetViewMatrix ();

  //         // Draws objects here
  //         batch_shader->use ();

  //         batch_shader->setInt ("texture_diffuse1", 0);
  //         // batch_shader->setFloat ("time", glfwGetTime ());
  //         // batch_shader->setInt ("light_count", lights_size);
  //         batch_shader->setMat4 ("projection", projection);
  //         batch_shader->setMat4 ("view", view);

  //         // for (GLuint j = 0; j < lights_size; j++)
  //         //   {
  //         //     batch_shader->setVec3 ("light_positions[" + std::to_string
  //         (j)
  //         //                                + "]",
  //         //                            lights[j].light_pos);
  //         //     batch_shader->setVec3 ("light_colors[" + std::to_string (j)
  //         //                                + "]",
  //         //                            lights[j].light_color);
  //         //   }

  //         for (GLuint g = 0; g < batch_model->Meshes.size (); g++)
  //           {
  //             if (batch_model->HasTexture ())
  //               {
  //                 glActiveTexture (GL_TEXTURE0);
  //                 glBindTexture (GL_TEXTURE_2D,
  //                                batch_model->Textures.at (0).ID);
  //               }
  //             glBindVertexArray (batch_model->Meshes.at (g).vao.GetID ());
  //             glDrawElementsInstanced (
  //                 GL_TRIANGLES,
  //                 static_cast<GLuint> (
  //                     batch_model->Meshes.at (g).indices.size ()),
  //                 GL_UNSIGNED_INT, 0, matrices.size ());
  //             glBindVertexArray (0);
  //             glActiveTexture (0);
  //           }
  //         vbo.Delete ();
  //         // glDeleteBuffers (1, &buffer);
  //       }
  //   }
}
