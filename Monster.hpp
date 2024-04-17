#pragma once

#include <iostream>
#include "surface.h"
#include "template.h"
#include "AABBCollider.hpp"
#include "ProgressBar.hpp"
#include <vector>
#include "MonsterAI.hpp"
#include "ParticleExplosion.hpp"
#include "Animation.hpp"

class Tmpl8::Sprite;

class Monster
{
public:
	//constructor & destructor

	Monster(const char* fileName, unsigned int numFrames, int hunger = 0, int thirst = 0, int evoStage = 1, int cost = 0, int stomach = 0, int hydration = 0, int timeNeededForEvo = 0 , int worth = 0);

	~Monster();

	//Member data access
	float GetHunger() const;
	float GetThirst() const;
	int GetEvoStage() const;
	int GetCost() const;
	float GetStomach() const;
	float GetHydration() const;
	int GetNumFrames() const;
	float GetTimeSinceFood() const;
	float GetTimeSinceWater() const;
	Tmpl8::Sprite* GetSprite() const;
	const Tmpl8::vec2& GetPosition() const;
	const Tmpl8::vec2& GetNextPosition() const;
	Tmpl8::vec2 GetSize() const;
	const AABBCollider& GetCollider() const;
	const ProgressBar& GetFoodBar() const;
	const ProgressBar& GetWaterBar() const;
	MonsterAI GetMonsterAI() const;
	int GetNextTileIndex() const;
	int GetTileIndex();
	int GetWorth();

	void TimeSinceSpawn();

	void Dies();
	void UpdateParticles(float deltaTime);

	void SetTileIndex(int tileIndex);
	void SetTileIndex(Tmpl8::vec2 position);
	void SetNextTileIndex(int tileIndex);
	void SetNextPosition(const int tileIndex);

	void SetHunger(float newHunger);
	void SetThirst(float newThirst);

	void Hunger(float deltaTime);
	void Thirst(float deltaTime);

	void SetTimeSinceFood(float time);
	void SetTimeSinceWater(float time);

	void TimeSinceFood(float deltaTime);
	void TimeSinceWater(float deltaTime);

	void SetCollider(const AABBCollider collider);

	void Move(float deltaTime);

	void SetPosition(const Tmpl8::vec2& pos);
	void SetPosition(const int tileIndex);

	Tmpl8::vec2 CentrePosition() const;

	//void SetAlive(bool alive);
	 
	//Special Opperations
	void DieOfHunger(int stomach, int hunger);
	void DieOfThirst(int hydration, int thirst);
	void Evolution();
    void Draw(Tmpl8::Surface* screen) const;

private:
	//Data members
	float m_Hunger;
	float m_Thirst;
	int m_EvoStage = 1;
	int m_Cost;
	float m_Stomach;
	float m_Hydration;
	int m_Worth = 0;
	bool m_Alive = true;
	float m_TimeSinceFood = 0;
	float m_TimeSinceWater = 0;
	int m_NumFrames;
	int m_TimeSinceSpawn = 0;
	int m_TimeNeededForEvo;

	float m_Speed = 10.f;

	int m_TileIndex = 0;
	int m_NextTileIndex = 0;
	Tmpl8::vec2 m_NextPosition;

	 AABBCollider m_Collider;
	 ProgressBar m_FoodBar;
	 ProgressBar m_WaterBar;
	 MonsterAI m_MonsterAI;
	 ParticleProperties m_DieParticles
	 {
	 .velocity = { 0, 0},
	 .velocityVariation = {1000, 1000},

	 .colorBegin{255, 0, 0},
	 .colorEnd{0, 0, 0},

	 .sizeBegin = 4.0f,
	 .sizeEnd = 2.0f,
	 .SizeVariation = 0.5f,

	 .lifeTime = 1.0f,
	 };

	 ParticleProperties m_EvolveParticles
	 {
	 .velocity = { 0, 0},
	 .velocityVariation = {300,300},

	 .colorBegin{0, 255, 0},
	 .colorEnd{255, 255, 0},

	 .sizeBegin = 4.0f,
	 .sizeEnd = 2.0f,
	 .SizeVariation = 0.5f,

	 .lifeTime = 1.0f,
	 };
	 
	 ParticleExplosion m_ParticleExplosionEvo{ m_EvolveParticles };
	 ParticleExplosion m_ParticleExplosionDeath{m_DieParticles}; 

	Tmpl8::Sprite* m_pSprite = nullptr;

	


};









/*

int Monster::Evolution(int time, int hunger, int thirst)
{
	if ((time< 100) && (hunger == 0) && (thirst == 0))
	{
		if (GetEvoStage() < 3)
		{
			m_EvoStage++;
		}

		return m_EvoStage;
	}
}
*/



