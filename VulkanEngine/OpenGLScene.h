#pragma once
#include <glad/glad.h>
#include "Scene.h"

#include "OpenGLActor.h"

class OpenGLScene :
	public Scene
{
public:
	OpenGLScene(GLuint shaderProgram, std::shared_ptr<ICamera> camera);
	OpenGLScene(GLuint shaderProgram, float aspectRatio);
	virtual ~OpenGLScene();

	virtual Actor* AddActor(Sprite* sprite, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 angles = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f });
	virtual Actor* AddActor(Model* model, Texture* texture, glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec3 angles = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 1.0f, 1.0f, 1.0f });
	virtual void RemoveActor(Actor* actor);
	virtual Scene* AddScene();

	void Draw();

private:
	std::vector<OpenGLActor*> Actors;
	GLuint ShaderProgram;
};
