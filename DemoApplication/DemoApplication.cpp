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
	Camera = std::static_pointer_cast<Camera3D>(GetRootScene()->GetCamera());
	Camera->SetPosition({ -3.0f, 3.0f, -3.0f });
	Camera->SetTarget({ 0.0f, 0.0f, 0.0f });
	Camera->SetFar(100.0f);

	UiScene = GetRootScene()->AddScene();
	FpsLabel = UiScene->AddLabel("", Font, glm::vec3(GetWidth() / -1.0f + 32.0f, GetHeight() / -1.0f + 32.0f, 0.0f));
	UiScene->SetCamera(
		std::make_shared<Camera2D>(glm::vec2(0.0f, 0.0f), (float)GetWidth(), (float)GetHeight(), 0.0f)
	);
}

void DemoApplication::OnUpdate(UpdateEvent update)
{
	std::stringstream fpsText;
	fpsText << "FPS: " << update.GetFramesPerSecond();
	fpsText << "\nFrame Time: " << update.GetDeltaTime();
	FpsLabel->SetText(fpsText.str().c_str());
}

void DemoApplication::OnKey(KeyEvent key)
{
	if (key.GetAction() == GLFW_PRESS)
	{
		Camera->MoveBy({ 1.0f, 0.0f, 1.0f });
	}
}
