#pragma once
#include "ParticleSystem.hpp"

class ParticleExplosion
{
public:
	ParticleExplosion() = default;
	ParticleExplosion(ParticleProperties particleProperties);

	void Explode(Tmpl8::vec2 explosionPos, float explosionDuration, float spawnRate);
	void Update(float deltaTime);
	void Draw(Tmpl8::Surface* screen) const;

private:
	ParticleSystem m_ParticleSystem;
	ParticleProperties m_ParticleProperties;

	Tmpl8::vec2 m_ExplosionPos = 0.0f;

	float m_ExplosionDuration = 0.0f;
	float m_CurrentDuration = 0.0f;

	float m_SpawnRate = 0.0f;
	float m_TimeTillNextSpawn = 0.0f;
};