#include "GamePlay.h"

GamePlay::GamePlay(std::shared_ptr<Context>& context) : m_context(context){

}

GamePlay::~GamePlay() {

}

void GamePlay::init() {
	m_context->m_assets->AddTexture(GRASS, "assets/textures/grass.png", true);
	m_context->m_assets->AddTexture(FOOD, "assets/textures/food.png");
	m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png");
	m_context->m_assets->AddTexture(PACMAN, "assets/textures/hexagon-16.png");
	

	m_grass = std::make_unique<sf::Sprite>(m_context->m_assets->GetTexture(GRASS),
		m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
	m_wall = std::make_unique<sf::Sprite>(m_context->m_assets->GetTexture(WALL), sf::IntRect({ 0, 0 }, { 16, 16 }));
	m_food = std::make_unique<sf::Sprite>(m_context->m_assets->GetTexture(FOOD), sf::IntRect({ 0, 0 }, { 16, 16 }));

}

void GamePlay::ProcessInput() {

}

void GamePlay::Update(sf::Time deltaTime) {

}

void GamePlay::Draw() {
	m_context->m_window->clear();
	m_context->m_window->draw(*m_grass);
	float x = 0, y = 0;
	for (int i = 0; i < 20; i++) {
		x = 0;
		for (int j = 0; j < 40; j++) {
			if (m_map[i][j] == '#')
				m_context->m_window->draw(*m_wall);
			x += 16;
			if (x == 640)
				x -= 16;
			m_wall->setPosition(sf::Vector2f(x, y));
		}
		y += 16;
	}
	m_context->m_window->display();
}

void GamePlay::Start() {

}

void GamePlay::Pause() {

}