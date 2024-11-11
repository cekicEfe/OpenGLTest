#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
//
#include <GLFW/glfw3.h>

class VAO
{
public:
  GLuint id;
  VAO ();
  void Bind ();
  void Unbind ();
  void Delete ();
};

#endif // !VAO_H
