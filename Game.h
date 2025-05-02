#pragma once
#include "AssetManager.h"
#include "StateManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

struct Context {
	std::unique_ptr<AssetManager> m_assets;
	std::unique_ptr<StateManager> m_states;
	std::unique_ptr<sf::RenderWindow> m_window;

	Context() {
		m_assets = std::make_unique<AssetManager>();
		m_states = std::make_unique<StateManager>();
		m_window = std::make_unique<sf::RenderWindow>();
	}
};

enum AssetID {
	MAIN_FONT = 0,
	GRASS,
	FOOD,
	WALL,
	PACMAN
};

class Game {
	std::shared_ptr<Context> m_context;
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
public:
	Game();
	~Game();

	void Run();
};