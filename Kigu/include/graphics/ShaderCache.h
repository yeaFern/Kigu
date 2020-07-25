#pragma once

#include <glad/glad.h>

#include "util/File.h"
#include "util/Log.h"

namespace Kigu
{
	class ShaderCache
	{
	public:
		static constexpr auto ShaderCachePath = "Data/ShaderCache/";

		static bool IsCachingSupported();

		static bool NeedsCompilation(const std::string& shaderName, const File& source);

		static File Get(const std::string& shaderName);
		static void Write(const std::string& shaderName, char* buffer, size_t length);
	};
}
