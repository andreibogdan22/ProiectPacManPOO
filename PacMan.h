#pragma once
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
class PacMan : public sf::Drawable{
	std::unique_ptr<sf::Sprite> m_body;
public:
	PacMan();
	~PacMan();

	void Init(const sf::Texture& texture);
	void Move(const sf::Vector2f& direction);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool isOn(const sf::Sprite& other) const;
	sf::Sprite& getSprite() const;
};