//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#include "stdafx.h"
#include "Transition.h"

#include "State.h"

Transition::Transition(void) {
}

Transition::~Transition(void) {
}

bool Transition::IsTriggered() {
	return triggerCondition->Test();
}

State* Transition::GetTargetState() {
	return targetState;
}

Action* Transition::GetAction() {
	return action;
}
