#include "CoreClass/RenderHandler/RenderHandler.h"

core::RenderHandler::RenderHandler()
{
  std::cout << "Called RenderFunctor Constructor" << std::endl;
}

core::RenderHandler::~RenderHandler()
{
  std::cout << "Called RenderFunctor DEconstructor" << std::endl;
}

void core::RenderHandler::DrawInstanced(
    float SCR_WIDTH, float SCR_HEIGHT, Camera *camera,
    std::vector<std::unique_ptr<Shader>> *shader,
    std::vector<std::unique_ptr<Model::Light>> *lightSources,
    std::unordered_map<std::string,
                       std::pair<std::unique_ptr<Model::Model>,
                                 std::vector<std::shared_ptr<core::CoreEntity>>>>
        *map)
{
  if (shader != NULL && camera != NULL && lightSources != NULL && map != NULL &&
      (shader->size() > 0) && (lightSources->size() > 0) && (map->size() > 0))
  {

    // creates a temporary main vector that takes from input
    Shader *localShader = shader->at(0).get();

    // shader related things here :
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, CLOSE_SIGHT,
        FAR_SIGHT);

    glm::mat4 view = camera->GetViewMatrix();
    localShader->setInt("texture_diffuse1", 0);
    localShader->setFloat("time", glfwGetTime());
    localShader->setInt("light_count", lightSources->size());
    for (GLuint i = 0; i < lightSources->size(); i++)
    {
      localShader->setVec3("light_positions[" + std::to_string(i) + "]",
                           lightSources->at(i)->light_pos);
      localShader->setVec3("light_colors[" + std::to_string(i) + "]",
                           lightSources->at(i)->light_color);
    }
    localShader->setMat4("projection", projection);
    localShader->setMat4("view", view);

    for (auto &elem : *map)
    {
      if (map != NULL && elem.second.second.size() > 0)
      {
        glm::mat4 *modelMatrices;
        modelMatrices = new glm::mat4[elem.second.second.size()];
        glm::mat4 modelMat = glm::mat4(1.0f);

        auto currentVecSize = elem.second.second.size();

        // Loads Matrices
        // MIND THE ROTATION
        for (size_t j = 0; j < currentVecSize; j++)
        {
          modelMat = glm::translate(modelMat, elem.second.second.at(j)->pos);
          modelMat = glm::scale(modelMat, elem.second.second.at(j)->modelScale);
          modelMat = glm::rotate(modelMat, elem.second.second.at(j)->rotDegreeRad,
                                 elem.second.second.at(j)->rotAxis);
          modelMatrices[j] = modelMat;
          modelMat = glm::mat4(1.0f);
        }

        // Creates buffer and buffer matrices
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, currentVecSize * sizeof(glm::mat4),
                     &modelMatrices[0], GL_STATIC_DRAW);

        // Buffers objects meshes
        for (GLuint j = 0; j < elem.second.first->Meshes.size();
             j++)
        {
          GLuint VAO = elem.second.first->Meshes[j].vao.id;
          glBindVertexArray(VAO);

          glEnableVertexAttribArray(4);
          glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                                (void *)0);
          glEnableVertexAttribArray(5);
          glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                                (void *)(1 * sizeof(glm::vec4)));
          glEnableVertexAttribArray(6);
          glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                                (void *)(2 * sizeof(glm::vec4)));
          glEnableVertexAttribArray(7);
          glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                                (void *)(3 * sizeof(glm::vec4)));

          glVertexAttribDivisor(4, 1);
          glVertexAttribDivisor(5, 1);
          glVertexAttribDivisor(6, 1);
          glVertexAttribDivisor(7, 1);

          glBindVertexArray(0);
        }

        // Draws objects here
        localShader->use();
        for (GLuint g = 0; g < elem.second.first->Meshes.size();
             g++)
        {
          if (elem.second.first->HasTexture())
          {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,
                          elem.second.first->Textures.at(0).ID);
          }
          glBindVertexArray(elem.second.first->Meshes.at(g).vao.id);
          glDrawElementsInstanced(
              GL_TRIANGLES,
              static_cast<GLuint>(
                  elem.second.first->Meshes.at(g).indices.size()),
              GL_UNSIGNED_INT, 0, currentVecSize);
          glBindVertexArray(0);
        }

        // To free the memory at the CUDA I guess ?
        glDeleteBuffers(1, &buffer);

        // To not leak memory
        delete[] modelMatrices;
      }
    }
  }
}
