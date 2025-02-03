#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <json/json.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <GraphicsBackend/Buffers/EBO/EBO.h>
#include <GraphicsBackend/Buffers/VAO/VAO.h>
#include <GraphicsBackend/Buffers/VBO/VBO.h>
#include <GraphicsBackend/Mesh/Mesh.hpp>
#include <GraphicsBackend/Shader/Shaders.h>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace Model
{

class Model
{
public:
  Model (std::string const &path, GLboolean gamma = false);
  GLboolean HasTexture () const;

  void Draw (const Shader &shader) const;

  ~Model ();

  std::vector<Mesh> Meshes;
  std::vector<Texture> Textures;
  std::string directory;
  std::string path;
  GLboolean gammaCorrection;

  bool containsTextures;
  bool containsMaterials;
  bool containsColours;

private:
  void loadModel (std::string path);
  void processNode (aiNode *node, const aiScene *scene);
  Mesh processMesh (aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures (aiMaterial *mat,
                                             aiTextureType type,
                                             std::string typeName);
  GLuint TextureFromFile (const char *path, const std::string &directory,
                          bool gamma);
};

} // namespace Model

#endif // !MODEL_H
