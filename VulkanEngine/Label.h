#pragma once

#include <vector>
#include "SpriteFont.h"
#include "Actor.h"

class Scene;

class Label
{
public:
	Label(const char* text, SpriteFont& font, ::Scene& scene, glm::vec3 position);
	virtual ~Label();

	void SetText(const char* text);
	void ClearText();

private:
	std::vector<Actor*> Actors;
	SpriteFont& Font;
	::Scene& Scene;
	glm::vec3 Position;
};
