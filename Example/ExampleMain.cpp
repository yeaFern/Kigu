#include <Kigu.h>
#include <KiguMain.h>

#include <iostream>

#include <imgui/imgui.h>

class ExampleApplication : public Kigu::Application
{
private:
	Kigu::ShaderPtr m_Shader;
	Kigu::VertexArray* m_VertexArray;
public:
	void OnInitialize()
	{
		m_Shader = Kigu::Shader::Create(
			"Basic",
			Kigu::File("Data/Shaders/Basic.vs"),
			Kigu::File("Data/Shaders/Basic.fs")
		);

		struct Vertex
		{
			float x, y, z;
			float r, g, b;
		};

		m_VertexArray = new Kigu::VertexArray;
		m_VertexArray->SetData(std::vector<Vertex> {
			{ 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, },
			{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, },
			{ 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, }
		}, 1, {
			{ Kigu::AttribType::Float3, "v_Position" },
			{ Kigu::AttribType::Float3, "v_Color" }
		});
	}

	void OnUpdate()
	{
		Kigu::Renderer::BeginPass("Main");
		Kigu::Renderer::UseFramebuffer(Kigu::Framebuffer::Default);
		Kigu::Renderer::UseShader(m_Shader);

		Kigu::Renderer::Submit(m_VertexArray);
		
		Kigu::Renderer::EndPass();
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
