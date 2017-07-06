#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
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
