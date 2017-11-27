#include "..\\..\\..\\stdafx.h"

zCView* zCView::CreateView(int x, int y, int width, int height, zSTRING& texture)
{
	zCView* view = (zCView*)malloc(0x100);
	if( view )
	{
		view->Constructor(x,y,width,height);
		view->InsertBack(texture);
		return view;
	}
	return NULL;
};

void zCView::Hook_Print(zINT p1, zINT p2, zSTRING & p3)
{
	pMemLib->RemoveHook(0x006FFEB0);
	oCNpc *focus = oCNpc::GetHero()->GetFocusNpc();

	if (focus)
	{
		zSTRING fname = p3;
		fname.Delete(focus->GetName(0).Length(), fname.Length());
		if (strcmp(focus->GetName(0).ToChar(), fname.ToChar()) == 0)
		{
			CPlayer *player = playerManager.GetPlayer(focus);
			if (SCallback::onRenderNickname(player ? player->GetID() : -1, focus->GetName(0).ToChar(), p1, p2) == 0)
				this->_Print(p1, p2, p3);

			pMemLib->ImportHook(0x006FFEB0, sizeof(void(zCView::*)(zINT, zINT, zSTRING &)), &zCView::Hook_Print);
			return;
		}
	}

	this->_Print(p1, p2, p3);
	pMemLib->ImportHook(0x006FFEB0, sizeof(void(zCView::*)(zINT, zINT, zSTRING &)), &zCView::Hook_Print);
};

void zCView::Print(zINT p1, zINT p2, zSTRING & p3)
{
	pMemLib->RemoveHook(0x006FFEB0);
	this->_Print(p1, p2, p3);
	pMemLib->ImportHook(0x006FFEB0, sizeof(void(zCView::*)(zINT, zINT, zSTRING &)), &zCView::Hook_Print);
};