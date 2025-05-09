#include "GameOver.h"
#include "GamePlay.h"
GameOver::GameOver(std::shared_ptr<Context>& context, std::string message) : m_context(context), m_message(message), m_isRetryButtonSelected(true), m_isRetryButtonPressed(false), m_isExitButtonPressed(false), m_isExitButtonSelected(false) {

}

GameOver::~GameOver() {

}

void GameOver::init() {

	m_gameOverTitle = std::make_unique<sf::Text>(m_context->m_assets->GetFont(MAIN_FONT), m_message);
	m_gameOverTitle->setOrigin(m_gameOverTitle->getLocalBounds().getCenter());
	m_gameOverTitle->setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 125.f));

	m_retryButton = std::make_unique<sf::Text>(m_context->m_assets->GetFont(MAIN_FONT), "Retry");
	m_retryButton->setOrigin(m_retryButton->getLocalBounds().getCenter());
	m_retryButton->setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.f));
	m_retryButton->setCharacterSize(20);

	m_exitButton = std::make_unique<sf::Text>(m_context->m_assets->GetFont(MAIN_FONT), "Exit");
	m_exitButton->setOrigin(m_exitButton->getLocalBounds().getCenter());
	m_exitButton->setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.f));
	m_exitButton->setCharacterSize(20);
}

void GameOver::ProcessInput() {
	while (const std::optional event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_context->m_window->close();
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			switch (keyPressed->scancode) {
			case sf::Keyboard::Scancode::Up:
			{
				if (!m_isRetryButtonSelected) {
					m_isRetryButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Scancode::Down:
			{
				if (!m_isExitButtonSelected) {
					m_isRetryButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			}
			case sf::Keyboard::Scancode::Enter:
			{
				m_isExitButtonPressed = false;
				m_isRetryButtonPressed = false;
				if (m_isRetryButtonSelected)
					m_isRetryButtonPressed = true;
				else if (m_isExitButtonSelected)
					m_isExitButtonPressed = true;
				break;
			}
			default:
				break;
			}
		}
	}
}

void GameOver::Update(sf::Time deltaTime) {
	if (m_isRetryButtonSelected) {
		m_retryButton->setFillColor(sf::Color::Yellow);
		m_exitButton->setFillColor(sf::Color::White);
	}
	else {
		m_exitButton->setFillColor(sf::Color::Yellow);
		m_retryButton->setFillColor(sf::Color::White);
	}

	if (m_isRetryButtonPressed) {
		m_context->m_states->Add(std::make_unique<GamePlay>(m_context));
	}
	else if (m_isExitButtonPressed) {
		m_context->m_window->close();
	}
}

void GameOver::Draw() {
	m_context->m_window->clear();
	m_context->m_window->draw(*m_gameOverTitle);
	m_context->m_window->draw(*m_retryButton);
	m_context->m_window->draw(*m_exitButton);
	m_context->m_window->display();
}