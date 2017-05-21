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
	Model2 = LoadModel("models/Icosphere.obj");
	Texture = LoadTexture("textures/ColoredCube.png");
	Texture2 = LoadTexture("textures/BlackAndWhiteCube.png");
	Texture3 = LoadTexture("textures/BlackAndWhiteTriangle.png");
}

void TestApplication::OnStart()
{
	Scene* scene = GetRootScene();
	Actor = scene->AddActor(Model, Texture);
	Actor2 = scene->AddActor(Model, Texture2);
	Actor3 = scene->AddActor(Model2, Texture3);

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

	float x = cos(TestCounter) * 2.0f;
	float z = sin(TestCounter) * 2.0f;
	postion = glm::vec3(x, 0.0f, z);
	Actor3->SetPosition(postion);
}
