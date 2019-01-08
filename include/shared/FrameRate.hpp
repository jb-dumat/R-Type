/*
** rtype
** Created on 21/11/18.
*/

#pragma once

#include <iostream>
#include "Timer.hpp"

class FrameRate
{
	private:
		Timer<std::chrono::milliseconds> __timer;
		unsigned int __fps;  // Frames Per Second

	public:
		FrameRate(unsigned int fps = 30) : __fps(fps) {};

		bool canUpdateFrame()
		{
			return (this->elapsedSeconds() > (double)1 / (double)__fps);
		}

		double elapsedSeconds()
		{
			return Timer<>::milliToSec(__timer.elapsedTime());
		}

		void reset()
		{
			__timer.reset();
		}

		void setFPS(unsigned int fps)
		{
			__fps = fps;
		}
};
