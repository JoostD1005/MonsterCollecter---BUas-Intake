#pragma once

#include <iostream>
#include "surface.h"
#include "template.h"
#include "AABBCollider.hpp"
#include "FoodWaterBar.hpp"

class Tmpl8::Sprite;

class Monster
{
public:
	//constructor & destructor

	Monster(const char* fileName, unsigned int numFrames, int hunger = 0, int thirst = 0, int evoStage = 1, int cost = 0, int stomach = 0, int hydration = 0, int worth = 0);
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
	const FoodWaterBar& GetFoodBar() const;
	const FoodWaterBar& GetWaterBar() const;

	int GetWorth();

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
	int Evolution(int time, int hunger, int thirst);
    void Draw(Tmpl8::Surface* screen) const;

private:
	//Data members
	float m_Hunger;
	float m_Thirst;
	int m_EvoStage;
	int m_Cost;
	float m_Stomach;
	float m_Hydration;
	int m_Worth = 0;
	bool m_Alive = true;
	float m_TimeSinceFood = 0;
	float m_TimeSinceWater = 0;
	int m_NumFrames;

	 AABBCollider m_Collider;
	 FoodWaterBar m_FoodBar;
	 FoodWaterBar m_WaterBar;


	Tmpl8::vec2 m_Position;

	

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



