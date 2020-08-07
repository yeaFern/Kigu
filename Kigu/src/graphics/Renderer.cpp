#include "graphics/Renderer.h"

namespace Kigu
{
	static VertexArray* s_VertexArray;

	void Renderer::Initialize()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	
		struct Vertex
		{
			float x, y, z;
		};

		s_VertexArray = new VertexArray;
		s_VertexArray->SetData(std::vector<Vertex> {
			{ 0.0f,  0.5f, 0.0f},
			{-0.5f, -0.5f, 0.0f},
			{ 0.5f, -0.5f, 0.0f}
		}, 1, {
			{ AttribType::Float3, "v_Position" }
		});
	}

	void Renderer::Clear(unsigned int flags)
	{
		glClear(flags);
	}

	void Renderer::Test()
	{
		s_VertexArray->Bind();
		s_VertexArray->Render();
	}
}
