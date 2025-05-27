#include "Game.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <string>
#include <typeinfo>
#include "MainMenu.h"

template<class T, class M>
class Log {
    Log() {}
    static Log s_instance;
    M m_counter = 0;
public:
    Log(const Log&) = delete;
    const Log& operator=(const Log&) = delete;
    void showOnConsole(T variable) {
        system("cls");
        std::cout << variable;
        if (typeid(m_counter) == typeid(int))
            m_counter++;
    }
    static Log& Get() {
        return s_instance;
    }
    int& GetCounter() {
        return m_counter;
    }
};

Log<std::string, int> Log<std::string, int>::s_instance;


Game::Game() {
    m_context = std::make_shared<Context>();
	m_context->m_window->create(sf::VideoMode({ 640, 320 }), "Pac Man", sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));

}

Game::~Game() {
    Log<std::string, int>::Get().showOnConsole("Program incheiat!");
}

void Game::Run() {
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;
    m_context->m_window->setFramerateLimit(60);
    while (m_context->m_window->isOpen())
    {
      if (timeSinceLastFrame <= TIME_PER_FRAME)
        timeSinceLastFrame += clock.restart();
        //while (timeSinceLastFrame > TIME_PER_FRAME) {
            timeSinceLastFrame -= TIME_PER_FRAME;
            m_context->m_states->ProcessStateChange();
            m_context->m_states->getCurrentState()->ProcessInput();
            m_context->m_states->getCurrentState()->Update(TIME_PER_FRAME);
            m_context->m_states->getCurrentState()->Draw();
            std::cout << Log<std::string, int>::Get().GetCounter();
            Log<std::string, int>::Get().showOnConsole(" cicluri");
        //}
    }
}