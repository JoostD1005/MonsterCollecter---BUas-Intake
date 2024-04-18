#include "MonsterAI.hpp"
#include "Monster.hpp"
#include <random>



void MonsterAI::NextTile(std::vector<Monster*>& monsters, Monster* monster)
{
    int currentTileIndex = monster->GetTileIndex();
    std::vector<int> availableSpaces = findAvailableSpaces(currentTileIndex, monsters);

    std::cout << "currentTileIndex: " << currentTileIndex << " x: " << monster->GetPosition().x << " y: " << monster->GetPosition().y << "\n";

    if (availableSpaces.empty())
    {
        std::cout << "cannot move this monster: " << this << "\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution goingToMove(0.5f);

    int randomIndex = std::uniform_int_distribution<int>(0, availableSpaces.size() - 1)(gen);

    if (goingToMove(gen))
    {
        int newTileIndex = availableSpaces[randomIndex];
        if (newTileIndex > 0 && newTileIndex < 127)
        {
            monster->SetNextTileIndex(newTileIndex);
        }
    }
 
}

bool MonsterAI::IsTileOccupied(int tileIndex, std::vector<Monster*>& monsters)
{
    for (Monster* monster : monsters)
    {
        if (monster->GetTileIndex() == tileIndex && monster->GetNextTileIndex() ==tileIndex)
        {
            return true;
        }
    }

    return false;
}

std::vector<int> MonsterAI::findAvailableSpaces(int currentTileIndex, std::vector<Monster*>& monsters)
{

    std::vector<std::pair<int, int>> ranges = {
        {0, 14}, {16, 30}, {32, 46}, {48, 62},
        {64, 78}, {80, 94}, {96, 110}, {112, 126}
    };

    for(auto& range : ranges)
        if (currentTileIndex >= range.first && currentTileIndex <= range.second)
        {
            std::cout << "Current Range: " << range.first << " - " << range.second << std::endl;
            // Check left tile
            if (!IsTileOccupied(currentTileIndex - 1, monsters) && (currentTileIndex - 1) >= range.first)
            {
                availableSpaces.push_back(currentTileIndex - 1);
            }
            // Check right tile
            if (!IsTileOccupied(currentTileIndex + 1, monsters) && (currentTileIndex + 1) <= range.second)
            {
                availableSpaces.push_back(currentTileIndex + 1);
            }
            // Check top tile
            int topTileIndex = currentTileIndex - 16;
            std::cout << "Top Tile Index: " << topTileIndex << std::endl;
            if (!IsTileOccupied(topTileIndex, monsters))
            {
                availableSpaces.push_back(topTileIndex);
            }
            // Check bottom tile
            int bottomTileIndex = currentTileIndex + 16;
            std::cout << "Bottom Tile Index: " << bottomTileIndex << std::endl;
            if (!IsTileOccupied(bottomTileIndex, monsters))
            {
                availableSpaces.push_back(bottomTileIndex);
            }
        }
    return availableSpaces;
}
