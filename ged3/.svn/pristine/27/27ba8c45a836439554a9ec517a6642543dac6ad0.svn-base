//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#include "stdafx.h"
#include "Condition.h"

Condition::Condition(void) {
}

Condition::~Condition(void) {
}

bool Condition::Test() {
	return *testBool;
}

void Condition::SetBool(bool *value) {
	testBool = value;
}


FloatCondition::FloatCondition(void) {
}

FloatCondition::~FloatCondition(void) {
}

bool FloatCondition::Test() {
	if (*minValue <= *testValue && *testValue <= *maxValue) {
		return true;	
	} else {
		return false;
	}
}

void FloatCondition::SetValues(float* min, float* max, float* test) {
	minValue = min;
	maxValue = max;
	testValue = test;
}

void FloatCondition::SetMinValue(float* value) {
	minValue = value;
}

void FloatCondition::SetMaxValue(float* value) {
	maxValue = value;
}

void FloatCondition::SetTestValue(float* value) {
	testValue = value;
}



AndCondition::AndCondition(void) {
}

AndCondition::~AndCondition(void) {
}

bool AndCondition::Test() {
	return (conditionA.Test() && conditionB.Test());
}



NotCondition::NotCondition(void) {
}

NotCondition::~NotCondition(void) {
}

bool NotCondition::Test() {
	return (!condition.Test());
}



OrCondition::OrCondition(void) {
}

OrCondition::~OrCondition(void) {
}

bool OrCondition::Test() {
	return (conditionA.Test() || conditionB.Test());
}