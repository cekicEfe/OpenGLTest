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
    float SCR_WIDTH,
    float SCR_HEIGHT,
    std::vector<std::unique_ptr<Shader>>* shader,
    Camera* camera,
    std::vector<std::unique_ptr<Model::Light>>* lightSources,
    std::vector<std::unique_ptr<CoreEntity>>* objects)
{
  if(shader != NULL 
      && camera != NULL 
      && lightSources != NULL 
      && objects != NULL
      && (shader->size() > 0)
      && (lightSources->size() > 0)
      && (objects->size() > 0)
      )
  {
    //creates a temporary main vector that takes from input
    std::vector<std::vector<CoreEntity*>> mainVector;
    Shader* localShader = shader->at(0).get(); 
    //lambda definitions 
    auto giveVector = []()
        {
          std::vector<CoreEntity*> newVector;
          return newVector;
        };

    mainVector.push_back(giveVector());
    mainVector.at(0).push_back(objects->at(0).get());

    //Sorts objects into same model-vectors
    for (unsigned int i = 1; i < objects->size(); i++)
    {
      for (unsigned int j = 0; j < mainVector.size(); j++)
      {
        if (mainVector.at(j).at(0)->mpModel == objects->at(i)->mpModel)
        {
          mainVector.at(j).push_back(objects->at(i).get());
          break;
        }
        else if (mainVector.at(j).at(0)->mpModel != objects->at(i)->mpModel && j == mainVector.size() - 1)
        {
          mainVector.push_back(giveVector());
          mainVector.at(mainVector.size() - 1).push_back(objects->at(i).get());
          break;
        }
      }
    }

    size_t mainVectorSize = mainVector.size();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, CLOSE_SIGHT, FAR_SIGHT);
    glm::mat4 view = camera->GetViewMatrix();

    localShader->setInt("texture_diffuse1", 0);
    localShader->setFloat("time", glfwGetTime());
    localShader->setInt("light_count", lightSources->size());

    //buffers lights 
    for(GLuint i = 0 ; i < lightSources->size(); i++)
    {
      localShader->setVec3("light_positions["+std::to_string(i)+ "]", lightSources->at(i)->light_pos);
      localShader->setVec3("light_colors["+std::to_string(i) +"]", lightSources->at(i)->light_color);
    }
    
    localShader->setMat4("projection", projection);
    localShader->setMat4("view", view);

    //renders objects vector by vector
    for (GLuint i = 0; i < mainVectorSize; i++)
    {
      size_t iVectorSize = mainVector.at(i).size();

      //if a model is drawn more than once
      //always once for now
      if (iVectorSize > 0 && mainVector.at(i).at(0)->mpModel != NULL)
      {
        glm::mat4* modelMatrices;
        modelMatrices = new glm::mat4[iVectorSize];
        glm::mat4 modelMat = glm::mat4(1.0f);

        //Loads Matrices
        //MIND THE ROTATION
        for (size_t j = 0; j < iVectorSize; j++)
        {
          modelMat = glm::translate(modelMat, mainVector.at(i).at(j)->mPos);
          modelMat = glm::scale(modelMat, mainVector.at(i).at(j)->mModelScale);
          modelMat = glm::rotate(modelMat,mainVector.at(i).at(j)->mRotDegreeRad,mainVector.at(i).at(j)->mRotAxis);
          modelMatrices[j] = modelMat;//NO ITS NOT ?
          modelMat = glm::mat4(1.0f);
        }

        //Creates buffer and buffer matrices
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, iVectorSize * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

        //Buffers objects meshes
        for (GLuint j = 0; j < mainVector.at(i).at(0)->mpModel->Meshes.size(); j++)
        {
          GLuint VAO = mainVector.at(i).at(0)->mpModel->Meshes[j].vao.id;
          glBindVertexArray(VAO);

          glEnableVertexAttribArray(4);
          glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
          glEnableVertexAttribArray(5);
          glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
          glEnableVertexAttribArray(6);
          glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
          glEnableVertexAttribArray(7);
          glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

          glVertexAttribDivisor(4, 1);
          glVertexAttribDivisor(5, 1);
          glVertexAttribDivisor(6, 1);
          glVertexAttribDivisor(7, 1);

          glBindVertexArray(0);
        }

        //Draws objects here 
        localShader->use();
        for (GLuint g = 0; g < mainVector.at(i).at(0)->mpModel->Meshes.size(); g++)
        {
          if( mainVector.at(i).at(0)->mpModel->HasTexture())
          {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mainVector.at(i).at(0)->mpModel->Textures.at(0).ID);
          }
          glBindVertexArray(mainVector.at(i).at(0)->mpModel->Meshes.at(g).vao.id);
          glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLuint>(mainVector.at(i).at(0)->mpModel->Meshes.at(g).indices.size()), GL_UNSIGNED_INT, 0, iVectorSize);
          glBindVertexArray(0);
        }

        //To free the memory at the CUDA I guess ?
        glDeleteBuffers(1, &buffer);
        //To not leak memory
        delete[] modelMatrices;
      }
    }

    //Gets rid of pointers
    for (unsigned int i = 0; i < mainVectorSize; i++)
    {
      for (unsigned int j = 0; j < mainVector.at(i).size(); j++)
      {
          mainVector.at(i).at(j) = NULL;
      }
    }
    
  }
}

