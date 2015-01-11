//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#pragma once

#include <list>

#include "Action.h"

class ActionManager
{
public:
	ActionManager(void);
	~ActionManager(void);

	void SceduleAction(Action *newAction);
	void Execute();

private:
	std::list<Action*> pendingQueue;
	std::list<Action*> activeQueue;

	float currentTime;
};