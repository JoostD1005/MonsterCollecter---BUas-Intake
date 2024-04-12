#pragma once
#include <vector>
#include "template.h"

// took heavy inspo from this youtube video: https://www.youtube.com/watch?v=GK0jHlv3e3w


struct ParticleProperties
{
	Tmpl8::vec2 position;
	Tmpl8::vec2 velocity;
	Tmpl8::vec2 velocityVariation;

	Tmpl8::vec4 colorBegin;
	Tmpl8::vec4 colorEnd;

	float sizeBegin;
	float sizeEnd;
	float SizeVariation;

	float lifeTime = 1.0f;


};


class ParticleSystem
{
public:
	ParticleSystem();

	void Update(float deltaTime);
	
	void Emit(const ParticleProperties& particleProperties);

private:

	struct Particle
	{
		Tmpl8::vec2 position;
		Tmpl8::vec2 velocity;

		Tmpl8::vec4 colorBegin;
		Tmpl8::vec4 colorEnd;

		float Rotation = 1.0f;
		float sizeBegin;
		float sizeEnd;

		float lifeTime = 1.0f;
		float lifeRemaining = 0.0f;

		bool active = false;
	};

	std::vector<Particle> m_Particles;
	int m_ParticleIndex = 999;

};