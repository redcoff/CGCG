#pragma once
#include "glm/mat4x4.hpp"

class Camera
{
public:
	glm::vec3 Position;


	Camera();
	void Move();


protected:
	glm::mat4x4 _worldToView;
	glm::mat4x4 _viewToWorld;
	glm::mat4x4 _projection;
};

