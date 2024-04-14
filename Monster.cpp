
#include "Monster.hpp"
#include "surface.h"
#include <iostream>
#include <random>

//Constructor.

Monster::Monster(const char* fileName, unsigned int numFrames, int hunger, int thirst, int evoStage, int cost, int stomach, int hydration, int timeNeededForEvo, int worth) :
    m_Hunger(hunger),
    m_Thirst(thirst),
    m_EvoStage(evoStage),
    m_Cost(cost),
    m_Stomach(stomach),
    m_Hydration(hydration),
    m_Worth(worth),
    m_TimeNeededForEvo(timeNeededForEvo),
    m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) },
    m_NumFrames(numFrames)
{

    m_Collider.SetSize(static_cast<float>( m_pSprite->GetWidth() ), static_cast<float>( m_pSprite->GetHeight() ) );

    m_FoodBar.SetColour(0x00ff00); // Green.
    m_WaterBar.SetColour(0x0000ff); // Blue.

    std::cout << "new Monster Created!\n" << m_Hunger << "\n" << m_Thirst << "\n" << m_EvoStage << "\n" << m_Cost << "\n" << m_Stomach << "\n" << m_Hydration << "\n";
}


Monster::~Monster()
{
    delete m_pSprite;
    m_pSprite = 0;

}

//Get components to access private data members.
float Monster::GetHunger() const
{
    return m_Hunger;
}

float Monster::GetThirst() const
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

float Monster::GetStomach() const
{
    return m_Stomach;
}

float Monster::GetHydration() const
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
        m_Worth = roundf(m_Cost - (m_Thirst  + m_Hunger) * 0.5f) * m_EvoStage;
        return m_Worth;
    }
    else
    {
        return 0;
    }
}

float Monster::GetTimeSinceFood() const
{
    return m_TimeSinceFood;
}

float Monster::GetTimeSinceWater() const
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

const ProgressBar& Monster::GetFoodBar() const
{
    return m_FoodBar;
}

const ProgressBar& Monster::GetWaterBar() const
{
    return m_WaterBar;
}

MonsterAI Monster::GetMonsterAI() const
{
    return m_MonsterAI;
}

int Monster::GetTileIndex()
{
    int row = GetPosition().y / 50;
    int col = GetPosition().x / 50;

    m_TileIndex = row * 16 + col + 1;
    return m_TileIndex;
}


Tmpl8::Sprite* Monster::GetSprite() const
{
    return m_pSprite;
}

//set datamembers.---------------------------------------------------------------------------
void Monster::TimeSinceSpawn()
{
    m_TimeSinceSpawn++;
}


void Monster::SetTileIndex(int tileIndex)
{
    m_TileIndex = tileIndex;
}

void Monster::Hunger(float deltaTime)
{
    SetHunger(m_Hunger + deltaTime);
}

void Monster::Thirst(float deltaTime)
{
    SetThirst(m_Thirst + deltaTime);
       
}
void Monster::SetHunger(float newHunger)
{
    m_Hunger = newHunger;
    m_FoodBar.SetValue((m_Stomach - m_Hunger) / m_Stomach);
}

void Monster::SetThirst(float newThirst)
{
    m_Thirst = newThirst;
    m_WaterBar.SetValue((m_Hydration - m_Thirst) / m_Hydration);
}

void Monster::SetTimeSinceFood(float time)
{
    m_TimeSinceFood = time;
}

void Monster::SetTimeSinceWater(float time)
{
    m_TimeSinceWater = time;
}

void Monster::TimeSinceFood(float deltaTime)
{
    m_TimeSinceFood = m_TimeSinceFood + deltaTime;
}

void Monster::TimeSinceWater(float deltaTime)
{
    m_TimeSinceWater = m_TimeSinceWater + deltaTime;
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

void Monster::SetPosition(const int tileIndex)
{
    int row = (tileIndex - 1) / 16;
    int col = (tileIndex - 1) % 16;
    float x = col * 50;
    float y = row * 50;
    std::cout << "nextTileIndex: " << tileIndex << "x: " << x << "y: " << y << "\n";

    m_Collider.SetPosition({ x, y });

    // Center the food and water bars below the monster.
    auto c = Tmpl8::vec2{ x + m_Collider.GetWidth() / 2.0f, y + m_Collider.GetHeight() };

    m_WaterBar.SetPos({ c.x - m_WaterBar.GetWidth() / 2.0f, c.y + 5.0f });
    m_FoodBar.SetPos({ c.x - m_FoodBar.GetWidth() / 2.0f, c.y + 15.0f });
}


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

void Monster::Evolution()
{
    if (m_TimeSinceSpawn > m_TimeNeededForEvo && m_Hunger == 0 && m_Thirst == 0 && m_EvoStage < 2) 
    {
        m_EvoStage++;
        m_TimeNeededForEvo =  m_TimeNeededForEvo * 3;
        m_ParticleExplosionEvo.Explode(CentrePosition(), 0.2f, 0.01f);
    }
    if (m_TimeSinceSpawn > m_TimeNeededForEvo && m_Hunger == 0 && m_Thirst == 0 && m_EvoStage < 3)
    {
        m_EvoStage++;
        m_ParticleExplosionEvo.Explode(CentrePosition(), 0.2f, 0.01f);
    }
}

void Monster::Dies()
{
    if (m_Alive)
    {
        m_ParticleExplosionDeath.Explode(CentrePosition(), 0.2f, 0.01f);
    }
    m_Alive = false;
}

void Monster::UpdateParticles(float deltaTime)
{
    m_ParticleExplosionDeath.Update(deltaTime);
    m_ParticleExplosionEvo.Update(deltaTime);
}



//---------------------------------------------------------------------------------------------------------


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
    m_ParticleExplosionDeath.Draw(screen);
    m_ParticleExplosionEvo.Draw(screen);
}





