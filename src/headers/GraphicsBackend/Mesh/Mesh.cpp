#include <GraphicsBackend/Mesh/Mesh.hpp>

Model::Mesh::Mesh (std::vector<Vertex> vertices, std::vector<GLuint> indices,
                   std::vector<Texture> textures)
{
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;
  setupMesh ();
}
void
Model::Mesh::setupMesh ()
{
  this->vao.Bind ();
  this->vbo.Bind ();
  this->vbo.BufferData (this->vertices);
  this->ebo.Bind ();
  this->ebo.BufferData (this->indices);

  this->vbo.PointData (POSITION);
  this->vbo.PointData (NORMAL);
  this->vbo.PointData (TEXTURE);
  this->vbo.PointData (COLOR);

  this->vao.Unbind ();
  // this->vbo.Unbind ();
  // this->ebo.Unbind ();
}

void
Model::Mesh::Draw (const Shader &shader) const
{
  // bind appropriate textures
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  unsigned int normalNr = 1;
  unsigned int heightNr = 1;

  for (unsigned int i = 0; i < textures.size (); i++)
    {
      glActiveTexture (GL_TEXTURE0
                       + i); // active proper texture unit before binding
      // retrieve texture number (the N in diffuse_textureN)
      std::string number;
      std::string name = textures[i].type;
      if (name == "texture_diffuse")
        number = std::to_string (diffuseNr++);
      else if (name == "texture_specular")
        number
            = std::to_string (specularNr++); // transfer unsigned int to string
      else if (name == "texture_normal")
        number
            = std::to_string (normalNr++); // transfer unsigned int to string
      else if (name == "texture_height")
        number
            = std::to_string (heightNr++); // transfer unsigned int to string

      // now set the sampler to the correct texture unit
      glUniform1i (glGetUniformLocation (shader.ID, (name + number).c_str ()),
                   i);
      // and finally bind the texture
      glBindTexture (GL_TEXTURE_2D, textures[i].ID);
    }

  // draw mesh
  this->vao.Bind ();
  glDrawElements (GL_TRIANGLES, static_cast<unsigned int> (indices.size ()),
                  GL_UNSIGNED_INT, 0);
  this->vao.Unbind ();

  // always good practice to set everything back to defaults once
  // configured.
  glActiveTexture (GL_TEXTURE0);
}
