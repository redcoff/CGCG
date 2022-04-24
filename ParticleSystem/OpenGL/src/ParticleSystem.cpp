#include "ParticleSystem.h"

#include "Random.h"

std::vector<Particle> ParticleSystem::particles(400);
size_t ParticleSystem::pidx = 0;

void ParticleSystem::Emit()
{
	glm::vec3 pos(Random::Float(), 0.f, Random::Float());
	particles[pidx] = { pos, glm::vec3(0.f, 1.f, 0.f), 1200. };
	pidx = (pidx + 1) % 400;
}

void ParticleSystem::Update(double deltaTime)
{
	for (size_t i = 0; i < particles.size(); ++i)
	{
		Particle& particle = particles[i];
		if (particle.lifetime <= 0.) continue;

		particle.position += particle.velocity;
		particle.lifetime -= deltaTime * 1000.;
	}
}

void ParticleSystem::Draw()
{

}
