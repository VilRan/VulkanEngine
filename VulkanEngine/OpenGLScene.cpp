#include "OpenGLScene.h"

#include <glm/gtc/type_ptr.hpp>

#include "OpenGLModel.h"
#include "OpenGLTexture.h"

OpenGLScene::OpenGLScene(GLuint shaderProgram, std::shared_ptr<ICamera> camera)
{
	ShaderProgram = shaderProgram;
	SetCamera(camera, false);
}

OpenGLScene::OpenGLScene(GLuint shaderProgram, float aspectRatio)
	: OpenGLScene(shaderProgram, CreateDefaultCamera(aspectRatio))
{
}

OpenGLScene::~OpenGLScene()
{
	//This is here for now because - as it is - labels must be deleted before actors
	for (auto label : Labels)
	{
		delete label;
	}

	for (auto actor : Actors)
	{
		delete actor;
	}
}

Actor* OpenGLScene::AddActor(Sprite* sprite, glm::vec3 position, glm::vec3 angles, glm::vec3 scale)
{
	return AddActor(sprite->GetModel(), sprite->GetTexture(), position, angles, scale);
}

Actor* OpenGLScene::AddActor(Model* model, Texture* texture, glm::vec3 position, glm::vec3 angles, glm::vec3 scale)
{
	auto actor = new OpenGLActor(model, texture);
	glm::quat rotation = glm::quat(angles);
	actor->SetTransform(position, rotation, scale);
	Actors.push_back(actor);
	return actor;
}

void OpenGLScene::RemoveActor(Actor* actor)
{
	auto position = std::find(Actors.begin(), Actors.end(), actor);
	if (position != Actors.end())
	{
		Actors.erase(position);
		delete actor;
	}
}

Scene* OpenGLScene::AddScene()
{
	auto scene = new OpenGLScene(ShaderProgram, GetCamera());
	ChildScenes.push_back(scene);
	return scene;
}

void OpenGLScene::Draw()
{
	glUseProgram(ShaderProgram);
	auto viewProjectionLocation = glGetUniformLocation(ShaderProgram, "camera.viewProjection");
	auto modelLocation = glGetUniformLocation(ShaderProgram, "instance.model");
	auto textureLocation = glGetUniformLocation(ShaderProgram, "texSampler");

	auto viewProjection = GetCamera()->GetViewProjection();
	glUniformMatrix4fv(viewProjectionLocation, 1, GL_FALSE, glm::value_ptr(viewProjection));

	for (auto actor : Actors)
	{
		auto model = static_cast<OpenGLModel*>(actor->GetModel());
		auto texture = static_cast<OpenGLTexture*>(actor->GetTexture());
		auto modelTransform = actor->GetTransform();

		model->Bind();
		texture->Bind();
		glUniform1i(textureLocation, 0);
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelTransform));

		glDrawElements(GL_TRIANGLES, model->GetIndexCount(), GL_UNSIGNED_INT, 0);
	}

	for (auto scene : ChildScenes)
	{
		auto openGLScene = static_cast<OpenGLScene*>(scene);
		openGLScene->Draw();
	}

	glBindVertexArray(0);
}
