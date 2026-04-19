#include "AssetManager.h"

namespace slot::gfx {
	void AssetManager::loadTexture(const std::string& key, const std::string& filepath)
	{
		sf::Texture texture(filepath);
		textures.try_emplace(key, std::move(texture));
	}

	const sf::Texture& AssetManager::getTexture(const std::string& key) const
	{
		return textures.at(key);
	}

	void AssetManager::loadFont(const std::string& key, const std::string& filepath)
	{
		sf::Font font(filepath);
		fonts.try_emplace(key, std::move(font));
	}

	const sf::Font& AssetManager::getFont(const std::string& key) const
	{
		return fonts.at(key);
	}
}