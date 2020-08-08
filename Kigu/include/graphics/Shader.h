#pragma once

#include <memory>

#include <glad/glad.h>

#include "util/File.h"
#include "util/Log.h"

namespace Kigu
{
	enum class ShaderType : GLenum
	{
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};

	class Shader
	{
	private:
		std::string m_Name;

		GLuint m_Program;
	public:
		Shader(
			const std::string name,
			const File& vertex,
			const File& fragment
		);

		inline GLuint GetProgram() const { return m_Program; }
	private:
		GLint CompileShader(const File& source, ShaderType type);

		void CompileAndSave(const File& vertex, const File& fragment);
		bool LoadFromBinary();
	public:
		static std::unique_ptr<Shader> Create(const std::string& name, const File& vertex, const File& fragment);
	};

	using ShaderPtr = std::unique_ptr<Shader>;
}
