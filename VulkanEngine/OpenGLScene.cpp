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

	for (const auto& actorsByTexture : GroupedActors)
	{
		for (const auto& actorsByModel : actorsByTexture.second)
		{
			for (auto actor : actorsByModel.second)
			{
				delete actor;
			}
		}
	}

	for (auto actor : VacantActors)
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
	OpenGLActor* actor;
	if (VacantActors.size() > 0)
	{
		actor = VacantActors.back();
		actor->SetTexture(texture);
		actor->SetModel(model);
		VacantActors.pop_back();
	}
	else
	{
		actor = new OpenGLActor(model, texture);
	}

	auto rotation = glm::quat(angles);
	actor->SetTransform(position, rotation, scale);

	auto openGLTexture = static_cast<OpenGLTexture*>(actor->GetTexture());
	auto openGLModel = static_cast<OpenGLModel*>(actor->GetModel());
	GroupedActors[openGLTexture][openGLModel].push_back(actor);

	ActorCount++;
	VertexCount += model->GetVertexCount();

	return actor;
}

void OpenGLScene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
	{
		return;
	}

	auto openGLActor = static_cast<OpenGLActor*>(actor);
	auto texture = static_cast<OpenGLTexture*>(actor->GetTexture());
	auto model = static_cast<OpenGLModel*>(actor->GetModel());
	auto& actorGroup = GroupedActors[texture][model];
	auto position = std::find(actorGroup.begin(), actorGroup.end(), actor);
	if (position != actorGroup.end())
	{
		actorGroup.erase(position);
		VacantActors.push_back(openGLActor);

		ActorCount--;
		VertexCount -= model->GetVertexCount();
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

	auto viewProjection = GetCamera()->GetViewProjection(false);
	glUniformMatrix4fv(viewProjectionLocation, 1, GL_FALSE, glm::value_ptr(viewProjection));

	for (const auto& actorsByTexture : GroupedActors)
	{
		auto texture = actorsByTexture.first;
		texture->Bind();
		for (const auto& actorsByModel : actorsByTexture.second)
		{
			auto model = actorsByModel.first;
			model->Bind();
			for (auto actor : actorsByModel.second)
			{
				auto modelTransform = actor->GetTransform();
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelTransform));
				glDrawElements(GL_TRIANGLES, model->GetIndexCount(), GL_UNSIGNED_INT, 0);
			}
		}
	}

	for (auto scene : ChildScenes)
	{
		auto openGLScene = static_cast<OpenGLScene*>(scene);
		openGLScene->Draw();
	}
}
