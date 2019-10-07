#pragma once

#include <stack>
#include <memory>
#include <type_traits>

class Application;

class Scene
{
private:

public:
	virtual void OnUpdate(Application& app) = 0;
};

class SceneManager
{
private:
	std::stack<std::unique_ptr<Scene>> m_SceneStack;
public:
	void OnUpdate(Application& app) const
	{
		if (!m_SceneStack.empty())
		{
			m_SceneStack.top()->OnUpdate(app);
		}
	}

	template<class T>
	void PushScene()
	{
		static_assert(std::is_base_of<Scene, T>::value);
		
		m_SceneStack.push(std::make_unique<T>());
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
