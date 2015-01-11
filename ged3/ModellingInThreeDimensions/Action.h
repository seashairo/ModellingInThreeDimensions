//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

////////////////////////////////////////////////////////////////////////////////
// Filename: Action.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <list>
#include <functional>

////////////////////////////////////////////////////////////////////////////////
// Class name: ActionClass
////////////////////////////////////////////////////////////////////////////////
class Action
{
public:
	Action(void);
	~Action(void);

	void Initialize();

	void SetExpiryTime(float time){ expiryTime = time; };
	float GetExpiryTime(){ return expiryTime; };

	void SetPriority(int value){ priority = value; };
	int GetPriority(){ return priority; };

	void SetCanInterupt(bool value){ canInterupt = value; };
	bool CanInterupt(){ return canInterupt; };

	void SetFunction(std::function<void ()> pFunction){ functionToCall = pFunction; };

	void AddConcurrentableAction( Action *action);
	bool CanDoBoth(Action *otherAction);

	void completeAction(){ isComplete = true; };
	bool IsComplete(){ return isComplete; };

	void Execute();

private:
	std::function<void ()> functionToCall;

	float expiryTime;
	int priority;

	bool canInterupt;
	bool isComplete;

	std::list<Action*> possibleConcurrentActions;
};

