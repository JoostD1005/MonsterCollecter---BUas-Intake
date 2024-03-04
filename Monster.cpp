
#include "Monster.hpp"
#include "surface.h"



//Constructor.

Monster::Monster(const char* fileName, unsigned int numFrames, int hunger, int thirst, int evoStage, int cost, int stomach, int hydration, int worth) :
	m_Hunger(hunger),
	m_Thirst(thirst),
	m_EvoStage(evoStage),
	m_Cost(cost),
	m_Stomach(stomach),
	m_Hydration(hydration),
	m_Worth(worth),
	m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) }
{

	m_Collider.SetSize(m_pSprite->GetWidth(), m_pSprite->GetHeight());
	m_FoodBar.SetPos(GetFoodBarPos());
	m_WaterBar.SetPos(GetWaterBarPos());
	
	std::cout << "new Monster Created!\n" << m_Hunger << "\n" << m_Thirst << "\n" << m_EvoStage << "\n" << m_Cost << "\n" << m_Stomach << "\n" << m_Hydration << "\n";
	std::cout << m_Position.x << ", " << m_Position.y << "\n";
}


Monster::~Monster()
{
	delete m_pSprite;
	m_pSprite = 0;

}

//Get components to access private data members.
int Monster::GetHunger() const
{
	return m_Hunger;
}

int Monster::GetThirst() const
{
	return m_Thirst;
}

int Monster::GetEvoStage() const
{
	return m_EvoStage;
}

int Monster::GetCost() const
{
	return m_Cost;
}

int Monster::GetStomach() const
{
	return m_Stomach;
}

int Monster::GetHydration() const
{
	return m_Hydration;
}

int Monster::GetWorth() const
{
	return m_Worth;
}



const Tmpl8::vec2& Monster::GetPosition() const
{
	return m_Collider.GetPosition();
}



AABBCollider Monster::GetCollider() const
{
	return m_Collider;
}

FoodWaterBar Monster::GetFoodBar() const
{
	return m_FoodBar;
}

FoodWaterBar Monster::GetWaterBar() const
{
	return m_WaterBar;
}

Tmpl8::vec2 Monster::GetFoodBarPos() const
{

	float monsterX =GetCollider().GetPosition().x;
	float monsterY =GetCollider().GetPosition().y;

	float monsterHeight =GetCollider().GetHeight();

	float monsterCentre =CentrePosition().x;
	float barCentre = m_FoodBar.GetSprite()->GetWidth() / 2;

	float barX = monsterCentre - barCentre;
	float barY = monsterY + monsterHeight + 5.0f;

	return {barX,barY};
}

Tmpl8::vec2 Monster::GetWaterBarPos() const
{
	float foodBarY = GetFoodBarPos().y;

	float waterBarX = GetFoodBarPos().x;;
	float waterBarY = foodBarY + m_FoodBar.GetSprite()->GetHeight() + 3.0f;

	return {waterBarX, waterBarY};
}



Tmpl8::Sprite* Monster::GetSprite() const
{
	return m_pSprite;
}

//set datamembers.---------------------------------------------------------------------------

void Monster::Hunger()
{
	m_Hunger++;
}

void Monster::Thirst()
{
	m_Thirst++;
}



void Monster::SetCollider(const AABBCollider collider)
{
	m_Collider = collider;
}

void Monster::SetPosition(const Tmpl8::vec2& pos)
{
	m_Collider.SetPosition(pos);
}


void Monster::SetSprite(Tmpl8::Sprite* sprite)
{
	m_pSprite = sprite;
}




Tmpl8::vec2 Monster::CentrePosition() const
{
	Tmpl8::vec2 centrePos{ GetPosition().x + (GetSprite()->GetWidth() / 2), GetPosition().y + (GetSprite()->GetHeight() / 2) };

	return centrePos;
}



//Special opperations definitions
void Monster::DieOfHunger(int stomach, int hunger)
{
	if (hunger >= stomach)
	{
		m_Alive = false;
	}
}

void Monster::DieOfThirst(int hydration, int thirst)
{
	if (thirst >= hydration)
	{
		m_Alive = false;
	}
}

 int Monster::Worth()
{
	int worth = m_Worth;
	worth = ((m_Stomach - m_Hunger) + (m_Hydration - m_Thirst) + m_Cost) * m_EvoStage;
	return worth;
}





