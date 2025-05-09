#include "AssetManager.h"
AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}

void AssetManager::AddTexture(int id, const std::string& filePath, bool isRepeated) {
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	if (texture->loadFromFile(filePath)) {
		texture->setRepeated(isRepeated);
		m_textures[id] = std::move(texture);
	}
}

void AssetManager::AddFont(int id, const std::string& filePath) {
	std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
	if (font->openFromFile(filePath)) {
		m_fonts[id] = std::move(font);
	}
}

const sf::Font& AssetManager::GetFont(int id) const {
	return *(m_fonts.at(id).get());
}

const sf::Texture& AssetManager::GetTexture(int id) const {
	return *(m_textures.at(id).get());
}
