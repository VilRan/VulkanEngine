#include "Label.h"

#include "Scene.h"

Label::Label(const char* text, SpriteFont& font, ::Scene& scene, glm::vec3 position)
	: Font(font), Scene(scene)
{
	Position = position;
	SetText(text);
}

Label::~Label()
{
	ClearText();
}

void Label::SetText(const char* text)
{
	ClearText();

	size_t i = 0;
	int maxRowHeight = 0;
	glm::vec3 offset = Position;
	while (text[i] != '\0')
	{
		char c = text[i];
		switch (c)
		{
		case '\n':
			offset = glm::vec3(Position.x, offset.y + maxRowHeight, Position.y);
			maxRowHeight = 0;
			break;
		case ' ':
			offset += glm::vec3(Font.GetSpaceWidth(), 0.0f, 0.0f);
			break;
		default:
			Sprite* sprite = Font.GetSprite(c);
			Rectangle bounds = sprite->GetBounds();
			Actor* actor = Scene.AddActor(sprite, offset);
			Actors.push_back(actor);
			offset += glm::vec3(bounds.GetWidth(), 0.0f, 0.0f);

			if (bounds.GetHeight() > maxRowHeight)
			{
				maxRowHeight = bounds.GetHeight();
			}
			break;
		}

		i++;
	}
}

void Label::ClearText()
{
	for (auto actor : Actors)
	{
		Scene.RemoveActor(actor);
	}
	Actors.clear();
}
