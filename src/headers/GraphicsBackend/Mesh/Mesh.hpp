#ifndef MESH_HPP
#define MESH_HPP

#include <GraphicsBackend/Buffers/EBO/EBO.h>
#include <GraphicsBackend/Buffers/VAO/VAO.h>
#include <GraphicsBackend/Buffers/VBO/VBO.h>
#include <GraphicsBackend/Shader/Shaders.h>
#include <GraphicsBackend/Texture/Texture.hpp>
#include <GraphicsBackend/Vertex/Vertex.h>
#include <vector>

namespace Model
{
class Mesh
{
public:
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<Texture> textures;

  Mesh (std::vector<Vertex> vertices, std::vector<GLuint> indices,
        std::vector<Texture> textures);
  void Draw (const Shader &shader) const;

  VBO vbo;
  EBO ebo;
  VAO vao;
  void setupMesh ();
};
} // namespace Model

#endif
