#include "HitBox.h"

void core::HitBox::AttachEntity(CoreEntity *entity) {
  this->mConnectedEntity = entity;
}

// Generates a Hitbox by sort throughghhg nodes which kind of sucks
void core::HitBox::GenerateHitbox() {
  /*
  if (this->mConnectedEntity != nullptr)
  {
    if (this->mConnectedEntity->model != nullptr)
    {
      //(probable) extreme points of the model

      //                       +y       -z
      //                       //       /
      //                       //      /
      //                       //     /
      //                       //    /
      //                       //   /
      //                       //  /
      //                       // /
      //                       ///
      //  -x////////////////////////////////////////+x
      //                      ///
      //                     / //
      //                    /  //
      //                   /   //
      //                  /    //
      //                 /     //
      //                /      //
      //               /       //
      //              +z       -y

      glm::vec3 top(0.0f, 0.0f, 0.0f);   //+y
      glm::vec3 bot(0.0f, 0.0f, 0.0f);   //-y
      glm::vec3 front(0.0f, 0.0f, 0.0f); //+z
      glm::vec3 rear(0.0f, 0.0f, 0.0f);  //-z
      glm::vec3 left(0.0f, 0.0f, 0.0f);  //-x
      glm::vec3 right(0.0f, 0.0f, 0.0f); //+x

      for (GLuint i = 0; i < this->mConnectedEntity->model->Meshes.size();
           i++)
      {
        for (GLuint j = 0;
             j < this->mConnectedEntity->model->Meshes.at(i).vertices.size();
             j++)
        {
          auto pos = this->mConnectedEntity->model->Meshes.at(i)
                         .vertices.at(j)
                         .position;
          if (pos.x > right.x)
            right = pos;
          if (pos.x < left.x)
            left = pos;
          if (pos.y > top.y)
            top = pos;
          if (pos.y < bot.y)
            bot = pos;
          if (pos.z > front.z)
            front = pos;
          if (pos.z < rear.z)
            rear = pos;
        }
      }

      this->mTopPos = top;
      this->mBotPos = bot;
      this->mFrontPos = front;
      this->mRearPos = rear;
      this->mLeftPos = left;
      this->mRightPos = right;
    }
    else
    {
      std::cout << "Entity has no model" << std::endl;
    }
  }
  else
  {
    std::cout << "No connected entity" << std::endl;
  }
  */
}
