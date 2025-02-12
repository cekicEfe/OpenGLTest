#include "VAO.h"
#include <CoreBackend/ErrorHandler/ErrorHandler.hpp>

VAO::VAO() {
  glGenVertexArrays(1, &this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

VAO::~VAO() {
  // Fuck, this line cost me 5 days to fucking find NO render call "works"
  // all meshes created through copy constructors
  // every time I create and call a copy constructor a mesh all previus VAO ID's
  // gets deleted thus no vertexes created by other VBO's gets pointed I dont
  // even understand half of it fuck that

  // Note to self:
  // DO NOT BLINDLY ADD BOILER PLATES
  // DUMB MOTHERFUCKER
  // this->Delete();
}

void VAO::Bind() const {
  glBindVertexArray(this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

void VAO::Unbind() const {
  glBindVertexArray(0);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

void VAO::Delete() {
  glDeleteVertexArrays(1, &this->id);
  core::ErrorHandler::getOpenglError(__FILE__, __LINE__);
}

GLuint VAO::GetID() const { return this->id; }
