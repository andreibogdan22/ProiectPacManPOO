#pragma once
#include <stack>
#include <memory>
#pragma once
#include "State.h"
class StateManager {
	std::stack<std::unique_ptr<State>> m_stateStack;
	std::unique_ptr<State> m_newState;

	bool m_add;
	bool m_replace;
	bool m_remove;
public:
	StateManager();
	~StateManager();

	void Add(std::unique_ptr<State> toAdd, bool replace = false);
	void PopCurrent();
	void ProcessStateChange();
	std::unique_ptr<State>& getCurrentState();
};