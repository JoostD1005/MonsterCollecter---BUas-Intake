#pragma once

#include <iostream>
#include <list>
// i want the monsters to move randomly on the screen: 
// option 1:
// i need create a tile map, store data on wich tile the monster is placed, check al surrounding tiles for other monsters
// if: other monsters are on a surrounding tile --> can't move there. 
// if: if surrounding tiles are outside of the screen --> can't move there.
// move the monster to an available space using an animation.
// add bool so that the AI freezes if it is false.  

//option 2: ----> way better
// create tile map, stor data on wich tile the monster is placed,
// get list of al the available tiles surrounding the monster.
// pick a random from the list
// 
//

class EnemyAI
{
public:

	void move(std::list<char> list);


private:
};