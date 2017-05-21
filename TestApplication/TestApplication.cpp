#include "TestApplication.h"

TestApplication::TestApplication()
{
}

TestApplication::~TestApplication()
{
}

void TestApplication::OnLoadContent()
{
	Model = LoadModel("models/Cube.obj");
}

void TestApplication::OnStart()
{
	Scene* scene = GetRootScene();
	Actor = scene->AddActor(Model, nullptr);
	Actor2 = scene->AddActor(Model, nullptr);

	glm::vec3 scale(0.5f, 0.5f, 0.5f);
	Actor2->SetScale(scale);
}

void TestApplication::OnUpdate()
{
	TestCounter += 0.0001f;
	glm::vec3 eulerAngles(0.0f, TestCounter, 0.0f);
	glm::quat rotation = glm::quat(eulerAngles);
	Actor->SetRotation(rotation);

	glm::vec3 postion(0.0f, TestCounter, 0.0f);
	Actor2->SetPosition(postion);
}
