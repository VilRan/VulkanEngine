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

	Model* icosphere = application.LoadModel("Models/Icosphere.obj");
	Texture* blackAndWhiteTriangle = application.LoadTexture("Textures/BlackAndWhiteTriangle.png");
	ProjectileTypes.emplace("Icosphere", ProjectileType(icosphere, blackAndWhiteTriangle));
}

TileType Ruleset::GetTileType(const char* uid)
{
	return TileTypes[uid];
}

ProjectileType Ruleset::GetProjectileType(const char* uid)
{
	return ProjectileTypes[uid];
}