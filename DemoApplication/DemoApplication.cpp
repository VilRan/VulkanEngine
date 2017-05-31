#include "DemoApplication.h"

#include <string>
#include <sstream>
#include "Camera2D.h"

DemoApplication::DemoApplication()
{
}

DemoApplication::~DemoApplication()
{
}

void DemoApplication::OnLoadContent()
{
	Ruleset.Initialize(*this);
	Font = LoadFont("Fonts/Monospace.png", "Fonts/Monospace.png.meta");
}

void DemoApplication::OnStart()
{
	TerrainScene = GetRootScene()->AddScene();

	Map.Initialize(TerrainScene, &Ruleset, 100, 1, 100);
	Camera = std::make_shared<FirstPersonCamera>();
	Camera->SetPosition({ -3.0f, 3.0f, -3.0f });
	Camera->SetFar(100.0f);
	TerrainScene->SetCamera(Camera);

	UiScene = GetRootScene()->AddScene();
	FpsLabel = UiScene->AddLabel("", Font, glm::vec3(GetWidth() / -1.0f + 32.0f, GetHeight() / -1.0f + 32.0f, 0.0f));
	UiScene->SetCamera(
		std::make_shared<Camera2D>(glm::vec2(0.0f, 0.0f), (float)GetWidth(), (float)GetHeight(), 0.0f)
	);
}

void DemoApplication::OnUpdate(UpdateEvent update)
{
	std::stringstream fpsText;
	fpsText << "FPS:        " << update.GetFramesPerSecond() << "\n";
	fpsText << "FPS (avg.): " << update.GetAverageFramesPerSecond() << "\n";
	fpsText << "Frame Time: " << update.GetDeltaTime() << "\n";
	FpsLabel->SetText(fpsText.str().c_str());

	float movementSpeed = update.GetDeltaTime() * 10.0f;
	if (GetKeyState(GLFW_KEY_W))
	{
		Camera->MoveForward(movementSpeed);
	}
	if (GetKeyState(GLFW_KEY_S))
	{
		Camera->MoveBackward(movementSpeed);
	}	
	if (GetKeyState(GLFW_KEY_A))
	{
		Camera->MoveLeft(movementSpeed);
	}	
	if (GetKeyState(GLFW_KEY_D))
	{
		Camera->MoveRight(movementSpeed);
	}
}

void DemoApplication::OnKey(KeyEvent key)
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

void DemoApplication::OnCursor(CursorPositionEvent cursor)
{
	Camera->Rotate((float)cursor.GetDeltaX() / -100.0f, (float)cursor.GetDeltaY() / 100.0f);
}
