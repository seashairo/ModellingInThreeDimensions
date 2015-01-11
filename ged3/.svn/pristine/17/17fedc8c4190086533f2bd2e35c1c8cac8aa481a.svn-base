//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#include "stdafx.h"
#include "ActionManager.h"

ActionManager::ActionManager(void) {
}

ActionManager::~ActionManager(void) {
}

void ActionManager::SceduleAction(Action *newAction) {
	pendingQueue.push_back(newAction);
}

bool ComparePriority( Action* a1, Action* a2 ) {
	if ( a1->GetPriority() < a2->GetPriority() ) {
		return true;
	}

	return false;
}

void ActionManager::Execute() {
	currentTime += 1;

	pendingQueue.sort(ComparePriority);
	activeQueue.sort(ComparePriority);

	if ( activeQueue.empty() ) {
		activeQueue = pendingQueue;
	}

	for ( std::list<Action*>::iterator action = pendingQueue.begin(); action != pendingQueue.end(); action++) {
		if ( activeQueue.empty() == false && (*action)->GetPriority() <= (*activeQueue.begin())->GetPriority() ) {
			break;
		}

		if ( (*action)->CanInterupt() ) {
			activeQueue.clear();
			activeQueue = pendingQueue;
			pendingQueue.clear();
		}
	}

	for ( std::list<Action*>::iterator action = pendingQueue.begin(); action != pendingQueue.end(); action++) {
		if ( (*action)->GetExpiryTime() < currentTime ) {
			action = pendingQueue.erase( action );
		}

		//TODO: Check if can be combined
		//If so do:
		//activeQueue.push_back(*action);
		//action = pendingQueue.erase(action);
	}

	for ( std::list<Action*>::iterator action = activeQueue.begin(); action != activeQueue.end(); action++) {
		if ( (*action)->IsComplete() ) {
			action = activeQueue.erase( action );
		} else {
			(*action)->Execute();
		}
	}
}