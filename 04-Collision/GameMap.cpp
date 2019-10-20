#include "GameMap.h"

GameMap::GameMap(LPCWSTR filePath, int _id, int _translate_x, int _translate_y)
{
	id = _id;
	translate_x = _translate_x;
	translate_y = _translate_y;
	texture->Add(id, filePath, D3DCOLOR_XRGB(0, 0, 0));
}

void GameMap::LoadMap(const char* mapIndex)
{
	ifstream infile;
	infile.open(mapIndex);
	while (infile)
	{
		infile >> numColTiles >> numRowTiles >> tileWidth >> tileHeight;
		for (int i = 0; i < numRowTiles; i++)
		{
			for (int j = 0; j < numColTiles; j++)
			{
				infile >> tileList[i][j];
			}
		}
	}
}

void GameMap::DrawMap(Camera* camera)
{
	remain_x = fmod(camera->getPosition().x, tileWidth);
	remain_y = fmod(camera->getPosition().y, tileHeight);

	int colTileLeft = camera->getPosition().x / tileWidth;
	int colTileRight = colTileLeft + tileWidth;
	int rowTileTop = camera->getPosition().y / tileHeight;
	int rowTileBottom = rowTileTop + tileHeight;

	for (int i = colTileLeft; i <= colTileRight; i++)
	{
		for (int j = rowTileTop; i <= rowTileBottom; i++)
		{
			float x = (i - colTileLeft) * tileWidth - remain_x + translate_x;
			float y = (j - rowTileTop) * tileHeight - remain_y + translate_y;

			int index = tileList[i][j];
			RECT rectTile;
			rectTile.left = (index % numColTiles) * tileWidth;
			rectTile.right = rectTile.left + tileWidth;
			rectTile.top = (index / numColTiles) * tileHeight;
			rectTile.bottom = rectTile.top + tileHeight;

			game->Draw(x, y, texture->Get(id), rectTile.left, rectTile.top, rectTile.right, rectTile.bottom);
		}
	}

}
