#pragma once
#include "State.h"
#include "Game.h"
#include <SFML/Graphics/Text.hpp>
class GameOver : public State {
	std::string m_message;
	std::shared_ptr<Context> m_context;
	std::unique_ptr<sf::Text> m_gameOverTitle;
	std::unique_ptr<sf::Text> m_retryButton;
	std::unique_ptr<sf::Text> m_exitButton;

	bool m_isRetryButtonSelected;
	bool m_isRetryButtonPressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;
public:
	GameOver(std::shared_ptr<Context>& context, std::string message);
	~GameOver();

	void init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};