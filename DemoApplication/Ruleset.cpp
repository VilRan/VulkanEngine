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
	auto& models = *application.GetModels();
	auto& textures = *application.GetTextures();

	Model* cube = models.Load("../Models/Cube.obj");
	Texture* blackAndWhiteCube = textures.Load("../Textures/BlackAndWhiteCube.png");
	Texture* coloredCube = textures.Load("../Textures/ColoredCube.png");
	TileTypes.emplace("Empty", TileType(nullptr, nullptr));
	TileTypes.emplace("Block", TileType(cube, blackAndWhiteCube));
	TileTypes.emplace("Colored", TileType(cube, coloredCube));

	Model* icosphere = models.Load("../Models/Icosphere.obj");
	Texture* blackAndWhiteTriangle = textures.Load("../Textures/BlackAndWhiteTriangle.png");
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