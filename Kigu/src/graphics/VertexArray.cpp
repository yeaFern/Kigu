#include "graphics/VertexArray.h"

namespace Kigu
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_Vao);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_VertexSize);
	}

	void VertexArray::Render() const
	{
		glBindVertexArray(m_Vao);
		glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
	}
}
