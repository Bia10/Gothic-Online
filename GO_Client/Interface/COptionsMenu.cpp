#include "..\\stdafx.h"

COptionsMenu::COptionsMenu()
{
	currentOption = 0;
	isVisible = false;
	background = new zCView(150, 6000, 1180, (100+280*MAX_MENU_OPTIONS));
	background->SetPos(150,6000);
	background->InsertBack(zSTRING("DLG_CONVERSATION.TGA"));
	//DEV
	zCView* screen = zCView::GetScreen();
	if( screen )
	{
		screen->InsertItem(background);
		background->SetSize(1180,(100+280*MAX_MENU_OPTIONS));
	}
};

COptionsMenu::~COptionsMenu()
{

};

void COptionsMenu::Render()
{
	zCView* screen = zCView::GetScreen();
	oCNpc* hero = oCNpc::GetHero(); //Do movlock'a

	zSTRING font = screen->GetFontName();
	screen->SetFont(zSTRING("Font_Old_20_White_Hi.TGA"));
	for( unsigned int i = 0; i < MAX_MENU_OPTIONS; i++ )
	{
		if( this->currentOption == i )
		{
			screen->SetFontColor(OPTION_COLOR_SELECTED);
			screen->Print(150,(6000+280*i), zSTRING(MenuOptions[i]));
			screen->SetFontColor(OPTION_COLOR_DEFAULT);
			
		}
		else
			screen->Print(150,(6000+280*i), zSTRING(MenuOptions[i]));
	}
	screen->SetFont(font);
};

void COptionsMenu::SetVisible(bool enable)
{
	if( enable == true )
	{
		oCGame* game = oCGame::GetGame();
		if( game )
		{
			if( game->GetShowPlayerStatus() == 1 )
			{
				game->SetShowPlayerStatus(0);
				if( this->isVisible == false )
				{
					oCNpc* hero = oCNpc::GetHero();
					if( hero )
					{
						zCModel* model = hero->GetModel();
						if( model )
							model->FadeOutAnisLayerRange(1,2000); //Wy³¹czenie animacji
						hero->CloseInventory(); //Zamkniêcie ekwipunku
						if( hero->GetWeaponMode() != NPC_WEAPON_NONE ) hero->SetWeaponMode2(NPC_WEAPON_NONE);
						if( !hero->IsMovLock() ) hero->SetMovLock(1);
					}
					//Tu dzieje siê magia
					this->currentOption = 0;
					this->isVisible = true;
				}
			}
		}
	}
	else
	{
		oCGame* game = oCGame::GetGame();
		if( game->GetShowPlayerStatus() == 0 )
		{
			game->SetShowPlayerStatus(1);
		}
		if( this->isVisible == true )
		{
			oCNpc* hero = oCNpc::GetHero();
			if( hero )
			{
				if( hero->IsMovLock() ) hero->SetMovLock(0); //W³¹czenie ruchu
			}
			//Tu ma sie dziac magia xD
			this->isVisible = false;
		}
	}
};