#include "graphics/ShaderCache.h"

#include <iostream>

namespace Kigu
{
	bool ShaderCache::IsCachingSupported()
	{
		// Shader caching is only available on GPUs which support at least one binary format.
		GLint formats;
		glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
		return formats > 0;
	}

	bool ShaderCache::NeedsCompilation(const std::string& shaderName, const File& source)
	{
		// A shader needs compilation if either;
		//  - It does not exist in the shader cache.
		//  - The cached binary is older than the source file.

		std::filesystem::path cache(ShaderCachePath);
		if (!std::filesystem::exists(cache) || !std::filesystem::is_directory(cache))
		{
			// If the shader cache doesn't exist at all, create it.
			std::filesystem::create_directories(cache);

			// We can also guarantee that the cache is empty, and thus, the shader should be compiled.
			return true;
		}

		File binary(ShaderCachePath + shaderName + ".bin");
		if (!binary.Exists())
		{
			// If the binary does not exist, the shader needs to be compiled.
			return true;
		}

		if (binary.GetLastWriteTime() < source.GetLastWriteTime())
		{
			// If the binary is out of date, the shader needs to be compiled.
			return true;
		}

		return false;
	}

	File ShaderCache::Get(const std::string& shaderName)
	{
		std::filesystem::path cache(ShaderCachePath);
		if (!std::filesystem::exists(cache) || !std::filesystem::is_directory(cache))
		{
			// If the shader cache doesn't exist at all, create it.
			std::filesystem::create_directories(cache);
			
			// Throw an error as the binary does not exist.
			LogError("Shader binary does not exist for shader '" << shaderName << "'.");
		}

		File binary(ShaderCachePath + shaderName + ".bin");
		if (!binary.Exists())
		{
			// Throw an error as the binary does not exist.
			LogError("Shader binary does not exist for shader '" << shaderName << "'.");
		}

		return binary;
	}

	void ShaderCache::Write(const std::string& shaderName, char* buffer, size_t length)
	{
		std::filesystem::path cache(ShaderCachePath);
		if (!std::filesystem::exists(cache) || !std::filesystem::is_directory(cache))
		{
			// If the shader cache doesn't exist at all, create it.
			std::filesystem::create_directories(cache);
		}

		// Write the binary.
		File binary(ShaderCachePath + shaderName + ".bin");
		binary.Write(buffer, length);
	}
}
