#pragma once


class Timer
{
public:
	Timer();
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	~Timer() = default;

	auto operator =(const Timer&) -> Timer& = delete;
	auto operator =(Timer&&) -> Timer& = delete;

	auto TotalTime() const -> float; // in seconds
	FORCEINLINE auto DeltaTime() const -> double // in seconds
	{
		return mDeltaTime;
	}

	auto	Reset() -> void;
	auto	Start() -> void;
	auto	Stop() -> void;
	auto	Tick() -> void;

private:
	auto	mGetPerformanceCounter()->int64;
	auto	mGetPerformanceFrequency()->int64;

	double mSecondsPerCount;
	double mDeltaTime;

	int64 mBaseTime;
	int64 mPausedTime;
	int64 mStopTime;
	int64 mPrevTime;
	int64 mCurrTime;

	bool mStopped;
};

extern Timer gTimer;
