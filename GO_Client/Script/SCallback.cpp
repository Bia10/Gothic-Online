#include "..\\stdafx.h"

int SCallback::onInit()
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onInit");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onRender()
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onRender");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onCommand(RakString command, RakString params)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onCommand");

	sq_pushstring(vm, command.C_String(), -1);
	sq_pushstring(vm, params.C_String(), -1);

	SQ_FUNCTION_CALL_RETURN_INT(vm, 2, returnedInt);
	SQ_FUNCTION_END(vm);

	//Jeœli zwróci "1" to komenda nie zostanie wys³ana
	return returnedInt;
};

int SCallback::onPacket(const char* data)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onPacket");

	sq_pushstring(vm, data, -1);

	SQ_FUNCTION_CALL(vm, 1);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onClick(const char* button, int x, int y, int wheel)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onClick");

	sq_pushstring(vm, button, -1);
	sq_pushinteger(vm, x);
	sq_pushinteger(vm, y);
	sq_pushinteger(vm, wheel);

	SQ_FUNCTION_CALL(vm, 4);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onKey(int key)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onKey");
	
	sq_pushinteger(vm, key);
	sq_pushstring(vm, RakString(core.GetKeyBoard()->GetTranslatedLetter(zCInput::GetInput()->GetLetter(key))).C_String(), -1);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onHit()
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onHit");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onDie()
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onDie");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onRespawn()
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onRespawn");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onUnconscious()
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onUnconscious");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onStandUp()
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onStandUp");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onProgramName(const char* windowText)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onProgramName");

	sq_pushstring(vm, windowText, -1);

	SQ_FUNCTION_CALL_RETURN_INT(vm, 1, returnedInt);
	SQ_FUNCTION_END(vm);

	return returnedInt;
};

int SCallback::onOpenInventory()
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onOpenInventory");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return returnedInt;
}

int SCallback::onCloseInventory()
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onCloseInventory");
	SQ_FUNCTION_CALL(vm, 0);
	SQ_FUNCTION_END(vm);

	return returnedInt;
}

int SCallback::onMobTrigger(oCMobInter *mob)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onMobTrigger");

	zVEC3 pos = mob->GetVobPosition();
	sq_pushstring(vm, mob->GetName().ToChar(), -1);
	sq_pushinteger(vm, pos.x);
	sq_pushinteger(vm, pos.y);
	sq_pushinteger(vm, pos.z);
	
	switch (*(int*)mob)
	{
	case VOB_TYPE_VT_OCMOBBED:				sq_pushinteger(vm, 0); break;
	case VOB_TYPE_VT_OCMOBCONTAINER:		sq_pushinteger(vm, 1); break;
	case VOB_TYPE_VT_OCMOBDOOR:				sq_pushinteger(vm, 2); break;
	case VOB_TYPE_VT_OCMOBINTER:			sq_pushinteger(vm, 3); break;
	case VOB_TYPE_VT_OCMOBLADDER:			sq_pushinteger(vm, 4); break;
	case VOB_TYPE_VT_OCMOBSWITCH:			sq_pushinteger(vm, 5); break;
	case VOB_TYPE_VT_OCMOBWHEEL:			sq_pushinteger(vm, 6); break;
	default:								sq_pushinteger(vm, -1); break;
	}

	SQ_FUNCTION_CALL_RETURN_INT(vm, 5, returnedInt);
	SQ_FUNCTION_END(vm);

	return returnedInt;
}

int SCallback::onMobUntrigger(oCMobInter *mob)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onMobUntrigger");

	zVEC3 pos = mob->GetVobPosition();
	sq_pushstring(vm, mob->GetName().ToChar(), -1);
	sq_pushinteger(vm, pos.x);
	sq_pushinteger(vm, pos.y);
	sq_pushinteger(vm, pos.z);

	switch (*(int*)mob)
	{
	case VOB_TYPE_VT_OCMOBBED:				sq_pushinteger(vm, 0); break;
	case VOB_TYPE_VT_OCMOBCONTAINER:		sq_pushinteger(vm, 1); break;
	case VOB_TYPE_VT_OCMOBDOOR:				sq_pushinteger(vm, 2); break;
	case VOB_TYPE_VT_OCMOBINTER:			sq_pushinteger(vm, 3); break;
	case VOB_TYPE_VT_OCMOBLADDER:			sq_pushinteger(vm, 4); break;
	case VOB_TYPE_VT_OCMOBSWITCH:			sq_pushinteger(vm, 5); break;
	case VOB_TYPE_VT_OCMOBWHEEL:			sq_pushinteger(vm, 6); break;
	default:								sq_pushinteger(vm, -1); break;
	}

	SQ_FUNCTION_CALL_RETURN_INT(vm, 5, returnedInt);
	SQ_FUNCTION_END(vm);

	return returnedInt;
}

int SCallback::onUseItem(const char *instance, int amount, int hand)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onUseItem");

	sq_pushstring(vm, instance, -1);
	sq_pushinteger(vm, amount);
	sq_pushinteger(vm, hand);

	SQ_FUNCTION_CALL(vm, 3);
	SQ_FUNCTION_END(vm);

	return returnedInt;
}

int SCallback::onTakeFocus(int id, const char *name, float x, float y, float z)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onTakeFocus");

	sq_pushinteger(vm, id);
	sq_pushstring(vm, name, -1);
	sq_pushfloat(vm, x);
	sq_pushfloat(vm, y);
	sq_pushfloat(vm, z);

	SQ_FUNCTION_CALL(vm, 5);
	SQ_FUNCTION_END(vm);

	return returnedInt;
}

int SCallback::onLostFocus(int id, const char *name)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onLostFocus");

	sq_pushinteger(vm, id);
	sq_pushstring(vm, name, -1);

	SQ_FUNCTION_CALL(vm, 2);
	SQ_FUNCTION_END(vm);

	return returnedInt;
}

int SCallback::onRenderNickname(int id, const char *name, int x, int y)
{
	int returnedInt = 0;

	HSQUIRRELVM vm = scr.GetVM();
	SQ_FUNCTION_BEGIN(vm, "onRenderNickname");

	sq_pushinteger(vm, id);
	sq_pushstring(vm, name, -1);
	sq_pushinteger(vm, x);
	sq_pushinteger(vm, y);

	SQ_FUNCTION_CALL_RETURN_INT(vm, 4, returnedInt);
	SQ_FUNCTION_END(vm);

	return returnedInt;
}