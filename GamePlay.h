#pragma once
#include "State.h"
#include "Game.h"
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
class GamePlay : public State {
	std::shared_ptr<Context> m_context;
	std::unique_ptr<sf::Sprite> m_grass;
	std::unique_ptr<sf::Sprite> m_food;
	std::unique_ptr<sf::Sprite> m_wall;
	std::array<std::string, 20> m_map = {
		"                                        ",
		"                                        ",
		"                                        ",
		"                                        ",
		"                           #            ",
		"           #                            ",
		"                                        ",
		"                                        ",
		"                                        ",
		"                                        ",
		"                         #              ",
		"                                        ",
		"                                        ",
		"                                        ",
		"                 #  ##                  ",
		"                                        ",
		"                                        ",
		"                                        ",
		"                                        ",
		"                                        "
	};

public:
	GamePlay(std::shared_ptr<Context>& m_context);
	~GamePlay();

	void init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
	void Start();
	void Pause();
};