#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto childScene : ChildScenes)
	{
		delete childScene;
	}
}

Label* Scene::AddLabel(const char* text, SpriteFont* font, glm::vec3 position, glm::vec3 angles, glm::vec3 scale)
{
	auto label = new Label(text, *font, *this, position);
	Labels.push_back(label);
	return label;
}

int Scene::GetActorCount()
{
	int count = 0;
	for (auto childScene : ChildScenes)
	{
		count += childScene->GetActorCount();
	}
	count += ActorCount;
	return count;
}

int Scene::GetVertexCount()
{
	int count = 0;
	for (auto childScene : ChildScenes)
	{
		count += childScene->GetVertexCount();
	}
	count += VertexCount;
	return count;
}

void Scene::RemoveScene(Scene* scene)
{
	auto position = std::find(ChildScenes.begin(), ChildScenes.end(), scene);
	ChildScenes.erase(position);
	delete scene;
}

void Scene::SetCamera(std::shared_ptr<ICamera> camera, bool passToChildScenes)
{
	Camera = camera;
	if (passToChildScenes)
	{
		for (auto childScene : ChildScenes)
		{
			childScene->SetCamera(camera);
		}
	}
}

std::shared_ptr<Camera3D> Scene::CreateDefaultCamera(float aspectRatio)
{
	return std::make_shared<Camera3D>(
		glm::vec3(3.0f, 3.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		60.0f, aspectRatio, 0.1f, 10.0f
		);
}

