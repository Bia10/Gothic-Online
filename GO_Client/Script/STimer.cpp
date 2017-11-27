#include "../stdafx.h"

STimer::STimer() :
	lastID(0)
{
}

void STimer::Pulse()
{
	HSQUIRRELVM vm = scr.GetVM();

	// Removing timers
	while (!removeTimers.empty())
	{
		sq_release(vm, &timers[removeTimers.front()].function);
		sq_release(vm, &timers[removeTimers.front()].data);
		timers.erase(removeTimers.front());
		removeTimers.pop();
	}

	for (std::map<unsigned, Timer>::iterator it = timers.begin(); it != timers.end(); ++it)
		if (GetTimeMS() >= it->second.endTime)
		{
			SQInteger topStackSize = sq_gettop(vm);
			sq_pushobject(vm, it->second.function);
			sq_pushroottable(vm);

			switch (it->second.data._type)
			{
			case OT_INTEGER:
				sq_pushinteger(vm, sq_objtointeger(&it->second.data));
				sq_call(vm, 2, SQFalse, SQTrue);
				break;
			case OT_FLOAT:
				sq_pushfloat (vm, sq_objtofloat(&it->second.data));
				sq_call(vm, 2, SQFalse, SQTrue);
				break;
			case OT_STRING:
				sq_pushstring(vm, sq_objtostring(&it->second.data), -1);
				sq_call(vm, 2, SQFalse, SQTrue);
				break;
			case OT_TABLE:
			case OT_ARRAY:
			case OT_CLOSURE:
			case OT_NATIVECLOSURE:
			case OT_GENERATOR:
			case OT_INSTANCE:
			case OT_WEAKREF:
			case OT_CLASS:
			case OT_THREAD:
				sq_pushobject(vm, it->second.data);
				sq_call(vm, 2, SQFalse, SQTrue);
			case OT_USERDATA:
			case OT_USERPOINTER:
				sq_pushuserpointer(vm, sq_objtouserpointer(&it->second.data));
				sq_call(vm, 2, SQFalse, SQTrue);
				break;
			case OT_NULL:
				sq_call(vm, 1, SQFalse, SQTrue);
				break;
			}

			sq_settop(vm, topStackSize);
			
			if (it->second.repeat) it->second.endTime = GetTimeMS() + it->second.intervalTime;
			else
			{
				removeTimers.push(it->first);
				freeID.push(removeTimers.front());
			}
		}
}

int STimer::Add(HSQOBJECT &function, unsigned time, bool repeat, HSQOBJECT &data)
{
	if (!freeID.empty())
	{
		unsigned id = freeID.front();
		freeID.pop();

		timers.insert(std::pair<unsigned, Timer>(id, Timer(function, time, repeat, data)));

		return id;
	}
	else
		timers.insert(std::pair<unsigned, Timer>(lastID, Timer(function, time, repeat, data)));

	return lastID++;
}

void STimer::Remove(unsigned id)
{
	if (timers.count(id) && !timers[id].killed)
	{
		removeTimers.push(id);
		freeID.push(id);
	}
}

void STimer::SetInterval(unsigned id, unsigned interval)
{
	if (timers.count(id))
	{
		timers[id].endTime = GetTimeMS() + interval;
		timers[id].intervalTime = interval;
	}
}

void STimer::SetRepeat(unsigned id, bool repeat)
{
	if (timers.count(id))
		timers[id].repeat = repeat;
}

void STimer::SetData(unsigned id, HSQOBJECT &data)
{
	if (timers.count(id))
		timers[id].data = data;
}