#include <GraphicsBackend/Mesh/Mesh.hpp>

Model::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
                  std::vector<Texture> textures) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;
  setupMesh();
}
void Model::Mesh::setupMesh() {
  this->vao.Bind();
  this->vbo.Bind();
  this->vbo.BufferData(this->vertices);
  this->ebo.Bind();
  this->ebo.BufferData(this->indices);

  this->vbo.PointData(POSITION);
  this->vbo.PointData(NORMAL);
  this->vbo.PointData(TEXTURE);
  this->vbo.PointData(COLOR);

  this->vao.Unbind();
  this->vbo.Unbind();
  this->ebo.Unbind();
}

// void Model::Mesh::Draw(Shader &shader) {
//   // bind appropriate textures
//   unsigned int diffuseNr = 1;
//   unsigned int specularNr = 1;
//   unsigned int normalNr = 1;
//   unsigned int heightNr = 1;

//   if (this->textures.size() != 0) {
//     for (unsigned int i = 0; i < this->textures.size(); i++) {
//       glActiveTexture(GL_TEXTURE0 + i);
//       std::string number;
//       std::string name = this->textures[i].type;
//       if (name == "texture_diffuse")
//         number = std::to_string(diffuseNr++);
//       else if (name == "texture_specular")
//         number =
//             std::to_string(specularNr++); // transfer unsigned int to string
//       else if (name == "texture_normal")
//         number = std::to_string(normalNr++); // transfer unsigned int to
//         string
//       else if (name == "texture_height")
//         number = std::to_string(heightNr++); // transfer unsigned int to
//         string

//       glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()),
//       i); glBindTexture(GL_TEXTURE_2D, this->textures[i].ID);
//     }

//     this->vao.Bind();
//     glDrawElements(GL_TRIANGLES, static_cast<GLuint>(this->indices.size()),
//                    GL_UNSIGNED_INT, 0);
//     this->vao.Unbind();
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, 0);
//   } else {
//     this->vao.Bind();
//     glDrawElements(GL_TRIANGLES, static_cast<GLuint>(this->indices.size()),
//                    GL_UNSIGNED_INT, 0);
//     this->vao.Unbind();
//   }
// }
