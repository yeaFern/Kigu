#include <Kigu.h>
#include <KiguMain.h>

#include <iostream>

#include <imgui/imgui.h>

class ExampleApplication : public Kigu::Application
{
public:
	void OnInitialize()
	{
		Kigu::ShaderPtr shader = Kigu::Shader::Create(
			"Basic",
			Kigu::File("Data/Shaders/Basic.vs"),
			Kigu::File("Data/Shaders/Basic.fs")
		);
	}

	void OnUpdate()
	{
	}

	void OnImGuiUpdate()
	{
		ImGui::Begin("Assets");
		for (auto it = Kigu::AssetManager::Begin(); it != Kigu::AssetManager::End(); ++it)
		{
			auto info = Kigu::AssetManager::GetAssetTypeInfo(it->Type);
			std::string line = it->Identifier + " : " + std::string(info.Name);
			ImGui::Text("%s", line.c_str());
		}
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

namespace Kigu
{
	Application* Create()
	{
		return new ExampleApplication;
	}
}
