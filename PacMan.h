#pragma once
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
class PacMan {
	std::unique_ptr<sf::Sprite> m_body;
public:
	PacMan();
	~PacMan();

	void Init(const sf::Texture& texture);
	void Move(const sf::Vector2f& direction);
	bool IsOn(const sf::Sprite& other) const;
};