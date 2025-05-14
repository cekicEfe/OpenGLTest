#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <nlohmann/json.hpp>

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
  Model (std::string const &path, bool gamma = false,
         bool flip_textures = true);
  ~Model ();

  bool HasTexture () const;
  void Draw (const Shader &shader) const;

  auto &
  GetBoneInfoMap ()
  {
    return m_BoneInfoMap;
  }
  int &
  GetBoneCount ()
  {
    return m_BoneCounter;
  }

  uint
  GetAnimCount ()
  {
    return this->animCount;
  }

private:
  std::vector<Mesh> Meshes;
  std::vector<Texture> Textures;
  std::map<std::string, BoneInfo> m_BoneInfoMap; //
  int m_BoneCounter = 0;

  std::string directory;
  std::string path;
  bool gammaCorrection;
  uint animCount;

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
