#ifndef VBO_H
#define VBO_H

#include <GraphicsBackend/Vertex/Vertex.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class VBO {
private:
  GLuint id;

public:
  VBO();
  ~VBO();

  void Bind();
  void Unbind();
  void Delete();
  void PointData(VERTEX_OFFSET offSetName);

  void PointData(size_t layoutIndex, size_t dataSize, size_t stride,
                 const void *address);
  template <typename A, typename B, typename C, typename D>
  void PointData(A, B, C, const D) = delete;

  void BufferData(std::vector<glm::mat4> *Instances);
  void BufferData(std::vector<Model::Vertex> &vertices);
};

#endif // !VBO_H
