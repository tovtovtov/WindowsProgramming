#pragma once

#include "framework.h"

using namespace std;

class ResourceManager;

enum MazeDifficulty
{
	EASY,
	NORMAL,
	HARD
};

class Map
{
private:
	vector<vector<int>> m_mapData;

	int m_width;
	int m_height;

	mt19937 random;

	void CarveMaze(int x, int y);

	void ConnectPaths(MazeDifficulty diff);

	void RemoveWall(int x, int y);

public:
	Map();

	void GenerateMaze(int width, int height, MazeDifficulty diff, unsigned int seed);
	
	void Render(HDC hdc, ResourceManager* resource);

	bool IsWalkable(int x, int y);
};

