
#include <GraphicsBackend/Model/Model.h>
//
#include "GraphicsBackend/Material/Material.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <assimp/types.h>
#include <filesystem>
#include <stb_image/stb_image.h>

Model::Model::Model (std::string const &path, bool gamma, bool flip_textures)
    : gammaCorrection (gamma)
{
  std::cout << "Model with path : " << path << " created" << std::endl;
  stbi_set_flip_vertically_on_load (flip_textures);
  loadModel (path);
}

bool
Model::Model::HasTexture () const
{
  if (this->Textures.size () == 0)
    {
      return false;
    }
  else
    {
      return true;
    };
}

Model::Model::~Model ()
{
}

void
Model::Model::Draw (const Shader &shader) const
{
  for (GLuint i = 0; i < this->Meshes.size (); i++)
    {
      this->Meshes[i].Draw (shader);
    }
}

void
Model::Model::loadModel (std::string path)
{
  // read file via ASSIMP
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile (
      path,
      aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs
          | aiProcess_CalcTangentSpace);
  // check for errors
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
      || !scene->mRootNode) // if is Not Zero
    {
      std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString ()
                << std::endl;
      return;
    }
  // retrieve the directory path of the filepath
  this->path = path;
  this->animCount = scene->mNumAnimations;
  this->directory = path.substr (0, path.find_last_of ('/'));
  // process ASSIMP's root node recursively
  processNode (scene->mRootNode, scene);
}

void
Model::Model::processNode (aiNode *node, const aiScene *scene)
{
  // process all the node's meshes (if any)
  for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      this->Meshes.push_back (processMesh (mesh, scene));
    }
  // then do the same for each of its children
  for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
      processNode (node->mChildren[i], scene);
    }
}

Model::Mesh
Model::Model::processMesh (aiMesh *mesh, const aiScene *scene)
{
  // data to fill
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<Texture> textures;
  std::map<std::string, uint> boneMapping;
  std::vector<glm::mat4> boneOffsets;

  // walk through each of the mesh's vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
      Vertex vertex;
      glm::vec3 vector; // we declare a placeholder vector since assimp uses
                        // its own vector class that doesn't directly convert
                        // to glm's vec3 class so we transfer the data to this
                        // placeholder glm::vec3 first.
      // positions
      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.position = vector;

      // normals
      if (mesh->HasNormals ())
        {
          vector.x = mesh->mNormals[i].x;
          vector.y = mesh->mNormals[i].y;
          vector.z = mesh->mNormals[i].z;
          vertex.normal = vector;
        }
      if (mesh->HasVertexColors (i))
        {
          vector.x = mesh->mColors[i]->r;
          vector.y = mesh->mColors[i]->g;
          vector.z = mesh->mColors[i]->b;
          vertex.color = glm::vec4 (vector, mesh->mColors[i]->a);
        }
      // texture coordinates
      if (mesh->mTextureCoords[0]) // does the mesh contain texture
                                   // coordinates?
        {
          glm::vec2 vec;
          // a vertex can contain up to 8 different texture coordinates. We
          // thus make the assumption that we won't use models where a vertex
          // can have multiple texture coordinates so we always take the first
          // set (0).
          vec.x = mesh->mTextureCoords[0][i].x;
          vec.y = mesh->mTextureCoords[0][i].y;
          vertex.texture = vec;

          //          tangent
          vector.x = mesh->mTangents[i].x;
          vector.y = mesh->mTangents[i].y;
          vector.z = mesh->mTangents[i].z;
          vertex.tangent = vector;

          // bitangent
          vector.x = mesh->mBitangents[i].x;
          vector.y = mesh->mBitangents[i].y;
          vector.z = mesh->mBitangents[i].z;
          vertex.biTangent = vector;
        }
      else
        vertex.texture = glm::vec2 (0.0f, 0.0f);

      vertices.push_back (vertex);
    }

  // walk through mesh bones
  for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
      int boneID = -1;
      std::string boneName = mesh->mBones[boneIndex]->mName.C_Str ();
      if (m_BoneInfoMap.find (boneName) == m_BoneInfoMap.end ())
        {
          BoneInfo newBoneInfo;
          newBoneInfo.id = m_BoneCounter;
          newBoneInfo.offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat (
              mesh->mBones[boneIndex]->mOffsetMatrix);
          m_BoneInfoMap[boneName] = newBoneInfo;
          boneID = m_BoneCounter;
          m_BoneCounter++;
        }
      else
        {
          boneID = m_BoneInfoMap[boneName].id;
        }
      assert (boneID != -1);
      auto weights = mesh->mBones[boneIndex]->mWeights;
      int numWeights = mesh->mBones[boneIndex]->mNumWeights;

      for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
          int vertexId = weights[weightIndex].mVertexId;
          float weight = weights[weightIndex].mWeight;
          assert (vertexId <= vertices.size ());
          for (int p = 0; p < 4; ++p)
            {
              if (vertices[vertexId].boneIds[p] < 0)
                {
                  vertices[vertexId].weights[p] = weight;
                  vertices[vertexId].boneIds[p] = boneID;
                  break;
                }
            }
        }
    }

  // now wak through each of the mesh's faces (a face is a mesh its triangle)
  // and retrieve the corresponding vertex indices.
  for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
      aiFace face = mesh->mFaces[i];
      // retrieve all indices of the face and store them in the indices vector
      for (GLuint j = 0; j < face.mNumIndices; j++)
        indices.push_back (face.mIndices[j]);
    }

  // process materials
  aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
  // we assume a convention for sampler names in the shaders. Each diffuse
  // texture should be named as 'texture_diffuseN' where N is a sequential
  // number ranging from 1 to MAX_SAMPLER_NUMBER. Same applies to other texture
  // as the following list summarizes: diffuse: texture_diffuseN specular:
  // texture_specularN normal: texture_normalN

  // 1. diffuse maps
  std::vector<Texture> diffuseMaps = loadMaterialTextures (
      material, aiTextureType_DIFFUSE, "texture_diffuse");
  textures.insert (textures.end (), diffuseMaps.begin (), diffuseMaps.end ());
  // 2. specular maps
  std::vector<Texture> specularMaps = loadMaterialTextures (
      material, aiTextureType_SPECULAR, "texture_specular");
  textures.insert (
      textures.end (), specularMaps.begin (), specularMaps.end ());
  // 3. normal maps
  std::vector<Texture> normalMaps = loadMaterialTextures (
      material, aiTextureType_HEIGHT, "texture_normal");
  textures.insert (textures.end (), normalMaps.begin (), normalMaps.end ());
  // 4. height maps
  std::vector<Texture> heightMaps = loadMaterialTextures (
      material, aiTextureType_AMBIENT, "texture_height");
  textures.insert (textures.end (), heightMaps.begin (), heightMaps.end ());

  // return a mesh object created from the extracted mesh data
  return Mesh (vertices, indices, textures);
}

