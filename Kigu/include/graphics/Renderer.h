#pragma once

#include <glad/glad.h>

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

		static void Test();
	};
}
