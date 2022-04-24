#include "ParticleSystem.h"

#include <ext/matrix_transform.hpp>
#include <GL/glew.h>
#include <gtc/type_ptr.hpp>

#include "Random.h"

std::vector<Particle> ParticleSystem::particles(400);
size_t ParticleSystem::pidx = 0;
GLuint ParticleSystem::buffer = 0;

void ParticleSystem::Emit()
{
	for (size_t i = 0; i < particles.capacity(); i++) {
		glm::vec3 vel(Random::Float(), Random::Float(), Random::Float());
		vel = glm::normalize(vel) * 0.05f;
		glm::vec3 pos(Random::Float(), Random::Float(), Random::Float());
		particles[i] = { pos, vel, 1200. };
		//pidx = (pidx + 1) % 400;
	}

	/*glm::vec3 pos(0.5f, 0.f, 0.f);
	particles[0] = { pos, glm::vec3(0.f, 1.f, 0.f), 1200. };

	glm::vec3 pos2(0.5f, 1.f, 0.f);
	particles[1] = { pos2, glm::vec3(0.f, 1.f, 0.f), 1200. };*/


}

void ParticleSystem::Update(double deltaTime)
{
	for (size_t i = 0; i < particles.size(); ++i)
	{
		Particle& particle = particles[i];
		if (particle.lifetime <= 0.) continue;

		particle.position += particle.velocity * (float)deltaTime;
		//particle.lifetime -= deltaTime * 1000.;
	}
}

void ParticleSystem::Draw(glm::mat4 world)
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, 5 * sizeof(float), positions, GL_STATIC_DRAW);

	for (Particle particle : particles)
	{
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		//if (particle.lifetime > 0.0)
		//{
			float myBuffer[3] = {particle.position.x, particle.position.y, particle.position.z };

			glEnableVertexAttribArray(0);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), myBuffer, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
			glDrawArrays(GL_POINTS, 0, 1);
			glGetError();
			/*auto transformation = glm::translate(world, particle.position);
			glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(glm::mat4(transformation)));

			glDrawArrays(GL_TRIANGLES, 0, 3);*/


		//}
	}
}
