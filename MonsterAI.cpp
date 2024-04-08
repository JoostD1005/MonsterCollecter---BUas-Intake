#include "MonsterAI.hpp"




//bool MonsterAI::IsTileOccupied(int tileIndex, std::vector<Monster*>&monsters)
//{
//	for (Monster* monster : monsters)
//	{
//		if (monster->GetTileIndex() == tileIndex)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
//
//std::vector<int> MonsterAI::findAvailableSpaces(int currentTileIndex, std::vector<Monster*>& monsters)
//{
//	std::vector<int> availableSpaces;
//
//	// Check left tile
//	if (!IsTileOccupied(currentTileIndex - 1, monsters)) {
//		availableSpaces.push_back(currentTileIndex - 1);
//	}
//	// Check right tile
//	if (!IsTileOccupied(currentTileIndex + 1, monsters)) {
//		availableSpaces.push_back(currentTileIndex + 1);
//	}
//	// Check top tile
//	if (!IsTileOccupied(currentTileIndex - 16, monsters)) {
//		availableSpaces.push_back(currentTileIndex - 16);
//	}
//	// Check bottom tile
//	if (!IsTileOccupied(currentTileIndex + 16, monsters)) {
//		availableSpaces.push_back(currentTileIndex + 16);
//	}
//
//	return availableSpaces;
//}
