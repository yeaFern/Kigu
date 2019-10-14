#pragma once

#include <entt/entt.hpp>

class Entity
{
private:
	entt::registry& m_Registry;
	entt::entity m_Handle;
public:
	Entity(entt::registry& registry, entt::entity handle)
		: m_Registry(registry), m_Handle(handle)
	{
	}

	template<typename Component, typename... Args>
	inline void Add(Args&& ... args) {
		m_Registry.assign<Component>(m_Handle, std::forward<Args>(args)...);
	}
};
