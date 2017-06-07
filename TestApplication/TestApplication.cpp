#include "TestApplication.h"

TestApplication::TestApplication()
{
	//SetBorder(false);
	//Resize(1920, 1080);
}

TestApplication::~TestApplication()
{
}

void TestApplication::OnLoadContent()
{
	Model = LoadModel("../Models/Cube.obj");
	Model2 = LoadModel("../Models/Icosphere.obj");
	Texture = LoadTexture("../Textures/ColoredCube.png");
	Texture2 = LoadTexture("../Textures/BlackAndWhiteCube.png");
	Texture3 = LoadTexture("../Textures/BlackAndWhiteTriangle.png");
	Sprite = CreateSprite(Texture);
	Font = LoadFont("../Fonts/Monospace.png", "../Fonts/Monospace.png.meta");
}

void TestApplication::OnStart()
{
	Scene* rootScene = GetRootScene();
	Scene2 = rootScene->AddScene();
	Scene2->SetVisible(false);
	Scene3 = rootScene->AddScene();

	Camera = std::static_pointer_cast<Camera3D>(rootScene->GetCamera());
	Camera2 = std::make_shared<Camera2D>(glm::vec2(0.0f, 0.0f), (float)GetWidth(), (float)GetHeight(), 0.0f);
	Scene3->SetCamera(Camera2);

	Actor = rootScene->AddActor(Model, Texture);
	Actor2 = rootScene->AddActor(Model, Texture2);
	Actor3 = Scene2->AddActor(Model2, Texture3);
	Actor5 = Scene3->AddActor(Sprite);
	Actor6 = Scene3->AddActor(Sprite);

	glm::vec3 scale(0.5f, 0.5f, 0.5f);
	Actor2->SetScale(scale);
	
	glm::vec3 position(-Texture->GetWidth() * 2, 0.0f, 0.0f);
	glm::vec3 angles(0.0f, 0.0f, 0.0f);
	glm::quat rotation(angles);
	scale = glm::vec3(1.0f, 1.00f, 1.00f);
	Actor5->SetTransform(position, rotation, scale);

	position = glm::vec3(Texture->GetWidth() * 2, 0.0f, 0.0f);
	Actor6->SetTransform(position, rotation, scale);
	
	position = glm::vec3(0.0f, Texture->GetHeight(), 0.0f);
	Scene3->AddLabel("This is a test!\nTesting Labels!", Font, position);
}

void TestApplication::OnUpdate(UpdateEvent update)
{
	TestCounter += (float)update.GetDeltaTime();
	glm::vec3 eulerAngles(0.0f, TestCounter, TestCounter / 2);
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
		Scene2->SetVisible(true);
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
			Camera = std::make_shared<Camera3D>(
				glm::vec3(3.0f, 3.0f, 3.0f),
				glm::vec3(3.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				60.0f, GetAspectRatio(), 0.1f, 100.0f
			);
			GetRootScene()->SetCamera(Camera, false);
			Scene2->SetCamera(Camera);
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

	Camera->SetPosition(glm::vec3(3.0f + TestCounter, 3.0f + TestCounter, 3.0f + TestCounter));
	Camera2->SetRotation(TestCounter);
}

void TestApplication::OnKey(KeyEvent key)
{
	if (key.GetAction() == GLFW_PRESS)
	{
		switch (key.GetId())
		{
		case GLFW_KEY_ESCAPE:
			Exit();
			break;
		default:
			break;
		}
	}
}

void TestApplication::OnCursor(CursorPositionEvent cursor)
{
}
