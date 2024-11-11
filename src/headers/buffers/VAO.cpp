#include "VAO.h"

VAO::VAO ()
{
  glGenVertexArrays (1, &this->id);
}
void
VAO::Bind ()
{
  glBindVertexArray (this->id);
}
void
VAO::Unbind ()
{
  glBindVertexArray (0);
}
void
VAO::Delete ()
{
  glDeleteVertexArrays (1, &this->id);
}
