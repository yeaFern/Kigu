#pragma once

#include <string>
#include <filesystem>
#include <fstream>

namespace Kigu
{
	class File
	{
	private:
		std::filesystem::path m_Path;
	public:
		File(const std::filesystem::path& path);

		bool Exists() const;
		size_t GetSize() const;
		std::filesystem::file_time_type GetLastWriteTime();

		bool Read(char* buffer, size_t bufferSize) const;
	};
}
