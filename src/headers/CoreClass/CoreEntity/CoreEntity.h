#ifndef COREOBJECT_H
#define COREOBJECT_H

#include <CoreClass/CoreClassPreDec.h>
#include <json/json.hpp>
#include <glm/gtc/quaternion.hpp>
#include <model/Model.h>
#include <vector>
#include <memory>

namespace core
{
	class CoreEntity
	{
	public:
		CoreEntity();
	    virtual ~CoreEntity();
		virtual nlohmann::json saveAsJson();
		virtual void update(GLfloat deltaTime);

		Model::Model *mpModel = nullptr;
		glm::vec3 mModelScale = glm::vec3(1.0f);

		glm::vec3 mPos = glm::vec3(0.0f);

		glm::vec3 mRotAxis = glm::vec3(1.0f,0.0f,0.0f);
		GLfloat mRotDegreeRad = 0;

		friend class core::MainHandler;
		friend class core::RenderHandler;
	};
}
#endif // !SCRIPTOBJECT
