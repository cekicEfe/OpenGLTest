#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <GraphicsBackend/Model/Model.h>
#include <assimp/Importer.hpp>
#include <stdexcept>

namespace Model
{
struct AssimpNodeData
{
  glm::mat4 transformation;
  std::string name;
  int childrenCount;
  std::vector<AssimpNodeData> children;
};

class Animation
{
public:
  Animation () = default;

  Animation (const std::string &animationPath, Model *model,
             size_t model_index)
  {
    Assimp::Importer importer;
    const aiScene *scene
        = importer.ReadFile (animationPath, aiProcess_Triangulate);
    assert (scene && scene->mRootNode);
    if (model_index < model->GetAnimCount () && model_index >= 0)
      {
        auto animation = scene->mAnimations[model_index];
        m_Duration = animation->mDuration;
        m_TicksPerSecond = animation->mTicksPerSecond;
        ReadHeirarchyData (m_RootNode, scene->mRootNode);
        ReadMissingBones (animation, *model);
      }
    else
      throw std::invalid_argument ("invalid index for model animation");
  }

  ~Animation ()
  {
  }

  Bone *
  FindBone (const std::string &name)
  {
    auto iter = std::find_if (
        m_Bones.begin (), m_Bones.end (), [&] (const Bone &Bone) {
          return Bone.GetBoneName () == name;
        });
    if (iter == m_Bones.end ())
      return nullptr;
    else
      return &(*iter);
  }

  inline float
  GetTicksPerSecond ()
  {
    return m_TicksPerSecond;
  }

  inline float
  GetDuration ()
  {
    return m_Duration;
  }

  inline const AssimpNodeData &
  GetRootNode ()
  {
    return m_RootNode;
  }

  inline const std::map<std::string, BoneInfo> &
  GetBoneIDMap ()
  {
    return m_BoneInfoMap;
  }

private:
  void
  ReadMissingBones (const aiAnimation *animation, Model &model)
  {
    int size = animation->mNumChannels;

    auto &boneInfoMap
        = model.GetBoneInfoMap (); // getting m_BoneInfoMap from Model class
    int &boneCount
        = model.GetBoneCount (); // getting the m_BoneCounter from Model class

    // reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++)
      {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;

        if (boneInfoMap.find (boneName) == boneInfoMap.end ())
          {
            boneInfoMap[boneName].id = boneCount;
            boneCount++;
          }
        m_Bones.push_back (Bone (channel->mNodeName.data,
                                 boneInfoMap[channel->mNodeName.data].id,
                                 channel));
      }

    m_BoneInfoMap = boneInfoMap;
  }

  void
  ReadHeirarchyData (AssimpNodeData &dest, const aiNode *src)
  {
    assert (src);

    dest.name = src->mName.data;
    dest.transformation
        = AssimpGLMHelpers::ConvertMatrixToGLMFormat (src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++)
      {
        AssimpNodeData newData;
        ReadHeirarchyData (newData, src->mChildren[i]);
        dest.children.push_back (newData);
      }
  }
  float m_Duration;
  int m_TicksPerSecond;
  std::vector<Bone> m_Bones;
  AssimpNodeData m_RootNode;
  std::map<std::string, BoneInfo> m_BoneInfoMap;
};

} // namespace Model

#endif
