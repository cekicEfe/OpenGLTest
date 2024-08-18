#ifndef TESTHITBOX_H
#define TESTHITBIX_H

#include <CoreClass/CoreClass.h>
#include <CoreClass/CoreEntity/CoreEntity.h>

namespace core
{
    class HitBox
    {
    private:
        CoreEntity *mConnectedEntity = nullptr;

        glm::vec3 mTopPos;
        glm::vec3 mBotPos ;
        glm::vec3 mFrontPos ;
        glm::vec3 mRearPos ;
        glm::vec3 mLeftPos ;
        glm::vec3 mRightPos ;

        void AttachEntity(CoreEntity* entity);
        void GenerateHitbox();

        friend class core::MainHandler;
        nlohmann::json SaveAsJson();
    };
}

#endif