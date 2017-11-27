#ifndef STIMER_H
#define STIMER_H

#define timer STimer::GetInstance()

class STimer
{
private:
	struct Timer
	{
		HSQOBJECT function;
		HSQOBJECT data;
		unsigned intervalTime, endTime;
		bool repeat, killed;

		Timer() {}
		Timer(HSQOBJECT &function, unsigned time, bool repeat, HSQOBJECT &data) :
			function(function),
			intervalTime(time),
			endTime(GetTimeMS() + time),
			repeat(repeat),
			data(data),
			killed(false)
		{}
	};

	STimer();

	void Pulse();

	std::map<unsigned, Timer> timers;
	std::queue<unsigned> freeID, removeTimers;

	unsigned lastID;

public:
	static STimer & GetInstance()
	{
		static STimer stimer;
		return stimer;
	}

	int Add(HSQOBJECT &function, unsigned time, bool repeat, HSQOBJECT &data);
	void Remove(unsigned id);
	void SetInterval(unsigned id, unsigned interval);
	void SetRepeat(unsigned id, bool repeat);
	void SetData(unsigned id, HSQOBJECT &data);

	friend class SScript;
};

#endif //STIMER_H