#define GLM_FORCE_SWIZZLE
#include "Camera.h"

glm::mat4 Camera::GetViewProjection() const
{
	const glm::mat4 view = glm::lookAt(_direction * 1.4f, _origin, _up);
	return _projection * view;
}


void Camera::Rotate(const float angleX, const float angleY)
{
	auto matrix = glm::identity<glm::mat4>();
	matrix = glm::rotate(matrix, angleX, _up);
	matrix = glm::rotate(matrix, angleY, _right);

	_direction = glm::vec4(_direction, 1.f) * matrix;
	_right = glm::vec4(_right, 1.f) * matrix;
}



