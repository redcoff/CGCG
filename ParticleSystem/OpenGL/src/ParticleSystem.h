#pragma once
#include <glm.hpp>
#include <vector>

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	float life;

	Particle() : position(0.f), velocity(0.f), life(0.f) { }
};

namespace ParticleSystem
{
	std::vector<Particle> particles;
	void Emit();
	void Update();
	void Draw();
};

