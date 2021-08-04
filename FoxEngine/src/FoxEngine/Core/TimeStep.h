#pragma once

namespace FoxEngine
{
	class TimeStep
	{
	private:
		float time;
	public:
		TimeStep(float time = 0.0f)
			: time(time)
		{

		}
		float getSeconds() const { return time; }
		float getMilliseconds() const { return time * 1000.0; }

		operator float()
		{
			return getMilliseconds();
		}
	};
}