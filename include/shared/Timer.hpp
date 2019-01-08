//
// EPITECH PROJECT, 2018
// Timer
// File description:
// Timer
//

#pragma once

#include <chrono>
#include <functional>

template <typename DefaultDuration = std::chrono::milliseconds>
class Timer {

		/*USING*/
	private:
		using high_clock_t = std::chrono::high_resolution_clock;

		/*PROPERTIES*/
	private:
		std::chrono::time_point<high_clock_t> _startTime;

		/*CONSTRUCTORS*/
	public:
		Timer() noexcept : _startTime(high_clock_t::now()) {};
		~Timer() noexcept = default;

		/*COPLIEN*/
		Timer(const Timer &) noexcept = default;
		Timer &operator=(const Timer&) noexcept = default;

		/*MOVE*/
		Timer(Timer&&) noexcept = default;
		Timer &operator=(Timer&&) noexcept = default;

		/*METHODS*/
	public:
		void reset() noexcept {_startTime = high_clock_t::now();}

		template <typename Duration = DefaultDuration>
		long elapsedTime() {return std::chrono::duration_cast<Duration> (high_clock_t::now() - _startTime).count();}

		template <typename Duration = DefaultDuration>
		bool isElapsedExceeding(long amount) {return this->elapsedTime<Duration>() > amount;}

		template<typename Duration = DefaultDuration, typename Func, typename ...Args>
		static long executionTime(Func&& func, Args&&... args)
		{
			Timer timer;

			std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
			return timer.elapsedTime<Duration>();
		};

		static double milliToSec(long ms)
		{
			return (double)ms / (double)1000;
		}
};
