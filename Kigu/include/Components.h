#pragma once

#include "MathLib.h"

struct Transform
{
	vec2 position;

	Transform()
	{
	}

	Transform(const vec2& position)
		: position(position)
	{
	}

	Transform(float x, float y)
		: position(x, y)
	{
	}

	Transform(const Transform& transform)
		: position(transform.position)
	{
	}
};
