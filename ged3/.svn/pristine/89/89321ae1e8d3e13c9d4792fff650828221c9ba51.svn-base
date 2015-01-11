#include "Timer.h"

Timer::Timer(){

}

bool Timer::Initialize(){
	// Check if the timer will be suported.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if(m_frequency == 0)
	{
		return false;
	}

	// How often the timer ticks
	m_tps = (float)(m_frequency / 1000);

	// Get the start time in microseconds
	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	m_fps = 0;
	m_count = 0;
	m_startTimeFPS = timeGetTime();

	

	return true;
}

void Timer::Frame()
{
	TimerStuff();
	FPSStuff();

	return;
}

void Timer::TimerStuff(){
	INT64 currentTime;
	float timeDifference;

	// Get the current time.
	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	// Time elapsed since last update.
	timeDifference = (float)(currentTime - m_startTime);

	// How much time that really is.
	m_frameTime = timeDifference / m_tps;

	// Update startTime for the next frame.
	m_startTime = currentTime;
}

void Timer::FPSStuff(){
	m_count++;

	if(timeGetTime() >= (m_startTimeFPS + 1000))
	{
		m_fps = m_count;
		m_count = 0;
		
		m_startTimeFPS = timeGetTime();
	}
}

float Timer::GetTime()
{
	return m_frameTime;
}

int Timer::GetFPS(){
	return m_fps;
}