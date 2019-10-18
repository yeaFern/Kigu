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

using PrefabFactory = std::function<Entity(entt::registry&)>;
#define MakePrefab(name) inline Entity name(entt::registry& r) { Entity e = Entity(r, r.create());
#define AddComponent(name, ...) e.Add<name>(__VA_ARGS__);
#define DonePrefab() return e; }

namespace KiguPrefabs
{
	MakePrefab(Default)
	DonePrefab()
}