std::vector<Model::Texture>
Model::Model::loadMaterialTextures (aiMaterial *mat, aiTextureType type,
                                    std::string typeName)
{
  std::vector<Texture> new_textures_loaded;
  for (GLuint i = 0; i < mat->GetTextureCount (type); i++)
    {
      aiString str;
      mat->GetTexture (type, i, &str);
      std::string model_str = str.data;

      model_str = model_str.substr (model_str.find_last_of ("/\\") + 1);

      std::filesystem::path model_str_path
          = std::filesystem::path (this->directory)
            / std::filesystem::path (model_str);

      // std::cout << model_str << std::endl;
      // std::cout << model_str_path << std::endl;

      // check if texture was loaded before and if so, continue to next
      // iteration: skip loading a new texture
      bool skip = false;
      for (GLuint j = 0; j < this->Textures.size (); j++)
        {
          if (std::strcmp (this->Textures[j].path.c_str (),
                           model_str_path.c_str ())
              == 0)
            {
              new_textures_loaded.push_back (this->Textures[j]);
              skip = true; // a texture with the same filepath has already been
                           // loaded, continue to next one. (optimization)
              break;
            }
        }
      if (!skip)
        { // if texture hasn't been loaded already, load it
          Texture texture;
          aiColor3D color;
          float shininess;

          texture.ID = TextureFromFile (
              model_str_path.c_str (), this->directory, this->gammaCorrection);
          texture.type = typeName;
          texture.path = model_str_path.c_str ();

          mat->Get (AI_MATKEY_COLOR_DIFFUSE, color);
          texture.material.diffuse = glm::vec3 (color.r, color.b, color.g);
          mat->Get (AI_MATKEY_COLOR_AMBIENT, color);
          texture.material.ambient = glm::vec3 (color.r, color.b, color.g);
          mat->Get (AI_MATKEY_COLOR_SPECULAR, color);
          texture.material.specular = glm::vec3 (color.r, color.b, color.g);
          mat->Get (AI_MATKEY_SHININESS, shininess);
          texture.material.shininess = shininess;

          new_textures_loaded.push_back (texture);
          this->Textures.push_back (
              texture); // store it as texture loaded for entire model, to
                        // ensure we won't unnecessary load duplicate textures.
        }
    }
  return new_textures_loaded;
}

// checks all material textures of a given type and loads the textures if
// they're not loaded yet. the required info is returned as a Texture struct.
GLuint
Model::Model::TextureFromFile (const char *path, const std::string &directory,
                               bool gamma)
{
  std::string filename = std::filesystem::path (path);
  // std::cout << filename << std::endl;
  // size_t index = filename.find_last_of("/\\");
  // std::filesystem::path filename_path =
  // directory / std::filesystem::path(filename.substr(index + 1));
  // std::cout << filename_path << std::endl;

  GLuint textureID = 0;
  glGenTextures (1, &textureID);

  int width, height, nrComponents;
  unsigned char *data
      = stbi_load (filename.c_str (), &width, &height, &nrComponents, 0);
  if (data)
    {
      GLenum format;
      if (nrComponents == 1)
        format = GL_RED;
      else if (nrComponents == 3)
        format = GL_RGB;
      else if (nrComponents == 4)
        format = GL_RGBA;

      glBindTexture (GL_TEXTURE_2D, textureID);
      glTexImage2D (GL_TEXTURE_2D,
                    0,
                    format,
                    width,
                    height,
                    0,
                    format,
                    GL_UNSIGNED_BYTE,
                    data);
      glGenerateMipmap (GL_TEXTURE_2D);

      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri (
          GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glBindTexture (GL_TEXTURE_2D, 0);

      stbi_image_free (data);
    }
  else
    {
      std::cout << "Texture failed to load at path: " << filename << std::endl;
      stbi_image_free (data);
    }
  return textureID;
}
