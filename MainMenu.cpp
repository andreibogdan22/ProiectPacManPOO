#include "MainMenu.h"
#include "SFML/Window/Event.hpp"
#include "GamePlay.h"
MainMenu::MainMenu(std::shared_ptr<Context>& context): m_context(context), m_isPlayButtonSelected(true), m_isPlayButtonPressed(false), m_isExitButtonPressed(false), m_isExitButtonSelected(false) {

}

MainMenu::~MainMenu() {

}

void MainMenu::init() {
	m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Pacifico-Regular.ttf");

	m_gameTitle = std::make_unique<sf::Text>(m_context->m_assets->GetFont(MAIN_FONT), "Pac Man");
	m_gameTitle->setOrigin(m_gameTitle->getLocalBounds().getCenter());
	m_gameTitle->setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 125.f));

	m_playButton = std::make_unique<sf::Text>(m_context->m_assets->GetFont(MAIN_FONT), "Play");
	m_playButton->setOrigin(m_playButton->getLocalBounds().getCenter());
	m_playButton->setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.f));
	m_playButton->setCharacterSize(20);

	m_exitButton = std::make_unique<sf::Text>(m_context->m_assets->GetFont(MAIN_FONT), "Exit");
	m_exitButton->setOrigin(m_exitButton->getLocalBounds().getCenter());
	m_exitButton->setPosition(sf::Vector2f(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.f));
	m_exitButton->setCharacterSize(20);
}

void MainMenu::ProcessInput() {
	while (const std::optional event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_context->m_window->close();
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			switch (keyPressed->scancode) {
			case sf::Keyboard::Scancode::Up:
			{
				if (!m_isPlayButtonSelected) {
					m_isPlayButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Scancode::Down:
			{
				if (!m_isExitButtonSelected) {
					m_isPlayButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			}
			case sf::Keyboard::Scancode::Enter:
			{
				m_isExitButtonPressed = false;
				m_isPlayButtonPressed = false;
				if (m_isPlayButtonSelected)
					m_isPlayButtonPressed = true;
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

void MainMenu::Update(sf::Time deltaTime) {
	if (m_isPlayButtonSelected) {
		m_playButton->setFillColor(sf::Color::Yellow);
		m_exitButton->setFillColor(sf::Color::White);
	}
	else {
		m_exitButton->setFillColor(sf::Color::Yellow);
		m_playButton->setFillColor(sf::Color::White);
	}
	
	if (m_isPlayButtonPressed) {
		m_context->m_states->Add(std::make_unique<GamePlay>(m_context));
	}
	else if (m_isExitButtonPressed) {
		m_context->m_window->close();
	}
}

void MainMenu::Draw() {
	m_context->m_window->clear();
	m_context->m_window->draw(*m_gameTitle);
	m_context->m_window->draw(*m_playButton);
	m_context->m_window->draw(*m_exitButton);
	m_context->m_window->display();
}
