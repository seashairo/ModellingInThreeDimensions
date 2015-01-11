#include "stdafx.h"
#include "State.h"

State::State(void) {
}

State::~State(void) {
}

Action* State::getAction() {
	return stateAction;
}

void State::setAction(Action *action) {
	stateAction = action;
}

Action* State::getEntryAction() {
	return entryAction;
}

void State::setEntryAction(Action *action) {
	entryAction = action;
}

Action* State::getExitAction() {
	return exitAction;
}

void State::setExitAction(Action *action) {
	exitAction = action;
}

std::list<Transition*>* State::getTransitions() {
	return &transitionList;
}

void State::addTransition(Transition *transition) {
	transitionList.push_front(transition);
}

/*
void State::removeTransition(Transition transition) {
	transitionList.remove(transition);
}
*/