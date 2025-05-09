#pragma once
#include "State.h"
#include "Game.h"
#include "SFML/Graphics/Text.hpp"
#include <memory>
class PauseGame : public State {
	std::shared_ptr<Context> m_context;
	std::unique_ptr<sf::Text> m_pauseTitle;

public:
	PauseGame(std::shared_ptr<Context>& context);
	~PauseGame();

	void init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};