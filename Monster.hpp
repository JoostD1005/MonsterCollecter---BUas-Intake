#pragma once

#include <iostream>
#include "surface.h"
#include "template.h"
#include "AABBCollider.hpp"
#include "ProgressBar.hpp"
#include <vector>
#include "MonsterAI.hpp"
#include "ParticleExplosion.hpp"

class Tmpl8::Sprite;

enum class AnimState // to change between animations.
{
	Idle,
	Moving,
};

class Monster
{
public:
	//constructor & destructor
	Monster(const char* fileName, unsigned int numFrames, int hunger = 0, int thirst = 0, int evoStage = 1, int cost = 0, int stomach = 0, int hydration = 0, int timeNeededForEvo = 0 , int worth = 0);

	~Monster();

	//access to the basics of the monster.
	float GetHunger() const;
	float GetThirst() const;
	int GetEvoStage() const;
	int GetCost() const;
	float GetStomach() const;
	float GetHydration() const;
	float GetTimeSinceFood() const;
	float GetTimeSinceWater() const;

	// access to sprite stuff.
	Tmpl8::Sprite* GetSprite() const;
	int GetNumFrames() const;

	//position related access
	const Tmpl8::vec2& GetPosition() const;
	const Tmpl8::vec2& GetNextPosition() const;
	Tmpl8::vec2 CentrePosition() const;
	Tmpl8::vec2 GetSize() const;

	//collider
	const AABBCollider& GetCollider() const;

	// progress bars
	const ProgressBar& GetFoodBar() const;
	const ProgressBar& GetWaterBar() const;

	//moving access
	MonsterAI GetMonsterAI() const;
	int GetNextTileIndex() const;
	int GetTileIndex();

	//worth
	int GetWorth();

	void TimeSinceSpawn();

	void UpdateParticles(float deltaTime);

	// animation logic
	void SetState(const AnimState& state);
	void DoAnimation(float deltaTime);

	void SetMovingAnimation(const char* fileName, unsigned int numFrames);
	void SetMovingAnimFrames(int numFrames);

	// moving logic and setting of variables needed for moving
	void Move(float deltaTime);
	void SetTileIndex(int tileIndex);
	void SetTileIndex(Tmpl8::vec2 position);
	void SetNextTileIndex(int tileIndex);
	void SetNextPosition(const int tileIndex);
	void SetPosition(const Tmpl8::vec2& pos);
	void SetPosition(const int tileIndex);


	// depleading progress Bars logic & what happens when empty
	void SetHunger(float newHunger);
	void SetThirst(float newThirst);
	void Hunger(float deltaTime);
	void Thirst(float deltaTime);
	void SetTimeSinceFood(float time);
	void SetTimeSinceWater(float time);
	void TimeSinceFood(float deltaTime);
	void TimeSinceWater(float deltaTime);
	void Dies();

	//set collider height and width of the monster sprite.
	void SetCollider(const AABBCollider collider);

	//set new evo stage.
	void Evolution();

	//drawing the sprite to the screen.
    void Draw(Tmpl8::Surface* screen) const;

private:
	//Data members
	float m_Hunger;
	float m_Thirst;
	float m_Stomach;
	float m_Hydration;
	float m_TimeSinceFood = 0;
	float m_TimeSinceWater = 0;
	int m_EvoStage = 1;
	int m_Cost;
	int m_Worth = 0;
	int m_TimeSinceSpawn = 0;
	int m_TimeNeededForEvo;
	bool m_Alive = true;


	float m_Speed = 50.f; // in pixels per second

	//position on the screen
	int m_TileIndex = 0;
	int m_NextTileIndex = 0;
	Tmpl8::vec2 m_NextPosition;

	//member classes
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

	 //sprites
	Tmpl8::Sprite* m_pSprite = nullptr;
	Tmpl8::Sprite* m_pMovingSprite = nullptr;
	Tmpl8::Sprite* m_pTempSprite = nullptr;

	// number of frames for each sprite.
	int m_NumFrames;
	int m_NumMovingFrames = 0;
	int m_NumTempFrames = 0;


};
