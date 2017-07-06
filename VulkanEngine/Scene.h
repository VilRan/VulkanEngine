#pragma once

#include <memory>
#include "Actor.h"
#include "Sprite.h"
#include "ICamera.h"
#include "Label.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual Actor* AddActor(Sprite* sprite, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 angles = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f }) = 0;
	virtual Actor* AddActor(Model* model, Texture* texture, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 angles = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f }) = 0;
	virtual Label* AddLabel(const char* text, SpriteFont* font, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 angles = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f }) = 0;
	virtual void RemoveActor(Actor* actor) = 0;
	virtual int GetActorCount() = 0;
	virtual int GetVertexCount() = 0;
	virtual Scene* AddScene() = 0;
	virtual void RemoveScene(Scene* scene) = 0;

	const std::shared_ptr<ICamera> GetCamera() const { return Camera; }
	void SetCamera(std::shared_ptr<ICamera> camera, bool passToChildScenes = true);
	const bool IsVisible() const { return Visible; }
	void SetVisible(bool visible) { Visible = visible; }

protected:
	std::vector<Scene*> ChildScenes;

private:
	std::shared_ptr<ICamera> Camera;
	bool Visible = true;
};

