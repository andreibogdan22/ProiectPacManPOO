#pragma once
#include <SFML/System/Time.hpp>
class State {

public:
	State() {};
	virtual ~State() {};

	virtual void init() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Draw() = 0;

	virtual void Pause() {};
	virtual void Start() {};

};