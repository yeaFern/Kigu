#pragma once

#include <glad/glad.h>

#include "graphics/Framebuffer.h"
#include "graphics/Shader.h"
#include "graphics/VertexArray.h"

namespace Kigu
{
	namespace ClearFlags
	{
		enum
		{
			Color = GL_COLOR_BUFFER_BIT,
			Depth = GL_DEPTH_BUFFER_BIT,
			Stencil = GL_STENCIL_BUFFER_BIT
		};
	}

	struct Renderer
	{
		static void Initialize();

		static void Clear(unsigned int flags = ClearFlags::Color | ClearFlags::Depth | ClearFlags::Stencil);

		static void BeginPass(const std::string& name);
		static void EndPass();

		static void UseFramebuffer(GLuint handle);
		static void UseFramebuffer(const FramebufferPtr& framebuffer);

		static void UseShader(const ShaderPtr& shader);

		static void Submit(VertexArray* mesh);
	};
}
