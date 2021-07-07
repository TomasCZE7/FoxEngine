#pragma once

namespace FoxEngine
{
	class TimeStep
	{
	private:
		float m_Time;
	public:
		TimeStep(float time = 0.0f)
			:m_Time(time)
		{

		}
		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0; }

		operator float()
		{
			return  m_Time;
		}
	};
}