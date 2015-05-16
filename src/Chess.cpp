#include "Chess.h"
#include "Map.h"
#include "Game.h"

Chess::Chess(string iName, bool icolor, COORD iPos) : Name(iName), Color(icolor), Pos(iPos), alive(true){}
King::King(string iName, bool icolor, COORD iPos) : Chess(iName, icolor, iPos){}
Chariot::Chariot(string iName, bool icolor, COORD iPos) : Chess(iName, icolor, iPos){}
Horse::Horse(string iName, bool icolor, COORD iPos) : Chess(iName, icolor, iPos){}
Cannon::Cannon(string iName, bool icolor, COORD iPos) : Chess(iName, icolor, iPos){}
Elephant::Elephant(string iName, bool icolor, COORD iPos) : Chess(iName, icolor, iPos){}
Adviser::Adviser(string iName, bool icolor, COORD iPos) : Chess(iName, icolor, iPos){}
Pawn::Pawn(string iName, bool icolor, COORD iPos) : Chess(iName, icolor, iPos){}

Chess::~Chess(){}
King::~King(){}
Chariot::~Chariot(){}
Horse::~Horse(){}
Cannon::~Cannon(){}
Elephant::~Elephant(){}
Adviser::~Adviser(){}
Pawn::~Pawn(){}

void Chess::setAlive(bool t)
{
	alive = t;
}

void Chess::setPos(COORD p)
{
	Pos = p;
}

