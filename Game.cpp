#include "Game.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "MainMenu.h"
Game::Game() {
    m_context = std::make_shared<Context>();
	m_context->m_window->create(sf::VideoMode({ 640, 320 }), "Pac Man", sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));

}

Game::~Game() {

}

void Game::Run() {
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();
        while (timeSinceLastFrame > TIME_PER_FRAME) {
            timeSinceLastFrame -= TIME_PER_FRAME;
            m_context->m_states->ProcessStateChange();
            m_context->m_states->getCurrentState()->ProcessInput();
            m_context->m_states->getCurrentState()->Update(TIME_PER_FRAME);
            m_context->m_states->getCurrentState()->Draw();
        }
    }
}