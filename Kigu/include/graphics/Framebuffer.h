#pragma once

#include <memory>

#include <glad/glad.h>

namespace Kigu
{
	class Framebuffer
	{
	private:
		GLuint m_Handle = 0;
	public:
		inline GLuint GetHandle() const { return m_Handle; }
	public:
		static std::unique_ptr<Framebuffer> Create();
		static constexpr GLuint Default = 0;
	};

	using FramebufferPtr = std::unique_ptr<Framebuffer>;
}
