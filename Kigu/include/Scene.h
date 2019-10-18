#pragma once

#include <stack>
#include <memory>
#include <type_traits>

#include "Entity.h"
#include "Components.h"

class Application;

class Scene
{
private:
	friend class SceneManager;

	entt::registry m_Registry;
protected:
	inline Entity AddEntity(PrefabFactory prefab = KiguPrefabs::Default)
	{
		return prefab(m_Registry);
	}
public:
	virtual void OnEnter() = 0;
};

class SceneManager
{
private:
	std::stack<std::shared_ptr<Scene>> m_SceneStack;
public:
	void OnUpdate(Application& app) const
	{
		if (!m_SceneStack.empty())
		{
			// Update scene systems.
			auto current = m_SceneStack.top();

			// Sample to iterate over every transformable object.
			current->m_Registry.view<Transform>().each([] (Transform& transform) {
				std::cout << "(" << transform.position.x << ", " << transform.position.y << ")" << std::endl;;
			});
		}
	}

	template<class T>
	void PushScene()
	{
		static_assert(std::is_base_of<Scene, T>::value);
		
		auto scene = std::make_shared<T>();
		scene->OnEnter();

		m_SceneStack.push(scene);
	}

	void PopScene()
	{
		if (!m_SceneStack.empty())
		{
			m_SceneStack.pop();
		}
	}

	template<class T>
	void SetScene()
	{
		static_assert(std::is_base_of<Scene, T>::value);

		PopScene();
		PushScene<T>();
	}
};
