#include "graphics/Renderer.h"

namespace Kigu
{
	void Renderer::Initialize()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::Clear(unsigned int flags)
	{
		glClear(flags);
	}

	void Renderer::BeginPass(const std::string& name)
	{

	}

	void Renderer::EndPass()
	{

	}

	void Renderer::UseFramebuffer(GLuint handle)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, handle);
	}

	void Renderer::UseFramebuffer(const FramebufferPtr& framebuffer)
	{
		UseFramebuffer(framebuffer->GetHandle());
	}

	void Renderer::UseShader(const ShaderPtr& shader)
	{
		glUseProgram(shader->GetProgram());
	}
	
	void Renderer::Submit(VertexArray* mesh)
	{
		mesh->Bind();
		mesh->Render();
	}
}
