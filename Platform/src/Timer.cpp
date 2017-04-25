#include "Platform/include/Platform.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

Platform::Timer	gTimer;

Platform::Timer::Timer()
	: mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
	mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	mSecondsPerCount = 1.0 / (double)mGetPerformanceFrequency();
}

auto Platform::Timer::TotalTime() const -> float
{
	if (mStopped)
	{
		return (float)(((mStopTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	}

	return (float)(((mCurrTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
}

auto Platform::Timer::Reset() -> void
{
	mBaseTime = mGetPerformanceCounter();
	mPrevTime = mBaseTime;
	mStopTime = 0;
	mStopped = false;
}

auto Platform::Timer::Start() -> void
{
	int64 startTime = mGetPerformanceCounter();

	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);

		mPrevTime = startTime;

		mStopTime = 0;
		mStopped = false;
	}
}

auto Platform::Timer::Stop() -> void
{
	if (!mStopped)
	{
		mStopTime = mGetPerformanceCounter();
		mStopped = true;
	}
}

auto Platform::Timer::Tick() -> void
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	mCurrTime = mGetPerformanceCounter();

	mDeltaTime = (mCurrTime - mPrevTime)*mSecondsPerCount;

	mPrevTime = mCurrTime;

	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}

#ifdef _WIN32

auto Platform::Timer::mGetPerformanceCounter() -> int64
{
	int64 counts;
	QueryPerformanceCounter((LARGE_INTEGER*)&counts);
	return counts;
}

auto Platform::Timer::mGetPerformanceFrequency() -> int64
{
	int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	return countsPerSec;
}

#elif __GNUC__

auto Platform::Timer::mGetPerformanceCounter() -> int64
{
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_nsec + ts.tv_sec * usec_per_sec;
}

auto Platform::Timer::mGetPerformanceFrequency() -> int64
{
	timespec ts;
	clock_getres(CLOCK_MONOTONIC, &ts);
	return ts.tv_nsec + ts.tv_sec * usec_per_sec;
}

#else

auto Platform::Timer::mGetPerformanceCounter() -> int64
{
	return 0;
}

auto Platform::Timer::mGetPerformanceFrequency() -> int64
{
	return 0
}

#endif