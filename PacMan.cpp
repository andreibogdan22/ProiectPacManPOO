#include "PacMan.h"

PacMan::PacMan(){

}

PacMan::~PacMan() {

}

void PacMan::Init(const sf::Texture& texture) {
	m_body = std::make_unique<sf::Sprite>(texture);
	m_body->setPosition({ 16, 16 });
}

void PacMan::Move(const sf::Vector2f& direction) {
	m_body->setPosition(m_body->getPosition() + direction);
}  

void PacMan::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*m_body);
}

bool PacMan::isOn(const sf::Sprite& other) const {
	return other.getGlobalBounds() == m_body->getGlobalBounds();
}

sf::Sprite& PacMan::getSprite() const {
	return *m_body;
}
