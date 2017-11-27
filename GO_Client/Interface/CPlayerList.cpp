#include "..\\stdafx.h"

CPlayerList::CPlayerList()
{
	playerList = new RakString[1024];
	isShowing = false;
	texture = new zCView(0, 0, 8192, 8192);
	texture->SetPos(0,0);
	texture->InsertBack(zSTRING("DLG_CONVERSATION.TGA"));
};

CPlayerList::~CPlayerList()
{
};

void CPlayerList::Render()
{
	if (scr.GetScriptVars()->isInterfaceEnabled)
	{
		zCInput* input = zCInput::GetInput();
		zCView* view = zCView::GetScreen();
		zSTRING font = view->GetFontName();
		zCOLOR color = zCOLOR(255,255,255,255);

		if( input->KeyPressed(KEY_F2) )
		{
			if( isShowing == false )
			{
				view->InsertItem(texture);
				core.GetChat()->Show(false);
				/*for( size_t i = 0; i < 200; i++ )
					playerList[i] = RakString("%d Player 0ms", i);*/
				isShowing = true;
			}
			else
			{
				view->SetFont(zSTRING("Font_Old_10_White_Hi.TGA"));
				view->SetFontColor(zCOLOR(247,243,115,255));
				view->Print(0,0,zSTRING("Lista graczy na serwerze:"));
				view->SetFontColor(color);
				view->SetFont(font);
				int x,y = 0;
				int column = 1;
				zSTRING currentName;
				for( size_t i = 0; i < 1024; i++ )
				{
					if( playerList[i] && !playerList[i].IsEmpty() )
					{
						currentName = playerList[i].C_String();
						if( int(i/35) == column+1 )
						{
							y = 0;
						}
						else
						{
							y++;
						}
						column = int(i/35);
						x = column*1200;
						view->Print(x, y*200, currentName);
					}
				}
			}
		}
		else
		{
			if( isShowing == true )
			{
				view->RemoveItem(texture);
				core.GetChat()->Show(true);
				isShowing = false;
			}
		}
	}
};