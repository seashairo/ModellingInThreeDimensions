//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#pragma once

#include <list>

#include "State.h"
#include "ActionManager.h"

class StateMachine
{
public:
	StateMachine(void);
	~StateMachine(void);

	void Initialize(ActionManager* actionManagerPtr);

	void AddState(State *newState);
	void SetInitialState(State *initState);
	//void RemoveState(State newState);

	void Update();

private:
	std::list<State*> states;
	State *initialState, *currentState;

	ActionManager* actionManager;

	float timer;
};