#ifndef _PLAYERCLASS_H_
#define _PLAYERCLASS_H_

#include "EntityClass.h"
#include "InputClass.h"

class PlayerClass : public EntityClass
{
	public:
		PlayerClass();
		void SetInput(InputClass*);
		void InputControl();
	private:
		void TransformModel();

	private:
		InputClass* m_input;

		//hold button
		bool m_holdLeft;
		bool m_holdRight;
		bool m_holdUp;
		bool m_holdDown;
		bool m_holdBigger;
		bool m_holdSmaller;

		//
};
#endif