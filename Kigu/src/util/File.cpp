#include "util/File.h"

namespace Kigu
{
	File::File(const std::filesystem::path& path)
		: m_Path(path)
	{
	}

	std::filesystem::path File::GetPath() const
	{
		return m_Path;
	}

	bool File::Exists() const
	{
		return std::filesystem::exists(m_Path) && std::filesystem::is_regular_file(m_Path);
	}

	size_t File::GetSize() const
	{
		return std::filesystem::file_size(m_Path);
	}

	std::string File::GetFileName() const
	{
		return m_Path.filename().string();
	}

	std::filesystem::file_time_type File::GetLastWriteTime() const
	{
		return std::filesystem::last_write_time(m_Path);
	}

	bool File::Read(char* buffer, size_t bufferSize) const
	{
		if (Exists())
		{
			std::ifstream file(m_Path, std::ios::binary);
			file.read((char*)buffer, bufferSize);
			return true;
		}
		else
		{
			return false;
		}
	}

	void File::Write(char* buffer, size_t bufferSize) const
	{
		std::ofstream stream(m_Path, std::ios::binary);
		stream.write(buffer, bufferSize);
		stream.close();
	}
}
