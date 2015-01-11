//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#include "stdafx.h"
#include "StateMachine.h"

StateMachine::StateMachine(void) {
}

StateMachine::~StateMachine(void) {
}

void StateMachine::Initialize(ActionManager* actionManagerPtr) {
	actionManager = actionManagerPtr;
	currentState = initialState;

	timer = 60;
}

void StateMachine::AddState(State *newState) {
	states.push_back(newState);
}

void StateMachine::SetInitialState(State* initState) {
	initialState = initState;
}

void StateMachine::Update() {
	Transition triggeredTransition;
	bool aTransitionHasTriggered = false;

	std::list<Transition*>::iterator it = currentState->getTransitions()->begin();

	for ( it; it != currentState->getTransitions()->end(); it++ ) {
		if ( (*it)->IsTriggered() ) {
			triggeredTransition = (**it);
			aTransitionHasTriggered = true;
			break;
		}
	}

	if ( aTransitionHasTriggered ) {
		State* targetState = triggeredTransition.GetTargetState();

		//actionManager->SceduleAction(currentState->getExitAction());
		//actionManager->SceduleAction(triggeredTransition.GetAction());
		//actionManager->SceduleAction(targetState->getEntryAction());

		//Log::COut("Transition has occured from " + currentState->name + " to " + targetState->name);

		if (currentState->getExitAction() != NULL) {
			//currentState->getExitAction()->Execute();
		}
		
		//targetState->getEntryAction()->Execute();

		currentState = targetState;
	} else {
		//actionManager->SceduleAction(currentState->getAction());

		if (currentState->getAction() != NULL) {
			//currentState->getAction()->Execute();
		}

		if ( timer <= 0 ) {
			timer = 60;
			//Log::COut("Currently in: " + currentState->name);
		}

		timer--;
	}
}