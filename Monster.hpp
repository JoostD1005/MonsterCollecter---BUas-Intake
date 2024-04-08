#pragma once

#include <iostream>
#include "surface.h"
#include "template.h"
#include "AABBCollider.hpp"
#include "ProgressBar.hpp"
#include <vector>
#include "MonsterAI.hpp"

class Tmpl8::Sprite;

class Monster
{
public:
	//constructor & destructor

	Monster(const char* fileName, unsigned int numFrames, int hunger = 0, int thirst = 0, int evoStage = 1, int cost = 0, int stomach = 0, int hydration = 0, int timeNeededForEvo = 0 , int worth = 0);
	//Monster(int hunger = 0, int thirst = 0, int evoStage = 1, int cost = 0, int stomach = 0, int hydration = 0, int worth = 0);

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
	Tmpl8::vec2 GetSize() const;
	const AABBCollider& GetCollider() const;
	const ProgressBar& GetFoodBar() const;
	const ProgressBar& GetWaterBar() const;
	int GetTileIndex() const;
	Tmpl8::vec2 GetTileIndexPos() const;

	int GetWorth();


	void TimeSinceSpawn();

	//monster AI
	void Move(std::vector<Monster*> monsters);
	bool IsTileOccupied(int tileIndex, std::vector<Monster*>& monsters);
	std::vector<int> findAvailableSpaces(int currentTileIndex, std::vector<Monster*>& monsters);

	void SetTileIndex(int tileIndex);

	void SetHunger(float newHunger);
	void SetThirst(float newThirst);

	void Hunger(float deltaTime);
	void Thirst(float deltaTime);

	void SetTimeSinceFood(float time);
	void SetTimeSinceWater(float time);

	void TimeSinceFood(float deltaTime);
	void TimeSinceWater(float deltaTime);


	void SetCollider(const AABBCollider collider);


	void SetPosition(const Tmpl8::vec2& pos);

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

	float m_TileIndex = 0;

	 AABBCollider m_Collider;
	 ProgressBar m_FoodBar;
	 ProgressBar m_WaterBar;

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



