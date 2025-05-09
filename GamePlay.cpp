#include "GamePlay.h"
#include "GameOver.h"
#include "PauseGame.h"
#include <memory>
#include <cstdlib>
#include <ctime>
class Random {
	Random() { srand(time(NULL)); }
	int IRandom(int number) {
		return rand() % number;
	}
public:
	Random(const Random&) = delete;
	const Random& operator=(const Random&) = delete;
	static int randomInteger(int number) {
		return Get().IRandom(number);
	}
	static Random& Get() {
		static Random s_instance;
		return s_instance;
	}
};

GamePlay::GamePlay(std::shared_ptr<Context>& context) : m_context(context), m_direction({16.f, 0.f}), m_elapsedTime(sf::Time::Zero) {

}

GamePlay::~GamePlay() {

}

void GamePlay::init() {
	m_context->m_assets->AddTexture(BLACK_SQUARE, "assets/textures/black_square.png", true);
	m_context->m_assets->AddTexture(FOOD, "assets/textures/food.png");
	m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png");
	m_context->m_assets->AddTexture(PACMAN, "assets/textures/hexagon-16.png");
	m_context->m_assets->AddTexture(BLUE_GHOST, "assets/textures/blue_hexagon.png");
	m_context->m_assets->AddTexture(PURPLE_GHOST, "assets/textures/purple_hexagon.png");
	m_context->m_assets->AddTexture(RED_GHOST, "assets/textures/red_hexagon.png");

	m_grass = std::make_unique<sf::Sprite>(m_context->m_assets->GetTexture(BLACK_SQUARE),
		m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	 int x = 0, y = 0;
	for (int i = 0; i < 20; i++) {
		x = 0;
		for (int j = 0; j < 40; j++) {
			if (m_map[i][j] == 1) {
				m_walls.push_back(sf::Sprite(m_context->m_assets->GetTexture(WALL),
					sf::IntRect({ 0, 0 }, { 16, 16 })));
				m_walls.back().setPosition({ float(x), float(y) });
			}
			else {
				m_foods.push_back(sf::Sprite(m_context->m_assets->GetTexture(FOOD),
					sf::IntRect({ 0, 0 }, { 16, 16 })));
				m_foods.back().setPosition({ float(x), float(y) });
			}
			x += 16;
		}
		y += 16;
	}
	//m_wall = std::make_unique<sf::Sprite>(m_context->m_assets->GetTexture(WALL), sf::IntRect({ 0, 0 }, { 16, 16 }));
	//m_food = std::make_unique<sf::Sprite>(m_context->m_assets->GetTexture(FOOD), sf::IntRect({ 0, 0 }, { 16, 16 }));

	m_pacMan.Init(m_context->m_assets->GetTexture(PACMAN));
	m_ghosts[0].Init(m_context->m_assets->GetTexture(RED_GHOST));
	m_ghosts[0].getSprite().setPosition({ 16 * 38, 16});
	m_ghosts[1].Init(m_context->m_assets->GetTexture(BLUE_GHOST));
	m_ghosts[1].getSprite().setPosition({16 * 38, 16 * 18});
	m_ghosts[2].Init(m_context->m_assets->GetTexture(PURPLE_GHOST));
	m_ghosts[2].getSprite().setPosition({16, 16 * 18});
}

void GamePlay::ProcessInput() {
	while (const std::optional event = m_context->m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_context->m_window->close();
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			switch (keyPressed->scancode) {
			case sf::Keyboard::Scancode::Up:
				m_direction = { 0.f, -16.f };
				/*m_pacMan.setY(m_pacMan.getY() - 1);
				if (m_map[m_pacMan.getY()][m_pacMan.getX()] == '#') {
					m_direction = { 0.f, 0.f };
					m_pacMan.setY(m_pacMan.getY() + 1);
				}*/
				break;
			case sf::Keyboard::Scancode::Down:
				m_direction = { 0.f, 16.f };
				/*m_pacMan.setY(m_pacMan.getY() + 1);
				if (m_map[m_pacMan.getY()][m_pacMan.getX()] == '#') {
					m_direction = { 0.f, 0.f };
					m_pacMan.setY(m_pacMan.getY() - 1);
				}*/
				break;
			case sf::Keyboard::Scancode::Left:
				m_direction = { -16.f, 0.f };
				/*m_pacMan.setX(m_pacMan.getX() - 1);
				if (m_map[m_pacMan.getY()][m_pacMan.getX()] == '#') {
					m_direction = { 0.f, 0.f };
					m_pacMan.setX(m_pacMan.getX() + 1);
				}*/
				break;
			case sf::Keyboard::Scancode::Right:
				m_direction = {16.f, 0.f};
				/*m_pacMan.setX(m_pacMan.getX() + 1);
				if (m_map[m_pacMan.getY()][m_pacMan.getX()] == '#') {
					m_direction = { 0.f, 0.f };
					m_pacMan.setX(m_pacMan.getX() - 1);
				}*/
				break;
			case sf::Keyboard::Scancode::Escape:
				m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
				break;
			}
		}
	}
	}

