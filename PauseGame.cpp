#include "PauseGame.h"

PauseGame::PauseGame(std::shared_ptr<Context>& context) : m_context(context){

}

PauseGame::~PauseGame() {

}

void PauseGame::init() {
	m_pauseTitle = std::make_unique<sf::Text>(m_context->m_assets->GetFont(MAIN_FONT), "Pac Man");
	m_pauseTitle->setOrigin(m_pauseTitle->getLocalBounds().getCenter());
	m_pauseTitle->setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2));
}

void PauseGame::ProcessInput() {
	while (const std::optional event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_context->m_window->close();
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			switch (keyPressed->scancode) {
			case sf::Keyboard::Scancode::Escape:
			{
				m_context->m_states->PopCurrent();
				break;
			}
			default:
				break;
			}
		}
	}
}

void PauseGame::Update(sf::Time deltatime) {

}

void PauseGame::Draw() {
	m_context->m_window->draw(*m_pauseTitle);
	m_context->m_window->display();
}