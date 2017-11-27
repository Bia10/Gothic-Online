#include "..\\stdafx.h"

SKey::SKey()
{
	DLOG("SKey::SKey()");

	timeLastKey = 0;
	disabledKeys.Clear();
};

SKey::~SKey()
{
	DLOG("SKey::~SKey()");
};

void SKey::KeyEvent(int key)
{
	if (zCInput::GetInput()->KeyPressed(KEY_LSHIFT) && zCInput::GetInput()->KeyPressed(KEY_LALT))
		core.GetKeyBoard()->SwitchLayout();

	// Blockade keys, when chat is active
	if (!core.GetChat()->IsInputActive() && GetTimeMS() > this->timeLastKey)
	{
		SCallback::onKey(key);
		this->timeLastKey = GetTimeMS() + 70;
	}
}

bool SKey::IsKeyEnabled(int key)
{
	if( disabledKeys.FindIndex(key) > -1 )
		return false;
	return true;
}

void SKey::SetKeyEnabled(int key, bool toggle)
{
	if( toggle == true )
		if( disabledKeys.FindIndex(key) > -1 )
			disabledKeys.Remove(key);
	if( toggle == false )
		if( disabledKeys.FindIndex(key) == -1 )
			disabledKeys.PushBack(key);
}