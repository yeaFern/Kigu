#pragma once

#include <iostream>
#include <filesystem>
#include <string_view>
#include <vector>

#include "util/Log.h"
#include "util/EnumMap.h"

namespace Kigu
{
	enum class AssetType
	{
		Unknown,
		VertexShader,
		FragmentShader,
		TextFile,
		_Last
	};

	struct AssetInfo
	{
		const AssetType Type;
		const std::string Identifier;

		AssetInfo(AssetType type, const std::string& identifier)
			: Type(type), Identifier(identifier)
		{
		}
	};

	struct AssetFormatInfo
	{
		std::string_view Name;
		std::string_view FileExtension;
	};

	struct AssetManager
	{
		static constexpr auto AssetDirectory = "Data";

		static void Initialize();
		static AssetFormatInfo GetAssetTypeInfo(AssetType type);

		static std::vector<AssetInfo>::iterator Begin();
		static std::vector<AssetInfo>::iterator End();
	};
}