/***base class***/
bool Chess::isValid(COORD move, const Map& map) const
{
	return true;
}
/*******�N*******/
bool King::isValid(COORD moveP, const Map& map) const
{
	bool color = getColor();
	COORD path = ComXY(moveP.X - getPos().X, moveP.Y - getPos().Y);

	if ((color ? 7 : 0) <= moveP.Y && moveP.Y <= (color ? 9 : 2) && moveP.X >= 3 && moveP.X <= 5 &&    //
		((abs(path.X) == 1 && abs(path.Y) == 0) || (abs(path.Y) == 1 && abs(path.X) == 0)))            // > �@�벾��
	{                                                                                                  //
		if (map.pChess[moveP.X][moveP.Y] != NULL && color == map.pChess[moveP.X][moveP.Y]->getColor()) //
			return false;                                                                              //
		return true;                                                                                   //
	}                                                                                                  //

	else if (getPos().X == moveP.X &&                                                           //������  �i�Y���
		(moveP.X == (color ? map.bKingPointer()->getPos().X : map.rKingPointer()->getPos().X))&&
		(moveP.Y == (color ? map.bKingPointer()->getPos().Y : map.rKingPointer()->getPos().Y)))
	{
		for (int i = (getPos().Y > moveP.Y ? moveP.Y : getPos().Y) + 1; i < (getPos().Y > moveP.Y ? getPos().Y : moveP.Y); i++)
			if (map.pChess[moveP.X][i] != NULL)
				return false;
		return true;
	}
	return false;
}
/*******��*******/
bool Chariot::isValid(COORD moveP, const Map& map) const
{
	Chess* tempCh = map.pChess[moveP.X][moveP.Y];
	bool pass = false;
	if ((getPos().X - moveP.X) != 0 && (getPos().Y == moveP.Y))      //���k�e�i
	{
		for (int i = (getPos().X > moveP.X ? moveP.X : getPos().X) + 1;i < (getPos().X > moveP.X ? getPos().X : moveP.X); i++)
			if (map.pChess[i][moveP.Y] != NULL)
				return false;
		pass = true;
	}
	else if ((getPos().X == moveP.X) && (getPos().Y - moveP.Y) != 0) //�W�U�e�i
	{
		for (int i = (getPos().Y > moveP.Y ? moveP.Y : getPos().Y) + 1;i < (getPos().Y > moveP.Y ? getPos().Y : moveP.Y); i++)
			if (map.pChess[moveP.X][i] != NULL)
				return false;
		pass = true;
	}
	if (pass) {
		if (tempCh != NULL) {  //�ؼЦ�m���Ѥl�A�B��l��m���ؼЦ�m�����L��L�Ѥl
			if (getColor() == tempCh->getColor())
				return false;  //�P��@�@return false
		}
			return true;
	}
	return false;
}
/*******��*******/
bool Horse::isValid(COORD moveP, const Map& map) const
{
	if (abs(getPos().Y - moveP.Y) ==2 )//�䰨�}Y
	{
		if (map.pChess[getPos().X][getPos().Y - (getPos().Y - moveP.Y)/2] != NULL)
			return false;
	}
	if (abs(getPos().X - moveP.X) == 2)//�䰨�}X
	{
		if (map.pChess[getPos().X - (getPos().X - moveP.X)/2][getPos().Y] != NULL)
			return false;
	}

	if (abs(getPos().Y - moveP.Y) == 2 && abs(getPos().X - moveP.X) == 1 ||
		(abs(getPos().Y - moveP.Y) == 1 && abs(getPos().X - moveP.X) == 2))
	{
		return true;
	}
	return false;
	
}
/*******��*******/
bool Cannon::isValid(COORD moveP, const Map& map) const
{
	short count = 0;   //�ݤ������X�ӴѤl
	if (abs(getPos().X - moveP.X) != 0 && abs(getPos().Y - moveP.Y) == 0)
		if (getPos().X - moveP.X > 0)
		{
			for (int i = getPos().X - 1; i > moveP.X; i--)
				if (map.pChess[i][getPos().Y] != NULL)
					count++;
			if ((count == 1 && map.pChess[moveP.X][moveP.Y] != NULL)
				|| count == 0 && map.pChess[moveP.X][moveP.Y] == NULL)
				return true;
		}
		else
		{
			for (int i = getPos().X + 1; i < moveP.X; i++)
				if (map.pChess[i][getPos().Y] != NULL)
					count++;
			if ((count == 1 && map.pChess[moveP.X][moveP.Y] != NULL)
				|| count == 0 && map.pChess[moveP.X][moveP.Y] == NULL)
				return true;
		}
	else if (abs(getPos().X - moveP.X) == 0 && abs(getPos().Y - moveP.Y) != 0)
		if (getPos().Y - moveP.Y > 0)
		{
			for (int i = getPos().Y - 1; i > moveP.Y; i--)
				if (map.pChess[getPos().X][i] != NULL)
					count++;
			if ((count == 1 && map.pChess[moveP.X][moveP.Y] != NULL)
				|| count == 0 && map.pChess[moveP.X][moveP.Y] == NULL)
				return true;
		}
		else
		{
			for (int i = getPos().Y + 1; i < moveP.Y; i++)
				if (map.pChess[getPos().X][i] != NULL)
					count++;
			if ((count == 1 && map.pChess[moveP.X][moveP.Y] != NULL)
				|| count == 0 && map.pChess[moveP.X][moveP.Y] == NULL)
				return true;
		}
		return false;
}
/*******�H*******/
bool Elephant::isValid(COORD moveP, const Map& map) const
{
	if (map.pChess[(getPos().X + moveP.X) / 2][(getPos().Y + moveP.Y) / 2] == NULL)//�����S�d��F��
	{
	   if (getColor() == true)
	   {
		   if (abs(moveP.X - getPos().X) == 2 && abs(moveP.Y - getPos().Y) == 2 && moveP.Y >= 5 && moveP.Y <= 9)
			  return true;
	   }
	   else
	   {
	    	if (abs(moveP.X - getPos().X) == 2 && abs(moveP.Y - getPos().Y) == 2 && moveP.Y >= 0 && moveP.Y <= 4)
			  return true;
	   }
	}
	return false;
	
}
/*******�h*******/
bool Adviser::isValid(COORD moveP, const Map& map) const
{
	if (moveP.X >= 3 && moveP.X <= 5)
	{
		if (getColor() == true)
		{
			if (abs(moveP.X - getPos().X) == 1 && abs(moveP.Y - getPos().Y) == 1 && moveP.Y >= 7 && moveP.Y <= 9)
				return true;
		}
		else
		{
			if (abs(moveP.X - getPos().X) == 1 && abs(moveP.Y - getPos().Y) == 1 && moveP.Y >= 0 && moveP.Y <= 2)
				return true;
		}
	}
	return false;
}
/*******�L*******/
bool Pawn::isValid(COORD moveP, const Map& map) const
{
	if (getColor() == true)//red
	{
		if (getPos().Y <= 4)//�w�L�e
		{
			if (((getPos().Y - moveP.Y) == 1 && abs(getPos().X - moveP.X) == 0) ||
				(abs(getPos().Y - moveP.Y) == 0 && abs(getPos().X - moveP.X) == 1))
				return true;
		}
		else//���L�e
			if (getPos().Y - moveP.Y == 1 && abs(getPos().X - moveP.X) == 0)
			{
				return true;
			}
		return false;
	}
	else//black
	{
		if (getPos().Y >= 5)//�w�L�e
		{
			if ((getPos().Y - moveP.Y == -1 && abs(getPos().X - moveP.X) == 0) ||
				(abs(getPos().Y - moveP.Y) == 0 && abs(getPos().X - moveP.X) == 1))
				return true;
		}
		else//���L�e
			if (getPos().Y - moveP.Y == -1 && abs(getPos().X - moveP.X) == 0)
			{
				return true;
			}
		return false;
		}
}

bool Chess::isDeath() {
	return (!alive);
}