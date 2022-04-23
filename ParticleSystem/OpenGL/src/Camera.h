#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#pragma once
class Camera
{
public:
	Camera():
		_direction(0.f, 0.f, 1.f),
		_origin(0.f, 0.f, 0.f),
		_up(0.f, 1.f, 0.f),
		_right(1.f, 0.f, 0.f),
		_projection(glm::perspective(glm::radians(70.f), 4.f/3.f, 0.1f, 1000.f)){}
	glm::mat4 GetViewProjection() const;
	void Rotate(const float, const float);
	glm::vec3 _direction;

private:
	glm::vec3 _origin;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::mat4 _projection;
};

