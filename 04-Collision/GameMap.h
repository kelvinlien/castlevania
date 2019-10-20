#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "Camera.h";
#include "Textures.h";
#include "Game.h";
#include <fstream>;

class GameMap
{
public:
	GameMap(LPCWSTR filePath, int _id, int _translate_x, int _translate_y);
	void LoadMap(const char* mapIndex);
	void DrawMap(Camera * camera);
	CTextures* texture = CTextures::GetInstance();
	CGame* game = CGame::GetInstance();
private:
	int id;
	int translate_x;
	int translate_y;
	float remain_x, remain_y;
	int tileList[50][50];
	int numColTiles;
	int numRowTiles;
	int tileWidth;
	int tileHeight;
};
