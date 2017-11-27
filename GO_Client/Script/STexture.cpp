#include "..\\stdafx.h"

STexture::STexture(const char* textureName, int x, int y, int w, int h)
{
	isVisible = true;
	pos[1] = x; pos[2] = y;
	pos[3] = w; pos[4] = h;

	texName = zSTRING(textureName);
	texture = zCView::CreateView(x, y, w, h, texName);
	texture->SetPos(x,y);
	texture->SetSize(w,h);
	//texture->InsertBack(zSTRING(textureName));
	zCView::GetScreen()->InsertItem(texture);

	zCursor::GetCursor().Top();
	scr.GetScriptVars()->DrawTop();
};

STexture::~STexture()
{
	if(texture)
	{
		zCView::GetScreen()->RemoveItem(texture);
		texture->Destructor();
		free(texture);
	}
};

void STexture::SetVisible(bool val)
{
	if (isVisible == false && val == true)
	{
		zCView::GetScreen()->InsertItem(texture);
		texture->SetPos(pos[1], pos[2]);
		texture->SetSize(pos[3], pos[4]);
		
		zCursor::GetCursor().Top();
		scr.GetScriptVars()->DrawTop();
	}
	else if (isVisible == true && val == false)
		zCView::GetScreen()->RemoveItem(texture);
	isVisible = val;
};