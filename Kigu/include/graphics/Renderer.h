#pragma once

#include <glad/glad.h>

#include "graphics/VertexArray.h"

namespace Kigu
{
	struct Renderer
	{
		static void Initialize();

		static void Clear();

		static void Test();
	};
}
