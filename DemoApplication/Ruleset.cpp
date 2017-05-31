#include "Ruleset.h"

#include "DemoApplication.h"

Ruleset::Ruleset()
{
}

Ruleset::~Ruleset()
{
}

void Ruleset::Initialize(DemoApplication& application)
{
	Model* cube = application.LoadModel("Models/Cube.obj");
	Texture* blackAndWhiteCube = application.LoadTexture("Textures/BlackAndWhiteCube.png");
	Texture* coloredCube = application.LoadTexture("Textures/ColoredCube.png");
	TileTypes.emplace("Empty", TileType(nullptr, nullptr));
	TileTypes.emplace("Block", TileType(cube, blackAndWhiteCube));
	TileTypes.emplace("Colored", TileType(cube, coloredCube));
}

TileType Ruleset::GetTileType(const char* uid)
{
	return TileTypes[uid];
}
