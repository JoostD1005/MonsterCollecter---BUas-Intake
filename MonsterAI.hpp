#pragma once

#include <iostream>
#include <vector>

class Monster;

class MonsterAI // a class that checks if the monster can move or not.
{
public:
	void NextTile(std::vector<Monster*>& monsters, Monster* monster);
	bool IsTileOccupied(int tileIndex, std::vector<Monster*>& monsters);
	std::vector<int> findAvailableSpaces(int currentTileIndex, std::vector<Monster*>& monsters);
private:
	std::vector<int> availableSpaces;
};