#include "HitBox.h"

void core::HitBox::AttachEntity(CoreEntity *entity)
{
    this->mConnectedEntity = entity;
}

//Generates a Hitbox by sort throughghhg nodes which kind of sucks
void core::HitBox::GenerateHitbox()
{
    if (this->mConnectedEntity != nullptr)
    {
        if (this->mConnectedEntity->mpModel != nullptr)
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

            for (GLuint i = 0; i < this->mConnectedEntity->mpModel->Meshes.size(); i++)
            {
                for (GLuint j = 0; j < this->mConnectedEntity->mpModel->Meshes.at(i).vertices.size(); j++)
                {
                    auto pos = this->mConnectedEntity->mpModel->Meshes.at(i).vertices.at(j).position;
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
}

nlohmann::json core::HitBox::SaveAsJson()
{
    nlohmann::json newJson;

    newJson["Bound Entity ID"] = std::to_string((int)this->mConnectedEntity); // Sucks so bad :(
    if (this->mConnectedEntity != nullptr)
    {
        newJson["Top  "] = {this->mTopPos.x, this->mTopPos.y, this->mTopPos.z};
        newJson["Bot  "] = {this->mBotPos.x, this->mBotPos.y, this->mBotPos.z};
        newJson["Front"] = {this->mFrontPos.x, this->mFrontPos.y, this->mFrontPos.z};
        newJson["Rear "] = {this->mRearPos.x, this->mRearPos.y, this->mRearPos.z};
        newJson["Left "] = {this->mLeftPos.x, this->mLeftPos.y, this->mLeftPos.z};
        newJson["Right"] = {this->mRightPos.x, this->mRightPos.y, this->mRightPos.z};
    }
}