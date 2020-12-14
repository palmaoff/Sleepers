#include "Header.h"

Player::Player()
{
	pos.x = 0;
	pos.y = 0;
}

Player::Player(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void	Player::change_pos(float x, float y, int W, int H, float time)
{

	if (pos.x + x < W && pos.y + y < H &&
		pos.x + x >= 0 && pos.y + y >= 0)
	{
		pos.x += x * time * 8;
		pos.y += y * time * 8;
	}
}

float	Player::getX()
{
	return pos.x;
}

float	Player::getY()
{
	return pos.y;
}

void	Player::set_pos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

int		Player::get_keys(int MapWidth, int MapHeight, float fElapsedTime)
{
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		change_pos(-1, 0, MapWidth, MapHeight, fElapsedTime);
	else if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		change_pos(1, 0, MapWidth, MapHeight, fElapsedTime);
	else if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
		change_pos(0, -1, MapWidth, MapHeight, fElapsedTime);
	else if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
		change_pos(0, 1, MapWidth, MapHeight, fElapsedTime);
	else
		return 0;
	return 1;
}
