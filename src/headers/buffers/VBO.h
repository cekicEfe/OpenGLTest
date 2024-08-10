#ifndef VBO_H
#define VBO_H

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include "model/Vertex.h"

class VBO
{
	private:
		GLuint id;
	public:
		VBO();
		void Bind();
		void Unbind();
		void Delete();
		void BufferData(std::vector <Model::Vertex> vertices);
		void BufferData(std::vector<glm::mat4> *Instances);
		void PointData(VERTEX_OFFSET offSetName);
};
 
#endif // !VBO_H
