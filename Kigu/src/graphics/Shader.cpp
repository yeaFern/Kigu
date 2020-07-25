#include "graphics/Shader.h"
#include "graphics/ShaderCache.h"

#include <iostream>

namespace Kigu
{
	Shader::Shader(const std::string name, const File& vertex, const File& fragment)
		: m_Name(name), m_Program(glCreateProgram())
	{
		if (!ShaderCache::IsCachingSupported())
		{
			LogFatal("Shader caching is not available.");
		}

		// Check if the shader needs to be recompiled.
		bool isCacheValid = true;
		if (ShaderCache::NeedsCompilation(m_Name, vertex  )) { isCacheValid = false; }
		if (ShaderCache::NeedsCompilation(m_Name, fragment)) { isCacheValid = false; }

		if (isCacheValid)
		{
			// If the cached binary is valid, load it.
			bool success = LoadFromBinary();

			// If the cached binary failed to link, recompile the shader.
			if (!success)
			{
				LogWarn("Shader cache failed to link, recompiling.");
				CompileAndSave(vertex, fragment);
			}
		}
		else
		{
			// If the shader cache is invalid, recompile the shader.
			LogInfo("Shader cache invalid, compiling.");
			CompileAndSave(vertex, fragment);
		}
	}

	GLint Shader::CompileShader(const File& source, ShaderType type)
	{
		if (!source.Exists())
		{
			LogFatal(source.GetPath() << " cannot be found.");
		}

		// Read the source file into a buffer.
		GLint size = static_cast<GLint>(source.GetSize());
		char* buffer = new char[size];
		source.Read(buffer, size);

		// Create the shader and pass it the source.
		GLuint id = glCreateShader(static_cast<GLenum>(type));
		glShaderSource(id, 1, &buffer, &size);

		// Compile and check for errors.
		glCompileShader(id);
		GLint success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(id, 1024, nullptr, infoLog);

			LogError("=====================================================");
			LogError(infoLog);
			LogError("== Caused by: " << source.GetFileName());
			LogError("== Failed to compile Shader =========================");
		}

		// Attach the shader and clean up.
		glAttachShader(m_Program, id);
		delete[] buffer;

		return id;
	}

	void Shader::CompileAndSave(const File& vertex, const File& fragment)
	{
		// Compile both shaders.
		GLuint v = CompileShader(vertex, ShaderType::Vertex);
		GLuint f = CompileShader(fragment, ShaderType::Fragment);

		// Link and check for errors.
		glLinkProgram(m_Program);
		GLint success = 0;
		GLchar errorLog[1024] = { 0 };
		glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
		if (success == 0)
		{
			glGetProgramInfoLog(m_Program, sizeof(errorLog), NULL, errorLog);

			LogError("=====================================================");
			LogError(errorLog);
			LogError("== Failed to link Shader ============================");
		}

		// Clean up the shaders.
		glDeleteShader(v);
		glDeleteShader(f);

		// Get the size of the binary.
		GLint binaryLength = 0;
		glGetProgramiv(m_Program, GL_PROGRAM_BINARY_LENGTH, &binaryLength);

		// Allocate space for it.
		char* binary = new char[binaryLength];

		// Get the binary from the driver, saving the format.
		GLenum binaryFormat;
		glGetProgramBinary(m_Program, binaryLength, nullptr, &binaryFormat, binary);

		// Write the binary to the cache.
		// TODO: Write the format too.
		ShaderCache::Write(m_Name, binary, binaryLength);

		// Clean up.
		delete[] binary;
	}

	bool Shader::LoadFromBinary()
	{
		// Get the binary file from the cache.
		File binary = ShaderCache::Get(m_Name);

		// Read it into a buffer.
		char* buffer = new char[binary.GetSize()];
		binary.Read(buffer, binary.GetSize());

		// Upload the binary.
		// TODO: Read the format from the binary.
		glProgramBinary(m_Program, 36894, buffer, binary.GetSize());

		// Clean up.
		delete[] buffer;

		// Check for success.
		GLint success = 0;
		glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
		return success;
	}

	ShaderPtr Shader::Create(const std::string& name, const File& vertex, const File& fragment)
	{
		return std::make_unique<Shader>(name, vertex, fragment);
	}
}
