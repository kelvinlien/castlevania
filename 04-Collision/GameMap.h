#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class GameMap
{
public:
	GameMap(LPCWSTR mapPath, int id, int translate_x, int translate_y);
	void LoadMap(LPCWSTR mapPath);
	void DrawMap();
private:
	int id;
	int translate_x;
	int translate_y;
};
