#pragma once

struct vec2
{
	float x;
	float y;

	vec2()
		: x(0), y(0)
	{
	}

	vec2(float x, float y)
		: x(x), y(y)
	{
	}

	vec2(const vec2& other)
		: x(other.x), y(other.y)
	{
	}

	vec2& operator+=(const vec2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	vec2& operator-=(const vec2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	vec2& operator*=(const vec2& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}

	vec2& operator/=(const vec2& rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		return *this;
	}

	vec2& operator*=(float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	vec2& operator/=(float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}

	friend vec2 operator+(vec2 lhs, const vec2& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	friend vec2 operator-(vec2 lhs, const vec2& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend vec2 operator*(vec2 lhs, const vec2& rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	friend vec2 operator/(vec2 lhs, const vec2& rhs)
	{
		lhs /= rhs;
		return lhs;
	}

	friend vec2 operator*(vec2 lhs, float rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	friend vec2 operator/(vec2 lhs, float rhs)
	{
		lhs *= rhs;
		return lhs;
	}
};

struct vec3
{
	float x;
	float y;
	float z;

	vec3()
		: x(0), y(0), z(0)
	{
	}

	vec3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}

	vec3(const vec3& other)
		: x(other.x), y(other.y), z(other.z)
	{
	}

	vec3(const vec2& v2, float z = 0.0f)
		: x(v2.x), y(v2.y), z(z)
	{
	}

	vec3& operator+=(const vec3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}

	vec3& operator-=(const vec3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}

	vec3& operator*=(const vec3& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		return *this;
	}

	vec3& operator/=(const vec3& rhs)
	{
		this->x /= rhs.x;
		this->y /= rhs.y;
		this->z /= rhs.z;
		return *this;
	}

	vec3& operator*=(float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		return *this;
	}

	vec3& operator/=(float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		return *this;
	}

	friend vec3 operator+(vec3 lhs, const vec3& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	friend vec3 operator-(vec3 lhs, const vec3& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	friend vec3 operator*(vec3 lhs, const vec3& rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	friend vec3 operator/(vec3 lhs, const vec3& rhs)
	{
		lhs /= rhs;
		return lhs;
	}

	friend vec3 operator*(vec3 lhs, float rhs)
	{
		lhs *= rhs;
		return lhs;
	}

	friend vec3 operator/(vec3 lhs, float rhs)
	{
		lhs *= rhs;
		return lhs;
	}
};

struct mat4
{
	using mat4_data = float[4 * 4];
	
	mat4_data elements = { 0 };

	mat4()
	{
		elements[0 + 0 * 4] = 1.0f;
		elements[1 + 1 * 4] = 1.0f;
		elements[2 + 2 * 4] = 1.0f;
		elements[3 + 3 * 4] = 1.0f;
	}

	mat4(const mat4& other)
	{
		std::memcpy(elements, other.elements, sizeof(mat4_data));
	}
};
