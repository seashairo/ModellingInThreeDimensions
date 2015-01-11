//Derived from pseudo code from AI For Games 2nd Edition - Millington, Funge

#pragma once
class Condition
{
public:
	Condition(void);
	~Condition(void);

	virtual bool Test();

	void SetBool(bool* value);

private:
	bool *testBool;
};

class FloatCondition : public Condition {
public:
	FloatCondition(void);
	~FloatCondition(void);

	bool Test();

	void SetValues(float* min, float* max, float* test);
	void SetMinValue(float* value);
	void SetMaxValue(float* value);
	void SetTestValue(float* value);

private:
	float *minValue, *maxValue, *testValue;
};

class AndCondition : public Condition {
public:
	AndCondition(void);
	~AndCondition(void);

	void Initialize(Condition a, Condition b);
	bool Test();

private:
	Condition conditionA, conditionB;
};

class NotCondition : public Condition {
public:
	NotCondition(void);
	~NotCondition(void);

	void Initialize(Condition a);
	bool Test();

private:
	Condition condition;
};

class OrCondition : public Condition {
public:
	OrCondition(void);
	~OrCondition(void);

	void Initialize(Condition a, Condition b);

	bool Test();

private:
	Condition conditionA, conditionB;
};