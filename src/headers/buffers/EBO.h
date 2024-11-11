#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <vector>

class EBO
{
public:
  GLuint id;
  EBO ();
  void Bind ();
  void Unbind ();
  void Delete ();
  void BufferData (std::vector<GLuint> indices);
};

#endif // EBO_H
