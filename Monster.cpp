
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
    m_Worth(cost),
    m_TimeNeededForEvo(timeNeededForEvo),
    m_pSprite{ new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames) },
    m_NumFrames(numFrames)
{

    m_Collider.SetSize(static_cast<float>( m_pSprite->GetWidth() ), static_cast<float>( m_pSprite->GetHeight() ) );

    m_NextPosition = GetPosition();

    m_FoodBar.SetColour(0x00ff00); // Green.
    m_WaterBar.SetColour(0x0000ff); // Blue.

    std::cout << "new Monster Created!\n" << m_Hunger << "\n" << m_Thirst << "\n" << m_EvoStage << "\n" << m_Cost << "\n" << m_Stomach << "\n" << m_Hydration << "\n";
}

//destructor. deletes all the pointers of the class
Monster::~Monster()
{
    delete m_pSprite;
    m_pSprite = nullptr;

    delete m_pMovingSprite;
    m_pMovingSprite = nullptr;

    m_pTempSprite = nullptr;

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

const Tmpl8::vec2& Monster::GetNextPosition() const
{
    return m_NextPosition;
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

int Monster::GetNextTileIndex() const
{
    return m_NextTileIndex;
}

int Monster::GetTileIndex()
{
    int row = GetPosition().y / 50;
    int col = GetPosition().x / 50;

    m_TileIndex = row * 16 + col;
    return m_TileIndex;
}


Tmpl8::Sprite* Monster::GetSprite() const
{
    return m_pSprite;
}


Tmpl8::vec2 Monster::CentrePosition() const
{
    return GetPosition() + GetSize() * 0.5f;
}

//set datamembers.---------------------------------------------------------------------------

void Monster::SetTileIndex(int tileIndex)
{
    m_TileIndex = tileIndex;
}

void Monster::SetNextTileIndex(int tileIndex)
{
    m_NextTileIndex = tileIndex;
    SetNextPosition(tileIndex);
}

void Monster::SetTileIndex(Tmpl8::vec2 position)
{
    int row = position.y / 50;
    int col = position.x / 50;

    m_TileIndex = row * 16 + col;
}

void Monster::SetNextPosition(const int tileIndex)
{
    int row = (tileIndex) / 16;
    int col = (tileIndex) % 16;
    float x = col * 50;
    float y = row * 50;
    
    m_NextPosition = { x, y };
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

void Monster::SetCollider(const AABBCollider collider)
{
    m_Collider = collider;
}

void Monster::SetMovingAnimation(const char* fileName, unsigned int numFrames)
{
    m_pMovingSprite = new Tmpl8::Sprite(new Tmpl8::Surface(fileName), numFrames);
}

void Monster::SetMovingAnimFrames(int numFrames)
{
    m_NumMovingFrames = numFrames;
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
    int col = (tileIndex) % 16;
    int row = (tileIndex) / 16;
    float x = col * 50;
    float y = row * 50;
    std::cout << "nextTileIndex: " << tileIndex << "x: " << x << "y: " << y << "\n";

    m_Collider.SetPosition({ x, y });

    // Center the food and water bars below the monster.
    auto c = Tmpl8::vec2{ x + m_Collider.GetWidth() / 2.0f, y + m_Collider.GetHeight() };

    m_WaterBar.SetPos({ c.x - m_WaterBar.GetWidth() / 2.0f, c.y + 5.0f });
    m_FoodBar.SetPos({ c.x - m_FoodBar.GetWidth() / 2.0f, c.y + 15.0f });
}

//time Related functions.----------------------------------------------------------------------

void Monster::TimeSinceSpawn()
{
    m_TimeSinceSpawn++;
}

void Monster::Hunger(float deltaTime)
{
    SetHunger(m_Hunger + deltaTime);
}

void Monster::Thirst(float deltaTime)
{
    SetThirst(m_Thirst + deltaTime);
       
}

void Monster::TimeSinceFood(float deltaTime)
{
    m_TimeSinceFood = m_TimeSinceFood + deltaTime;
}

void Monster::TimeSinceWater(float deltaTime)
{
    m_TimeSinceWater = m_TimeSinceWater + deltaTime;
}

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


//moving of the monster.
void Monster::Move(float deltaTime)
{
    SetState(AnimState::Moving);

    Tmpl8::vec2 currentPos = GetPosition();

    Tmpl8::vec2 direction = { m_NextPosition.x - currentPos.x , m_NextPosition.y - currentPos.y };
    float directionLength = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (directionLength > 0.01f)
    {
        // Normalize direction to maintain constant speed
        direction = { direction.x / directionLength, direction.y / directionLength };
        Tmpl8::vec2 velocity = direction * m_Speed * deltaTime;
        currentPos += velocity;
    }
    SetPosition(currentPos);

    if (abs(currentPos.x - m_NextPosition.x) < 2.0f && abs(currentPos.y - m_NextPosition.y) < 2.0f) // snaps the position to the next position on the tile map if it is in range.
    {
        SetPosition(m_NextPosition);
    }

}

//animation stuff.
void Monster::UpdateParticles(float deltaTime)
{
    m_ParticleExplosionDeath.Update(deltaTime);
    m_ParticleExplosionEvo.Update(deltaTime);
}

void Monster::SetState(const AnimState& state)
{
    switch (state)
    {
    case AnimState::Idle:
        m_pTempSprite = m_pSprite;
        m_NumTempFrames = m_NumFrames;
        break;
    case AnimState::Moving:
        m_pTempSprite = m_pMovingSprite;
        m_NumTempFrames = m_NumMovingFrames;
        break;

    }
}

void Monster::DoAnimation(float deltaTime)
{
    if (m_pTempSprite == nullptr){ return; }

    int frame = m_pTempSprite->GetFrame();
    if (frame == m_NumTempFrames - 1)
    {
        m_pTempSprite->SetFrame(0);
    }
    if (frame < m_NumTempFrames - 1)
    {
        m_pTempSprite->SetFrame(frame + 1);
    }
}




//---------------------------------------------------------------------------------------------------------

//drawing
void Monster::Draw(Tmpl8::Surface* screen) const
{
    if (m_pTempSprite != nullptr)
    {
        const auto pos = m_Collider.GetPosition();
        m_pTempSprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
    }

    m_FoodBar.Draw(screen);
    m_WaterBar.Draw(screen);
    m_ParticleExplosionDeath.Draw(screen);
    m_ParticleExplosionEvo.Draw(screen);
}





