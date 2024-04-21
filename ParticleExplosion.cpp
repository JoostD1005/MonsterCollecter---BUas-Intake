#include "ParticleExplosion.hpp"

ParticleExplosion::ParticleExplosion(ParticleProperties particleProperties) : //sets the member variable to the particleProperties
	m_ParticleProperties{particleProperties}
{

}

void ParticleExplosion::Explode(Tmpl8::vec2 explosionPos, float explosionDuration, float spawnRate) // sets the parameters
{
	m_ExplosionPos = explosionPos;
	m_ExplosionDuration = explosionDuration;
	m_CurrentDuration = explosionDuration;
	m_SpawnRate = spawnRate;
	m_TimeTillNextSpawn = 0;
}

void ParticleExplosion::Update(float deltaTime)
{
	if (m_CurrentDuration > 0) //spawns a particle every timetillnextspawn until the duration stops.
	{
		m_CurrentDuration -= deltaTime;
		m_TimeTillNextSpawn -= deltaTime;

		if (m_TimeTillNextSpawn <= 0.0f)
		{
			m_TimeTillNextSpawn = m_SpawnRate;
			m_ParticleSystem.Emit(m_ParticleProperties, m_ExplosionPos);
		}
	}

	m_ParticleSystem.Update(deltaTime);
}

void ParticleExplosion::Draw(Tmpl8::Surface* screen) const
{
	m_ParticleSystem.Draw(screen);
}



