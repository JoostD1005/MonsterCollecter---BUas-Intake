
#include "Monster.hpp"
#include "surface.h"
#include <iostream>

//Constructor.

Monster::Monster(const char* fileName, unsigned int numFrames, int hunger, int thirst, int evoStage, int cost, int stomach, int hydration, int worth) :
    m_Hunger(hunger),
    m_Thirst(thirst),
    m_EvoStage(evoStage),
    m_Cost(cost),
    m_Stomach(stomach),
    m_Hydration(hydration),
    m_Worth(worth),
    m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) },
    m_NumFrames(numFrames)
{

    m_Collider.SetSize(static_cast<float>( m_pSprite->GetWidth() ), static_cast<float>( m_pSprite->GetHeight() ) );

    m_FoodBar.SetColour(0x00ff00); // Green.
    m_WaterBar.SetColour(0x0000ff); // Blue.

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

int Monster::GetNumFrames() const
{
    return m_NumFrames;
}

int Monster::GetWorth()
{
    if (m_Worth > 0)
    {
        m_Worth = (m_Cost - m_Thirst - m_Hunger) * m_EvoStage;
        return m_Worth;
    }
    else
    {
        return 0;
    }
}

int Monster::GetTimeSinceFood() const
{
    return m_TimeSinceFood;
}

int Monster::GetTimeSinceWater() const
{
    return m_TimeSinceWater;
}

const Tmpl8::vec2& Monster::GetPosition() const
{
    return m_Collider.GetPosition();
}

Tmpl8::vec2 Monster::GetSize() const
{
    return { static_cast<float>(m_pSprite->GetWidth()), static_cast<float>(m_pSprite->GetHeight()) };
}

const AABBCollider& Monster::GetCollider() const
{
    return m_Collider;
}

const FoodWaterBar& Monster::GetFoodBar() const
{
    return m_FoodBar;
}

const FoodWaterBar& Monster::GetWaterBar() const
{
    return m_WaterBar;
}


Tmpl8::Sprite* Monster::GetSprite() const
{
    return m_pSprite;
}

//set datamembers.---------------------------------------------------------------------------

void Monster::Hunger()
{
    m_Hunger++;
    m_FoodBar.SetValue(static_cast<float>(m_Stomach - m_Hunger) / static_cast<float>(m_Stomach));
}

void Monster::Thirst()
{
    m_Thirst++;
    m_WaterBar.SetValue(static_cast<float>(m_Hydration - m_Thirst) / static_cast<float>(m_Hydration));

 //   float value = (m_Hydration - m_Thirst) / m_Hydration;
  //  m_WaterBar.SetValue(value);
}
void Monster::SetHunger(int newHunger)
{
    m_Hunger = newHunger;
}

void Monster::SetThirst(int newThirst)
{
    m_Thirst = newThirst;
}

void Monster::TimeSinceFood()
{
    m_TimeSinceFood++;
}

void Monster::TimeSinceWater()
{
    m_TimeSinceWater++;
}



void Monster::SetCollider(const AABBCollider collider)
{
    m_Collider = collider;
}

void Monster::SetPosition(const Tmpl8::vec2& pos)
{
    m_Collider.SetPosition(pos);

    // Center the food and water bars below the monster.
    auto c = Tmpl8::vec2{ pos.x + m_Collider.GetWidth() / 2.0f, pos.y + m_Collider.GetHeight() };

    m_WaterBar.SetPos({ c.x - m_WaterBar.GetWidth() / 2.0f, c.y + 5.0f });
    m_FoodBar.SetPos({ c.x - m_FoodBar.GetWidth() / 2.0f, c.y + 15.0f });
}

//void Monster::SetSprite(Tmpl8::Sprite* sprite)
//{
//    m_pSprite = sprite;
//}

Tmpl8::vec2 Monster::CentrePosition() const
{
    return GetPosition() + GetSize() * 0.5f;
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



void Monster::Draw(Tmpl8::Surface* screen) const
{
    if (m_pSprite != nullptr)
    {
        const auto pos = m_Collider.GetPosition();
        m_pSprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
        // screen->Box(m_Collider, 0xff0000);
    }

    m_FoodBar.Draw(screen);
    m_WaterBar.Draw(screen);
}





