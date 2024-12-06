#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <json/json.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <buffers/EBO.h>
#include <buffers/VAO.h>
#include <buffers/VBO.h>
#include <model/Shaders.h>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace Model
{

class Texture
{
public:
  GLuint ID;
  std::string type;
  std::string path;
};

// COMPLETE
class Mesh
{
public:
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<Texture> textures;

  Mesh (std::vector<Vertex> vertices, std::vector<GLuint> indices,
        std::vector<Texture> textures);
  void Draw (Shader &shader);

  VBO vbo;
  EBO ebo;
  VAO vao;
  void setupMesh ();
};

class Model
{
public:
  Model (std::string const &path, GLboolean gamma = false);
  GLboolean HasTexture () const;
  void Draw (Shader &shader);
  ~Model ();

  // private:
  std::vector<Mesh> Meshes;
  std::vector<Texture> Textures;
  std::string directory;
  std::string path;
  GLboolean gammaCorrection;

  void loadModel (std::string path);
  void processNode (aiNode *node, const aiScene *scene);
  Mesh processMesh (aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures (aiMaterial *mat,
                                             aiTextureType type,
                                             std::string typeName);
  GLuint TextureFromFile (const char *path, const std::string &directory,
                          bool gamma);
};

class Light
{
public:
  glm::vec3 light_color;
  glm::vec3 light_pos;
  GLfloat ambient = 0;
  GLfloat diffuse = 0;
  GLfloat specular = 0;
};

class Material
{
public:
  GLfloat ambient;
  GLfloat diffuse;
  GLfloat specular;
  float shininess;
};

} // namespace Model

#endif // !MODEL_H
