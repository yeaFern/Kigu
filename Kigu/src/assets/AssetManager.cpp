#include "assets/AssetManager.h"

namespace Kigu
{
	// 
	// Asset Type Definitions
	// 
	static EnumMap<AssetType, AssetFormatInfo> s_AssetFormats({
		{ AssetType::Unknown, {
			"Unknown",
			".???"
		} },
		{ AssetType::VertexShader, {
			"Vertex Shader",
			".vs"
		} },
		{ AssetType::FragmentShader, {
			"Fragment Shader",
			".fs"
		} },
		{ AssetType::TextFile, {
			"Text File",
			".txt"
		} }
	});

	// 
	// Asset List
	// Contains every recognized asset in the assets directory.
	// 
	static std::vector<AssetInfo> s_Assets;

	// 
	// Asset API
	// 
	void AssetManager::Initialize()
	{
		Assert(AssetDirectory[0] != '\0');

		// Create the asset directory if it does not exist.
		std::filesystem::path assetPath(AssetDirectory);
		if (!std::filesystem::exists(assetPath) || !std::filesystem::is_directory(assetPath))
		{
			std::filesystem::create_directories(assetPath);
		}

		// Iterate each entry in the asset directory.
		for (auto& entry : std::filesystem::recursive_directory_iterator(assetPath))
		{
			// If the entry is a file.
			if (std::filesystem::is_regular_file(entry))
			{
				// Get the path of the file.
				auto path = entry.path();
				
				// If we can deduce what type of asset this is.
				if (path.has_extension())
				{
					// Get the files extension.
					auto ext = path.extension();

					// Try and find a match for this extension in the asset format database.
					for (size_t i = 0; i < s_AssetFormats.Size(); i++)
					{
						// Probably a safe cast.
						auto type = static_cast<AssetType>(i);
						auto format = s_AssetFormats.Get(type);

						// If the extension matches.
						if (format.FileExtension == ext)
						{
							// Create the assets unique identifier.
							auto identifier = path.generic_string();

							// Add the asset to the list of known assets.
							s_Assets.emplace_back(type, identifier);
							break;
						}
					}
				}
			}
		}
	}

	AssetFormatInfo AssetManager::GetAssetTypeInfo(AssetType type)
	{
		return s_AssetFormats.Get(type);
	}

	std::vector<AssetInfo>::iterator AssetManager::Begin()
	{
		return s_Assets.begin();
	}

	std::vector<AssetInfo>::iterator AssetManager::End()
	{
		return s_Assets.end();
	}
}
