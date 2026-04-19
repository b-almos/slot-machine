#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

namespace slot::gfx {
	class AssetManager {
	private:
		std::unordered_map<std::string, sf::Texture> textures;
		std::unordered_map<std::string, sf::Font> fonts;
	public:
		void loadTexture(const std::string& key, const std::string& filepath);
		const sf::Texture& getTexture(const std::string& key) const;

		void loadFont(const std::string& key, const std::string& filepath);
		const sf::Font& getFont(const std::string& key) const;
	};
}