void GamePlay::Update(sf::Time deltaTime) {
	m_elapsedTime += deltaTime;
	if (m_elapsedTime.asSeconds() > 0.25) {
		static sf::Vector2f lastDirections[3];
		for (int i = 0; i < 3; i++) {
			lastDirections[i] = m_ghostsDirections[i];
				m_ghostsDirections[i] = m_directions[Random::randomInteger(4)];
				while (m_ghostsDirections[i] == -lastDirections[i])
					m_ghostsDirections[i] = m_directions[Random::randomInteger(4)];
			m_ghosts[i].Move(m_ghostsDirections[i]);
		}
		if (!m_foods.empty()) {
			for (int i = 0; i < m_foods.size(); i++)
				if (m_pacMan.isOn(m_foods[i]))
					m_foods.erase(m_foods.begin() + i);
			for (int i = 0; i < 3; i++)
				if (m_pacMan.isOn(m_ghosts[i].getSprite())) {
					m_context->m_states->Add(std::make_unique<GameOver>(m_context, "Game Over!"), true);
				}
			m_pacMan.Move(m_direction);
			for (int i = 0; i < m_walls.size(); i++) {
				if (m_pacMan.isOn(m_walls[i])) {
					m_pacMan.Move(-m_direction);
					m_direction = { 0, 0 };
				}
				for (int j = 0; j <= 2; j++)
					if (m_ghosts[j].isOn(m_walls[i])) {
						m_ghosts[j].Move(-m_ghostsDirections[j]);
						lastDirections[j] = -m_ghostsDirections[j];
					}
			}
		}
		else {
			m_context->m_states->Add(std::make_unique<GameOver>(m_context, "You Won!"), true);
		}
		m_elapsedTime = sf::Time::Zero;
	}
}

void GamePlay::Draw() {
	m_context->m_window->clear();
	m_context->m_window->draw(*m_grass);
	/*float x = 0, y = 0;
	m_wall->setPosition(sf::Vector2f(0, 0));
	m_food->setPosition(sf::Vector2f(0, 0));
	for (int i = 0; i < 20; i++) {
		x = 0;
		for (int j = 0; j < 40; j++) {
			if (m_map[i][j] == '#') {
				m_context->m_window->draw(*m_wall);
			}
			else if (m_map[i][j] == ' ')
				m_context->m_window->draw(*m_food);
			x += 16;
			if (x == 640)
				x -= 16;
			m_wall->setPosition(sf::Vector2f(x, y));
			m_food->setPosition(sf::Vector2f(x, y));
		}
		y += 16;
	}*/
	for (auto& wall : m_walls)
		m_context->m_window->draw(wall);
	for (auto& food : m_foods)
		m_context->m_window->draw(food);

	m_context->m_window->draw(m_pacMan);
	for (auto& ghost : m_ghosts)
		m_context->m_window->draw(ghost);
	m_context->m_window->display();
}

void GamePlay::Start() {

}

void GamePlay::Pause() {

}