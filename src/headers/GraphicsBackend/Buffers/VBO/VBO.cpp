#include "VBO.h"
#include "CoreBackend/ErrorHandler/ErrorHandler.hpp"
#include "GraphicsBackend/Vertex/Vertex.h"
#include <cstddef>

using namespace Model;

VBO::VBO() {
  glGenBuffers(1, &this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
};

VBO::~VBO() {
  // this->Delete();
}

void VBO::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

void VBO::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

void VBO::Delete() { glDeleteBuffers(1, &this->id); }

void VBO::BufferData(std::vector<Vertex> &vertices) {
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

void VBO::BufferData(std::vector<glm::mat4> *Instances) {
  glBufferData(GL_ARRAY_BUFFER, Instances->size() * sizeof(glm::mat4),
               &Instances->at(0), GL_STATIC_DRAW);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

void VBO::PointData(VERTEX_INCLUDES offSetName) {
  switch (offSetName) {
  case POSITION:
    glEnableVertexAttribArray(0);
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    break;
  case NORMAL:
    glEnableVertexAttribArray(1);
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, normal));
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    break;
  case TEXTURE:
    glEnableVertexAttribArray(2);
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, texture));
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    break;
  case COLOR:
    glEnableVertexAttribArray(3);
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, color));
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    break;
  case TANGENT:
    glEnableVertexAttribArray(4);
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, tangent));
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    break;
  case BITANGENT:
    glEnableVertexAttribArray(5);
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, biTangent));
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    break;
  case BONE:
    glEnableVertexAttribArray(6);
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    glVertexAttribPointer(6, 4, GL_INT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, boneIds));
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    break;
  case WEIGHT:
    glEnableVertexAttribArray(7);
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, weights));
    core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
    break;
  }
}
