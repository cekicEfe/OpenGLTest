#include "CoreClass/RenderHandler/RenderHandler.h"
#include <glm/glm.hpp>

core::RenderHandler *core::RenderHandler::instance = nullptr;

core::RenderHandler::RenderHandler() {
  std::cout << "Called RenderHandler Constructor" << std::endl;
}
core::RenderHandler::~RenderHandler() {
  std::cout << "Called RenderHandler DEconstructor" << std::endl;
}
core::RenderHandler *core::RenderHandler::createInstance() {
  if (core::RenderHandler::instance == nullptr) {
    std::cout << "Creating a renderHandler Instance" << std::endl;
    core::RenderHandler::instance = new core::RenderHandler();
    return instance;
  } else {
    std::cout << "A renderHandler already exists" << std::endl;
    return nullptr;
  }
}
void core::RenderHandler::deleteInstance() {
  if (core::RenderHandler::instance == nullptr) {
    std::cout << "No renderHandler exist to delete" << std::endl;
  } else {
    std::cout << "Deleting render handler" << std::endl;
    delete core::RenderHandler::instance;
    core::RenderHandler::instance = nullptr;
  }
}

void core::RenderHandler::DrawInstanced(
    float SCR_WIDTH, float SCR_HEIGHT, Camera *const camera,
    const std::vector<Model::Light> *const lights,
    const std::vector<core::CoreEntity> *const entities) {
  if (camera != NULL && lights != NULL && entities != NULL &&
      (lights->size() > 0) && (entities->size() > 0)) {

    for (size_t i = 0; i < entities->size(); i++) {

      static Model::Model *model = entities->at(i).pModel;
      static Shader *shader = entities->at(i).pShader;
      static bool initBatch = true;
      static std::vector<glm::mat4> modelMatrices;

      if (initBatch) {
        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT,
            CLOSE_SIGHT, FAR_SIGHT);

        glm::mat4 view = camera->GetViewMatrix();
        shader->setInt("texture_diffuse1", 0);
        shader->setFloat("time", glfwGetTime());
        shader->setInt("light_count", lights->size());
        for (GLuint i = 0; i < lights->size(); i++) {
          shader->setVec3("light_positions[" + std::to_string(i) + "]",
                          lights->at(i).light_pos);
          shader->setVec3("light_colors[" + std::to_string(i) + "]",
                          lights->at(i).light_color);
          shader->setMat4("projection", projection);
          shader->setMat4("view", view);

          model = entities->at(i).pModel;
          shader = entities->at(i).pShader;
          modelMatrices.clear();

          initBatch = false;
        }
      }

      if (model != entities->at(i + 1).pModel ||
          shader != entities->at(i + 1).pShader || i + 1 == entities->size()) {

        glm::mat4 modelMatrix = glm::mat4(1.0);
        modelMatrix =
            glm::translate(modelMatrix, entities->at(i).movComponent.pos);
        modelMatrix = glm::scale(modelMatrix, entities->at(i).modelScale);
        modelMatrix = glm::rotate(
            modelMatrix, entities->at(i).rotComponent.RotationDegreeDueAxis,
            entities->at(i).rotComponent.RotationAxis);
        modelMatrices.push_back(modelMatrix);

        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4),
                     &modelMatrices[0], GL_STATIC_DRAW);

        for (GLuint j = 0; j < entities->at(i).pModel->Meshes.size(); j++) {
          GLuint VAO = entities->at(i).pModel->Meshes[j].vao.id;
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
        shader->use();
        for (GLuint g = 0; g < entities->at(i).pModel->Meshes.size(); g++) {
          if (entities->at(i).pModel->HasTexture()) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,
                          entities->at(i).pModel->Textures.at(0).ID);
          }
          glBindVertexArray(entities->at(i).pModel->Meshes.at(g).vao.id);
          glDrawElementsInstanced(
              GL_TRIANGLES,
              static_cast<GLuint>(
                  entities->at(i).pModel->Meshes.at(g).indices.size()),
              GL_UNSIGNED_INT, 0, modelMatrices.size());
          glBindVertexArray(0);
        }

        glDeleteBuffers(1, &buffer);
        initBatch = true;

      } else {
        glm::mat4 modelMatrix = glm::mat4(1.0);
        modelMatrix =
            glm::translate(modelMatrix, entities->at(i).movComponent.pos);
        modelMatrix = glm::scale(modelMatrix, entities->at(i).modelScale);
        modelMatrix = glm::rotate(
            modelMatrix, entities->at(i).rotComponent.RotationDegreeDueAxis,
            entities->at(i).rotComponent.RotationAxis);
        modelMatrices.push_back(modelMatrix);
      }
    }

    /*
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT,
    CLOSE_SIGHT, FAR_SIGHT);

    glm::mat4 view = camera->GetViewMatrix();
    localShader->setInt("texture_diffuse1", 0);
    localShader->setFloat("time", glfwGetTime());
    localShader->setInt("light_count", lightSources->size());
    for (GLuint i = 0; i < lightSources->size(); i++) {
      localShader->setVec3("light_positions[" + std::to_string(i) + "]",
                           lightSources->at(i)->light_pos);
      localShader->setVec3("light_colors[" + std::to_string(i) + "]",
                           lightSources->at(i)->light_color);
    }
    localShader->setMat4("projection", projection);
    localShader->setMat4("view", view);
    */

    /*
    for (auto &elem : *map) {
      if (map != NULL && elem.second.second.size() > 0) {
        glm::mat4 *modelMatrices;
        modelMatrices = new glm::mat4[elem.second.second.size()];
        glm::mat4 modelMat = glm::mat4(1.0f);

        auto currentVecSize = elem.second.second.size();

        // Loads Matrices
        // MIND THE ROTATION
        for (size_t j = 0; j < currentVecSize; j++) {
          modelMat = glm::translate(modelMat,
                                    elem.second.second.at(j)->movComponent.pos);
          modelMat = glm::scale(modelMat, elem.second.second.at(j)->modelScale);

          modelMat = glm::rotate(
              modelMat,
              elem.second.second.at(j)
                  .get()
                  ->rotComponent.RotationDegreeDueAxis,
              elem.second.second.at(j).get()->rotComponent.RotationAxis);

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
        for (GLuint j = 0; j < elem.second.first->Meshes.size(); j++) {
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
        for (GLuint g = 0; g < elem.second.first->Meshes.size(); g++) {
          if (elem.second.first->HasTexture()) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, elem.second.first->Textures.at(0).ID);
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
    */
  }
}
