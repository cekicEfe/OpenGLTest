#include "EBO.h"
#include <CoreBackend/ErrorHandler/ErrorHandler.hpp>

EBO::EBO() {
  glGenBuffers(1, &this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

EBO::~EBO() {
  // this->Delete();
}

void EBO::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

void EBO::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

void EBO::Delete() {
  glDeleteBuffers(1, &this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

void EBO::BufferData(std::vector<GLuint> indices) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               &indices[0], GL_STATIC_DRAW);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}
