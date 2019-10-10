#pragma once

#include <stack>
#include <memory>
#include <type_traits>

class Application;

class Scene
{
private:

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
