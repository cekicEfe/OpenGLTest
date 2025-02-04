#include "VAO.h"

VAO::VAO() { glGenVertexArrays(1, &this->id); }

VAO::~VAO() {
  // Fuck, this line cost me 5 days to fucking find NO render call "works"
  // all meshes created through copy constructors
  // every time I create and call a copy constructor a mesh all previus VAO ID's
  // gets deleted thus no vertexes created by other VBO's gets pointed I dont
  // even understand half of it fuck that

  // Note to self:
  // DO NOT BLINDLY ADD BOILER PLATES
  // DUMB MOTHERFUCKER
  // this->Delete ();
}

void VAO::Bind() const { glBindVertexArray(this->id); }

void VAO::Unbind() const { glBindVertexArray(0); }

void VAO::Delete() { glDeleteVertexArrays(1, &this->id); }

GLuint VAO::GetID() const { return this->id; }
