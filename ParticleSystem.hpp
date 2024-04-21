#pragma once
#include <vector>
#include "template.h"
#include "surface.h"

// took heavy inspo from this youtube video: https://www.youtube.com/watch?v=GK0jHlv3e3w
// also, Kuroxy from the 3DGep discord helped me a ton, so some thing may overlap with his system.


struct ParticleProperties //sets the properties of the particles, so that i can use different types of particles.
{
	Tmpl8::vec2 velocity = 0;
	Tmpl8::vec2 velocityVariation = 0;

	Tmpl8::vec3 colorBegin = 0;
	Tmpl8::vec3 colorEnd = 0;

	float sizeBegin = 0;
	float sizeEnd = 0;
	float SizeVariation = 0;

	float lifeTime = 1.0f;


};


class ParticleSystem
{
public:
	ParticleSystem();

	void Update(float deltaTime);
	
	void Emit(const ParticleProperties& particleProperties, const Tmpl8::vec2& position);

	void Draw(Tmpl8::Surface* screen) const;

private:

	struct Particle //default particle, all the variables are set with the ParticleProperties.
	{
		Tmpl8::vec2 Position;
		Tmpl8::vec2 Velocity;

		Tmpl8::Pixel Color;
		Tmpl8::vec3 ColorBegin;
		Tmpl8::vec3 ColorEnd;

		float SizeBegin;
		float SizeEnd;
		float CurrentSize;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};

	std::vector<Particle> m_Particles; //all the particles 

};