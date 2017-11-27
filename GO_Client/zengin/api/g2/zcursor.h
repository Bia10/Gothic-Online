#ifndef _ZCURSOR_H
#define _ZCURSOR_H

#include "api/g2/zcinput.h"
#include "api/g2/zcview.h"
//W³asna klasa, wszystko po swojemu bo skejt mówi³ ¿e gotik ma swój mouse handler
struct MOUSEPOS
{
	float x;
	float y;
	float wheel;
};

class zCursor
{
public:
	enum EMouseStatus;

private:
	MOUSEPOS position;
	zCInput* inp;
	zCView* mouseTex;
	zSTRING texName;
	EMouseStatus mouseStatus;
	float sensitivity;
	bool isShowing;
	bool mouseLeft, mouseRight, mouseWheel;
private:
	zCursor();
	zCursor( const zCursor & ) {};
	~zCursor();
public:
	enum EMouseStatus
	{
		NONE,
		LEFT_UP,
		LEFT_DOWN,
		RIGHT_UP,
		RIGHT_DOWN,
		WHEEL_UP,
		WHEEL_DOWN
	};

	enum EMouseButton
	{
		LEFT,
		RIGHT,
		WHEEL
	};

	static zCursor& GetCursor()
	{
		static zCursor cursor;
		return cursor;
	}

	MOUSEPOS GetPosition() const;
	void SetPosition(float x, float y, float wheel = 0.0f);
	bool IsRightBtnClicked() const;
	bool IsLeftBtnClicked() const;
	bool IsWheelClicked() const;
	float GetSensitivity() const { return this->sensitivity;};
	inline void SetSensitivity(float val) { this->sensitivity = val; };
	void SetShowing(bool val);
	bool IsShowing() const { return this->isShowing;};
	void SetTexture(const char *texName);
	zSTRING GetTexture() { return texName; };
	void OnUpdate();
	void Top();
	EMouseStatus HandleEvent(EMouseButton button);
};

#endif //_ZCURSOR_H