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
	Texture* whiteAndBlackTriangle = textures.Load("../Textures/WhiteAndBlackTriangle.png");
	ProjectileTypes.emplace("Icosphere", ProjectileType(icosphere, blackAndWhiteTriangle));
	ProjectileTypes.emplace("InverseIcosphere", ProjectileType(icosphere, whiteAndBlackTriangle));

	Model* torus = models.Load("../Models/Torus.obj");
	Texture* blackAndWhiteSquare = textures.Load("../Textures/BlackAndWhiteSquare.png");
	Texture* whiteAndBlackSquare = textures.Load("../Textures/WhiteAndBlackSquare.png");
	ProjectileTypes.emplace("Torus", ProjectileType(torus, blackAndWhiteSquare));
	ProjectileTypes.emplace("InverseTorus", ProjectileType(torus, whiteAndBlackSquare));
}

TileType Ruleset::GetTileType(const char* uid)
{
	return TileTypes[uid];
}

ProjectileType Ruleset::GetProjectileType(const char* uid)
{
	return ProjectileTypes[uid];
}