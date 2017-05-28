#pragma once

#include <memory>
#include "Actor.h"
#include "Sprite.h"
#include "ICamera.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual Actor* AddActor(Sprite* sprite) = 0;
	virtual Actor* AddActor(Model* model, Texture* texture) = 0;
	virtual void RemoveActor(Actor* actor) = 0;
	virtual Scene* AddScene() = 0;
	virtual void RemoveScene(Scene* scene) = 0;
	virtual std::shared_ptr<ICamera> GetCamera() = 0;
	virtual void SetCamera(std::shared_ptr<ICamera> camera, bool passToChildScenes = true) = 0;
	inline void SetVisible(bool visible) { Visible = visible; }
	inline const bool IsVisible() const { return Visible; }

private:
	bool Visible = true;
};

