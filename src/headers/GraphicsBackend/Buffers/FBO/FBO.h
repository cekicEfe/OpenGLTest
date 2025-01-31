#ifndef FBO_H
#define FBO_H

#include <glad/glad.h>
//
#include <GLFW/glfw3.h>

// Frame buffer object
class FBO {
private:
  GLuint id;

public:
  FBO();
  ~FBO();

  void Bind();
  void Unbind();
  void Delete();
};

#endif // !FBO_H
