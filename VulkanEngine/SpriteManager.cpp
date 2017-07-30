#include "SpriteManager.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::SpriteManager(::ModelManager* modelManager)
{
	Initialize(modelManager);
}

SpriteManager::~SpriteManager()
{
	for (auto sprite : Sprites)
	{
		delete sprite;
	}
}

void SpriteManager::Initialize(::ModelManager * modelManager)
{
	ModelManager = modelManager;
}

Sprite* SpriteManager::Create(Texture* texture)
{
	Engine::Rectangle area(0, 0, texture->GetWidth(), texture->GetHeight());
	return Create(texture, area);
}

Sprite* SpriteManager::Create(Texture* texture, Engine::Rectangle area)
{
	float width = area.GetWidth() / 2.0f;
	float height = area.GetHeight() / 2.0f;
	float left = area.GetLeft() / (float)texture->GetWidth();
	float right = area.GetRight() / (float)texture->GetWidth();
	float top = area.GetTop() / (float)texture->GetHeight();
	float bottom = area.GetBottom() / (float)texture->GetHeight();

	std::vector<Vertex> vertices(4);
	vertices[0].Position = glm::vec3(-width, -height, 0.0f);
	vertices[0].TextureCoordinates = glm::vec3(left, top, 0.0f);
	vertices[0].Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[1].Position = glm::vec3(width, -height, 0.0f);
	vertices[1].TextureCoordinates = glm::vec3(right, top, 0.0f);
	vertices[1].Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[2].Position = glm::vec3(-width, height, 0.0f);
	vertices[2].TextureCoordinates = glm::vec3(left, bottom, 0.0f);
	vertices[2].Color = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[3].Position = glm::vec3(width, height, 0.0f);
	vertices[3].TextureCoordinates = glm::vec3(right, bottom, 0.0f);
	vertices[3].Color = glm::vec3(1.0f, 1.0f, 1.0f);

	std::vector<uint32_t> indices(6);
	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	Model* model = ModelManager->Create(vertices, indices);
	auto sprite = new Sprite(model, texture, area);
	Sprites.push_back(sprite);
	return sprite;
}
