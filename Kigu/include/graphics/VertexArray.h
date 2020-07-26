#pragma once

#include <string>
#include <vector>
#include <initializer_list>
#include <glad/glad.h>

#include "util/EnumMap.h"

namespace Kigu
{
	enum class AttribType
	{
		Float1,
		Float2,
		Float3,
		Float4,
		_Last
	};

	struct AttribInfo
	{
		GLenum GLType;
		size_t ComponentCount;
		size_t ComponentSize;
	};

	static EnumMap<AttribType, AttribInfo> s_AttribFormats({
		{ AttribType::Float1, {
			GL_FLOAT, 1, 4
		} },
		{ AttribType::Float2, {
			GL_FLOAT, 2, 4
		} },
		{ AttribType::Float3, {
			GL_FLOAT, 3, 4
		} },
		{ AttribType::Float4, {
			GL_FLOAT, 4, 4
		} },
	});

	struct AttributeDescription
	{
		AttribType Type;
		std::string Name;
	};

	class VertexArray
	{
	private:
		GLuint m_Vao;
		GLuint m_Vbo;
		int m_VertexSize = 0;
		int m_VertexCount = 0;
	public:
		VertexArray();

		void Bind() const;

		template<typename T>
		void SetData(const std::vector<T>& data, int stride, const std::initializer_list<AttributeDescription>& attribs);

		void Render() const;
	};

	template<typename T>
	inline void VertexArray::SetData(const std::vector<T>& data, int stride, const std::initializer_list<AttributeDescription>& attribs)
	{
		// Stride is how many elements of T constitute a single vertex.
		// For example, if you are passing raw float positions, this would be 3.
		// But if you are supplying a custom struct, this would be 1.

		this->m_VertexSize = stride * sizeof(T);
		this->m_VertexCount = data.size() / stride;

		glGenBuffers(1, &m_Vbo);

		glBindVertexArray(m_Vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);

		int offset = 0;
		int attributeCount = 0;
		for (const auto& attrib : attribs)
		{
			AttribInfo info = s_AttribFormats.Get(attrib.Type);

			glEnableVertexAttribArray(attributeCount);
			glVertexAttribPointer(attributeCount, info.ComponentCount, info.GLType, GL_FALSE, m_VertexSize, (void*)offset);

			offset += info.ComponentSize * info.ComponentCount;
			attributeCount++;
		}
	}
}
