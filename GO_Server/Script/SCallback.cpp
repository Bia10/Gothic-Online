#include "../stdafx.h"

SQInteger SCallback::onInit()
{
	int resultInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onInit");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onTick()
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onTick");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onJoin(int playerID)
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onJoin");

	sq_pushinteger(vm, playerID);

	SQ_FUNCTION_CALL(vm, 1);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onDisconnect(int playerID, const char* reason)
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onDisconnect");

	sq_pushinteger(vm, playerID);
	sq_pushstring(vm, reason, -1);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onCommand(int playerID, const char* command, const char* params)
{
	int resultInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onCommand");

	sq_pushinteger(vm, playerID);
	sq_pushstring(vm, command, -1);
	sq_pushstring(vm, params, -1);

	SQ_FUNCTION_CALL(vm, 3);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onPacket(int playerID, const char* data)
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onPacket");

	sq_pushinteger(vm, playerID);
	sq_pushstring(vm, data, -1);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onAdminCommand(int playerID, const char* command)
{
	int resultInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onAdminCommand");

	sq_pushinteger(vm, playerID);
	sq_pushstring(vm, command, -1);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onMessage(int playerID, const char* message)
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onMessage");

	sq_pushinteger(vm, playerID);
	sq_pushstring(vm, message, -1);

	SQ_FUNCTION_CALL_RETURN_INT(vm, 2, resultInt);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onHit(int playerID, int targetID)
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onHit");

	sq_pushinteger(vm, playerID);
	sq_pushinteger(vm, targetID);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onDie(int playerID, int killerID)
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onDie");

	sq_pushinteger(vm, playerID);
	sq_pushinteger(vm, killerID);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onUnconscious(int playerID, int killerID)
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onUnconscious");

	sq_pushinteger(vm, playerID);
	sq_pushinteger(vm, killerID);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onRespawn(int playerID)
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onRespawn");

	sq_pushinteger(vm, playerID);

	SQ_FUNCTION_CALL(vm, 1);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onStandUp(int playerID)
{
	int resultInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onStandUp");

	sq_pushinteger(vm, playerID);

	SQ_FUNCTION_CALL(vm, 1);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onTake(int playerID, int itemID, const char* itemInstance, int amount, const char* world)
{
	int resultInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onTake");

	sq_pushinteger(vm, playerID);
	sq_pushinteger(vm, itemID);
	sq_pushstring(vm, itemInstance, -1);
	sq_pushinteger(vm, amount);
	sq_pushstring(vm, world, -1);

	SQ_FUNCTION_CALL(vm, 5);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onDrop(int playerID, int itemID, const char* itemInstance, int amount, const char* world)
{
	int resultInt = 0;
	
	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onDrop");

	sq_pushinteger(vm, playerID);
	sq_pushinteger(vm, itemID);
	sq_pushstring(vm, itemInstance, -1);
	sq_pushinteger(vm, amount);
	sq_pushstring(vm, world, -1);

	SQ_FUNCTION_CALL(vm, 5);
	SQ_FUNCTION_END(vm);

	return resultInt;
};

SQInteger SCallback::onTakeFocus(int playerID, int focusID)
{
	int resultInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onTakeFocus");

	sq_pushinteger(vm, playerID);
	sq_pushinteger(vm, focusID);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return resultInt;
}

SQInteger SCallback::onLostFocus(int playerID, int focusID)
{
	int resultInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onLostFocus");

	sq_pushinteger(vm, playerID);
	sq_pushinteger(vm, focusID);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return resultInt;
}