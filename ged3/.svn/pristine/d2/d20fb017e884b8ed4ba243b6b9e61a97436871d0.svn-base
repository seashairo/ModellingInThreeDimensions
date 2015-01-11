//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#include "stdafx.h"
#include "Action.h"

Action::Action(void) {
	isComplete = false;
}

Action::~Action(void) {
}

void Action::Initialize() {
}

void Action::AddConcurrentableAction(Action *action) {
	possibleConcurrentActions.push_back(action);
}

bool Action::CanDoBoth(Action *otherAction) {
	for ( std::list<Action*>::iterator action = possibleConcurrentActions.begin(); action != possibleConcurrentActions.end(); action++ ) {
		if ( *action == otherAction ) {
			return true;
		}
	}

	return false;
}

void Action::Execute() {
	functionToCall();
}