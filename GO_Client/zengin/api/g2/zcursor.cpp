#include "api/g2/zcursor.h"

zCursor::zCursor()
{
	inp = zCInput::GetInput();
	mouseTex = new zCView(0,0,8192,8192);
	mouseTex->InsertBack(zSTRING("LO.TGA"));
	mouseTex->SetSize(192,192);
	mouseTex->SetFlags(255);
	texName = zSTRING("LO.TGA");
	mouseStatus = NONE;
	sensitivity = 16.0f;

	mouseLeft = false; mouseRight = false; mouseWheel = false;
};

zCursor::~zCursor()
{

};

MOUSEPOS zCursor::GetPosition() const
{
	return position;
};

void zCursor::SetPosition(float x, float y, float wheel)
{
	position.x = x;
	position.y = y;
	position.wheel = wheel;
};

bool zCursor::IsLeftBtnClicked() const
{
	return inp->GetMouseButtonPressedLeft();
};

bool zCursor::IsRightBtnClicked() const
{
	return inp->GetMouseButtonPressedRight();
};

bool zCursor::IsWheelClicked() const
{
	return inp->GetMouseButtonPressedMid();
};

void zCursor::SetShowing(bool val)
{
	if (!isShowing && val && mouseTex)
		zCView::GetScreen()->InsertItem(mouseTex,true);
	if (isShowing && !val && mouseTex)
		zCView::GetScreen()->RemoveItem(mouseTex);

	isShowing = val;
};

void zCursor::SetTexture(const char *_texName)
{
	if (isShowing)
	{
		zCView::GetScreen()->RemoveItem(mouseTex);
		mouseTex->InsertBack(zSTRING(_texName));
		zCView::GetScreen()->InsertItem(mouseTex, true);
	}
	else
		mouseTex->InsertBack(zSTRING(_texName));

	texName = _texName;
}

void zCursor::OnUpdate()
{
	float fX, fY, fWheel;
	inp->GetMousePos(fX,fY,fWheel);
	if( fX != 0 && fX != position.x )
		position.x += (fX * sensitivity);
	if( fY != 0 && fY != position.y )
		position.y += (fY * sensitivity);
	if( fWheel != 0 && fWheel != position.wheel )
		position.wheel += fWheel;
	if( position.x < 0 ) position.x = 0;
	else if( position.x > 8192.0f ) position.x = 8192.0f;
	if( position.y < 0 ) position.y = 0;
	else if( position.y > 8192.0f ) position.y = 8192.0f;

	if( mouseTex && isShowing == true )
		mouseTex->SetPos(position.x, position.y);
};

void zCursor::Top()
{
	if (isShowing)
	{
		zCView::GetScreen()->RemoveItem(mouseTex);
		mouseTex->InsertBack(zSTRING(texName));
		zCView::GetScreen()->InsertItem(mouseTex, true);
	}
}

zCursor::EMouseStatus zCursor::HandleEvent(EMouseButton button)
{
	switch (button)
	{
	case LEFT:
		if (IsLeftBtnClicked() && !mouseLeft)
		{
			mouseLeft = true;
			return LEFT_DOWN;
		}
		else if (!IsLeftBtnClicked() && mouseLeft)
		{
			mouseLeft = false;
			return LEFT_UP;
		}
		break;

	case RIGHT:
		if (IsRightBtnClicked() && !mouseRight)
		{
			mouseRight = true;
			return RIGHT_DOWN;
		}
		else if (!IsRightBtnClicked() && mouseRight)
		{
			mouseRight = false;
			return RIGHT_UP;
		}
		break;

	case WHEEL:
		if (IsWheelClicked() && !mouseWheel)
		{
			mouseWheel = true;
			return WHEEL_DOWN;
		}
		else if (!IsWheelClicked() && mouseWheel)
		{
			mouseWheel = false;
			return WHEEL_UP;
		}
		break;
	}

	return NONE;
}