#pragma once
#include "Actor.h"
class OpenGLActor :
	public Actor
{
public:
	OpenGLActor(::Model* model, ::Texture* texture);
	virtual ~OpenGLActor();
};
