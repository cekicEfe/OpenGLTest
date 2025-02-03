#include "EBO.h"
EBO::EBO() { glGenBuffers(1, &this->id); }

EBO::~EBO() {
  // this->Delete();
}

void EBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id); }

void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::Delete() { glDeleteBuffers(1, &this->id); }

void EBO::BufferData(std::vector<GLuint> indices) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               &indices[0], GL_STATIC_DRAW);
}
