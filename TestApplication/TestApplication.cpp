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

	if (TestCounter < 1.0f)
	{
		glm::vec3 position(0.0f, TestCounter, 0.0f);
		Actor2->SetPosition(position);
	}
	else if (Actor2 != nullptr)
	{
		GetRootScene()->RemoveActor(Actor2);
		Actor2 = nullptr;
	}

	float x = cos(TestCounter) * 2.0f;
	float y = 0.0f;
	float z = sin(TestCounter) * 2.0f;
	glm::vec3 position(x, y, z);
	Actor3->SetPosition(position);

	if (Actor4 == nullptr)
	{
		if (TestCounter > 2.0f)
		{
			Actor4 = GetRootScene()->AddActor(Model2, Texture3);
		}
	}
	else
	{
		x = sin(TestCounter) * 2.0f;
		y = cos(TestCounter) * 2.0f;
		z = 0.0f;
		position = glm::vec3(x, y, z);
		Actor4->SetPosition(position);
	}
}
