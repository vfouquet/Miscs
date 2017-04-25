#pragma once



class Event
{
public:
	enum EType
	{
		NONE,
		UNKNOWN,
		WINDOW_RESIZED,
		WINDOW_FOCUS,
		WINDOW_LOSTFOCUS,
		WINDOW_CLOSE
	};

	Event() = default;
	Event(const Event&) = delete;
	Event(Event&&) = delete;
	~Event() = default;

	auto operator =(const Event&) -> Event& = delete;
	auto operator =(Event&&) -> Event& = delete;

	auto	Type() const -> EType { return mType; }

	static auto	GetEvent(Event& event) -> bool;


private:
	EType	mType;
};

