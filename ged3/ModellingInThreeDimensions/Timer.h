#ifndef _TIMER_H_
#define _TIMER_H_

// Includes
#include <Windows.h>

// Class
class Timer{
public:
	Timer();

	bool Initialize();
	void Frame();

	float GetTime();
	int GetFPS();

private:
	void TimerStuff();
	void FPSStuff();

private:
	INT64 m_frequency, m_startTime;
	float m_tps, m_frameTime;
	int m_fps, m_count;
	unsigned long m_startTimeFPS;
};

#endif