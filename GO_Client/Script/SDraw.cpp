#include "..\\stdafx.h"

SDraw::SDraw(RakString txt, RakString fnt, int x, int y, zCOLOR clr)
{
	isVisible = false;
	pos[1] = x;
	pos[2] = y;
	text = zSTRING(txt.C_String());
	font = zSTRING(fnt.C_String());
	color = clr;

	zCursor::GetCursor().Top();
};

void SDraw::OnRender(zCView *screen)
{
	if( isVisible )
	{
		screen->SetFont(font);
		screen->SetFontColor(color);
		screen->SetFont(font);
		screen->Print(pos[1], pos[2], text);
	}
};