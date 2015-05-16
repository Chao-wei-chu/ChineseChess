#ifndef PLAYER_H
#define PLAYER_H
#include "Map.h"
#include "GUI.h"
class Player
{
public:
	Player()=delete;
	Player(bool icolor);
	SHORT move(COORD cursorP, COORD moveP, Map& map);
	COORD chooseMovePos(COORD cursorPos, Map& map, bool& isMoveSuc, bool& reChoose, GUI& gui);
private:
	bool color;   //true = ¬õ¤è false ¶Â¤è
};

#endif