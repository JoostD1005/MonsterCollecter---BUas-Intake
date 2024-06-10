#include "ParticleSystem.hpp"
#include <random>

ParticleSystem::ParticleSystem()
{
	m_Particles.resize(100); // sets the vector to 100
}

void ParticleSystem::Update(float deltaTime)
{
	for (auto& particle : m_Particles)
	{
		if (!particle.Active)
		{
			continue;
		}

		if (particle.LifeRemaining <= 0.0f) // checks if the particle should die
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= deltaTime;
		particle.Position += particle.Velocity * deltaTime;

		float lifeTimePercentage = (particle.LifeTime - particle.LifeRemaining) / particle.LifeTime;


		particle.CurrentSize = (particle.SizeEnd - particle.SizeBegin) * lifeTimePercentage + particle.SizeBegin; // sets the size of the particle

		int r = (particle.ColorEnd.x - particle.ColorBegin.x) * lifeTimePercentage + particle.ColorBegin.x;

		int g = (particle.ColorEnd.y - particle.ColorBegin.y) * lifeTimePercentage + particle.ColorBegin.y;

		int b = (particle.ColorEnd.z - particle.ColorBegin.z) * lifeTimePercentage + particle.ColorBegin.z;

		particle.Color = (r << 16) | (g << 8) | b;  // sets the color of the particle
	}

	std::sort(m_Particles.begin(), m_Particles.end(), [](const Particle& lhs, const Particle& rhs) // sorts the vector from oldest to youngest, so that the oldest is drawn first -- (lefthandside, righthandside)
		{
			return lhs.LifeRemaining < rhs.LifeRemaining;
		});
}

void ParticleSystem::Emit(const ParticleProperties& particleProperties, const Tmpl8::vec2& position) // set all the partical variables to the particleProperties
{
	if (m_Particles.front().Active)
	{
		return;
	}

	Particle& particle = m_Particles.front();
	particle.Active = true;
	particle.Position = position;

	//velocity
	particle.Velocity = particleProperties.velocity;
	particle.Velocity.x += Rand(particleProperties.velocityVariation.x * 2) - particleProperties.velocityVariation.x ; // randomise the velocity
	particle.Velocity.y += Rand(particleProperties.velocityVariation.y * 2) - particleProperties.velocityVariation.y ; // randomise the velocity

	//color
	particle.ColorBegin = particleProperties.colorBegin;
	particle.ColorEnd = particleProperties.colorEnd;

	particle.LifeTime = particleProperties.lifeTime;
	particle.LifeRemaining = particleProperties.lifeTime;
	particle.SizeBegin = particleProperties.sizeBegin + Rand(particleProperties.SizeVariation * 2) - particleProperties.SizeVariation;
	particle.SizeEnd = particleProperties.sizeEnd;

	std::sort(m_Particles.begin(), m_Particles.end(), [](const Particle& lhs, const Particle& rhs) // sorts the vector
		{
			return lhs.LifeRemaining < rhs.LifeRemaining;
		});
}

void ParticleSystem::Draw(Tmpl8::Surface* screen) const // draws a circle for every particle
{
	for (auto& particle : m_Particles)
	{
		if (particle.Active)
		{
			screen->Circle(particle.Position.x, particle.Position.y, particle.CurrentSize, particle.Color);
		}
	}
}

