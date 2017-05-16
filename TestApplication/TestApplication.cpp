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
}

void TestApplication::OnUpdate()
{
	TestCounter += 0.001f;
	glm::vec3 eulerAngles(0.0f, TestCounter, 0.0f);
	glm::quat rotation = glm::quat(eulerAngles);
	Actor->SetRotation(rotation);
}
