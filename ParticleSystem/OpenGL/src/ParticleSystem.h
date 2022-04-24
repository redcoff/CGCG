#pragma once
#include <glm.hpp>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "Utils.h"

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	double lifetime;

	Particle() : position(0.f), velocity(0.05f), lifetime(0.f){}
	Particle(glm::vec3 position, glm::vec3 velocity, float lifetime):
		position(position), velocity(velocity), lifetime(lifetime) {}
};

class ParticleSystem
{
private:
	static std::vector<Particle> particles;
	static size_t pidx;
	static GLuint buffer;

public:
	static void Emit();
	static void Update(double);
	static void Draw(glm::mat4);
};


