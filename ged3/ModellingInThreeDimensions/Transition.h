//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#pragma once

class State;

// #include "State.h"
#include "ActionManager.h"
#include "Condition.h"

class Transition
{
public:
	Transition(void);
	~Transition(void);

	bool IsTriggered();
	State* GetTargetState();
	Action* GetAction();

	void SetTargetState(State* state) { targetState = state; };
	void SetTriggerConditon(Condition *condition) { triggerCondition = condition; };

private:
	Condition *triggerCondition;
	State *targetState;
	Action *action;
};