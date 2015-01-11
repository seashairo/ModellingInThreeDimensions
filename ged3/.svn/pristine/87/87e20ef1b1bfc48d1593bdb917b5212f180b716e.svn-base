//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#pragma once

#include <list>

#include "ActionManager.h"
#include "Transition.h"

class State
{
public:
	State(void);
	~State(void);

	Action* getAction();
	void setAction(Action *action);

	Action* getEntryAction();
	void setEntryAction(Action *action);

	Action* getExitAction();
	void setExitAction(Action *action);

	std::list<Transition*>* getTransitions();
	void addTransition(Transition *transition);
	//void removeTransition(Transition transition);

	std::string name;

private:
	Action *stateAction, *entryAction, *exitAction;

	std::list<Transition*> transitionList;
};