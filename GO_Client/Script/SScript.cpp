#include "..\\stdafx.h"

SScript::SScript()
{
	isFrozen = false;
	isKeyEnabled = true;
	isUnconsciousEnabled = true;
	isSavingActive = true;
	isInterfaceEnabled = true;
	isEqEnabled = true;
	isSpawningEnabled = false;
	isMarvinEnabled = false;
	drawList.Clear();
	textureList.Clear();

	drawView = new zCView(0, 0, 8192, 8192);
	zCView::GetScreen()->InsertItem(drawView);
	drawView->SetTransparency(1);
};

void SScript::SetFreeze(bool _enable)
{
	this->isFrozen = _enable;
	oCNpc::GetHero()->SetMovLock(_enable);
};

void SScript::DrawTop()
{
	zCView::GetScreen()->RemoveItem(drawView);
	zCView::GetScreen()->InsertItem(drawView);
};

void SScript::OnRender()
{
	timer.Pulse();
	SCallback::onRender();
		
	drawView->ClrPrintwin();
	for( size_t i = 0; i < drawList.Num(); ++i )
		drawList[i]->OnRender(drawView);

	if (zCursor::GetCursor().IsShowing())
	{
		// handle three keys at once
		zCursor::EMouseStatus statusLeft = zCursor::GetCursor().HandleEvent(zCursor::LEFT);
		zCursor::EMouseStatus statusRight = zCursor::GetCursor().HandleEvent(zCursor::RIGHT);
		zCursor::EMouseStatus statusWheel = zCursor::GetCursor().HandleEvent(zCursor::WHEEL);

		MOUSEPOS pos = zCursor::GetCursor().GetPosition();

		switch (statusLeft)
		{
		case zCursor::LEFT_DOWN:
			SCallback::onClick("LEFT_DOWN", (int)pos.x, (int)pos.y, (int)pos.wheel);
			break;

		case zCursor::LEFT_UP:
			SCallback::onClick("LEFT_UP", (int)pos.x, (int)pos.y, (int)pos.wheel);
			break;
		}

		switch (statusRight)
		{
		case zCursor::RIGHT_DOWN:
			SCallback::onClick("RIGHT_DOWN", (int)pos.x, (int)pos.y, (int)pos.wheel);
			break;

		case zCursor::RIGHT_UP:
			SCallback::onClick("RIGHT_UP", (int)pos.x, (int)pos.y, (int)pos.wheel);
			break;
		}

		switch (statusWheel)
		{
		case zCursor::WHEEL_DOWN:
			SCallback::onClick("WHEEL_DOWN", (int)pos.x, (int)pos.y, (int)pos.wheel);
			break;

		case zCursor::WHEEL_UP:
			SCallback::onClick("WHEEL_UP", (int)pos.x, (int)pos.y, (int)pos.wheel);
			break;
		}
	}
};
