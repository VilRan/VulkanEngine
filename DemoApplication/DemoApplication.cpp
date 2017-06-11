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
	Font = LoadFont("../Fonts/Monospace.png", "../Fonts/Monospace.png.meta");
}

void DemoApplication::OnStart()
{
	MapScene = GetRootScene()->AddScene();

	Map.Initialize(MapScene, &Ruleset, 100, 10, 100);
	Camera = std::make_shared<FirstPersonCamera>();
	Camera->SetPosition({ 50.0f, 12.0f, 50.0f });
	Camera->SetFar(200.0f);
	Camera->SetFieldOfView(90.0f);
	MapScene->SetCamera(Camera);

	UiScene = GetRootScene()->AddScene();
	FpsLabel = UiScene->AddLabel("", Font, glm::vec3(GetWidth() / -2.0f + 32.0f, GetHeight() / -2.0f + 32.0f, 0.0f));
	UiScene->SetCamera(
		std::make_shared<Camera2D>(glm::vec2(0.0f, 0.0f), (float)GetWidth(), (float)GetHeight(), 0.0f)
	);

	FpsTimer.SetEvent(std::bind(&DemoApplication::HandleFpsTimer, this, std::placeholders::_1));
	FpsTimer.SetInterval(0.1);
	FpsTimer.Start();
}

void DemoApplication::OnUpdate(UpdateEvent update)
{
	FpsUpdate = UpdateEvent(update.GetDeltaTime(), update.GetAverageDeltaTime());
	FpsTimer.Update(update);
	TryMoveCamera(update);
	Map.Update(update);
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

void DemoApplication::OnClick(ClickEvent click)
{

}

void DemoApplication::TryMoveCamera(UpdateEvent update)
{
	float movementSpeed = (float)update.GetDeltaTime() * 10.0f;
	if (GetKeyState(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		movementSpeed *= 2;
	}
	if (GetKeyState(GLFW_KEY_W) == GLFW_PRESS)
	{
		Camera->MoveForward(movementSpeed);
	}
	if (GetKeyState(GLFW_KEY_S) == GLFW_PRESS)
	{
		Camera->MoveBackward(movementSpeed);
	}
	if (GetKeyState(GLFW_KEY_A) == GLFW_PRESS)
	{
		Camera->MoveLeft(movementSpeed);
	}
	if (GetKeyState(GLFW_KEY_D) == GLFW_PRESS)
	{
		Camera->MoveRight(movementSpeed);
	}
	if (GetKeyState(GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Camera->MoveBy({ 0.0f, movementSpeed, 0.0f });
	}
	if (GetKeyState(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Camera->MoveBy({ 0.0f, -movementSpeed, 0.0f });
	}
}

void DemoApplication::UpdateFpsLabel(UpdateEvent update)
{
	std::stringstream fpsText;
	fpsText << "FPS:          " << update.GetFramesPerSecond() << "\n";
	fpsText << "FPS (avg.):   " << update.GetAverageFramesPerSecond() << "\n";
	fpsText << "Frame Time:   " << update.GetDeltaTime() << "\n";
	fpsText << "Actor Count:  " << GetRootScene()->GetActorCount() << "\n";
	fpsText << "Vertex Count: " << GetRootScene()->GetVertexCount() << "\n";
	FpsLabel->SetText(fpsText.str().c_str());
}

void DemoApplication::HandleFpsTimer(TimerEvent timer)
{
	UpdateFpsLabel(FpsUpdate);
}
