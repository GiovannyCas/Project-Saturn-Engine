#pragma once


#include <windows.h>



namespace Utility
{
	class TimerClass
	{

	private:
		INT64 m_frequency;
		float m_ticksPerMs;
		INT64 m_startTime;
		float m_frameTime;

	public:
		TimerClass();
		~TimerClass() = default;

		bool Initialize();
		void Frame();

		float GetTime();
	};
}

