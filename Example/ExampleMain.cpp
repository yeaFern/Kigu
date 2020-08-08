#include <Kigu.h>
#include <KiguMain.h>

#include <iostream>

#include <imgui/imgui.h>

class ExampleApplication : public Kigu::Application
{
private:
	Kigu::ShaderPtr m_Shader;
public:
	void OnInitialize()
	{
		m_Shader = Kigu::Shader::Create(
			"Basic",
			Kigu::File("Data/Shaders/Basic.vs"),
			Kigu::File("Data/Shaders/Basic.fs")
		);
	}

	void OnUpdate()
	{
		// Kigu::Renderer::BeginPass();
		// Kigu::Renderer::UseFramebuffer(Framebuffer::Default());
		// Kigu::Renderer::UseShader(m_Shader);

		// Kigu::Renderer::Submit(m_MyMesh);
		
		// Kigu::Renderer::EndPass();

		glUseProgram(m_Shader->GetProgram());
		Kigu::Renderer::Test();
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
