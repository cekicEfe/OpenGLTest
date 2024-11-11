#ifndef VBO_H
#define VBO_H

#include "model/Vertex.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class VBO
{
private:
  GLuint id;

public:
  VBO ();
  void Bind ();
  void Unbind ();
  void Delete ();
  void BufferData (std::vector<Model::Vertex> vertices);
  void BufferData (std::vector<glm::mat4> *Instances);
  void PointData (VERTEX_OFFSET offSetName);
};

#endif // !VBO_H
