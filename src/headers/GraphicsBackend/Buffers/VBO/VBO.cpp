#include "VBO.h"

using namespace Model;

VBO::VBO() { glGenBuffers(1, &this->id); };

VBO::~VBO() {
  // this->Delete();
}

void VBO::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, this->id); }

void VBO::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::Delete() { glDeleteBuffers(1, &this->id); }

void VBO::BufferData(std::vector<Vertex> &vertices) {
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);
}

void VBO::BufferData(std::vector<glm::mat4> *Instances) {
  glBufferData(GL_ARRAY_BUFFER, Instances->size() * sizeof(glm::mat4),
               &Instances->at(0), GL_STATIC_DRAW);
}

void VBO::PointData(VERTEX_INCLUDES offSetName) {
  switch (offSetName) {
  case POSITION:
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    break;
  case NORMAL:
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, normal));
    break;
  case TEXTURE:
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, texture));
    break;
  case COLOR:
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, color));
    break;
  }
}
