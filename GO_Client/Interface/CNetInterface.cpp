#include "..\\stdafx.h"

CNetInterface::CNetInterface()
{
	isShowing = false;
	receivedPacketCount = 0;
	window = new zCView(0,0,windowMaxPosX,windowMaxPosY);
	window->SetPos(0,0);
	window->InsertBack(zSTRING("DLG_CONVERSATION.TGA"));
};

CNetInterface::~CNetInterface()
{

};

void CNetInterface::Render()
{
	oCGame* game = oCGame::GetGame();
	zCView* screen = zCView::GetScreen();
	zCInput* input = zCInput::GetInput();
	CChat* chat = core.GetChat();
	CNetwork* net = core.GetNetwork();
	zSTRING font = screen->GetFontName();
	zCOLOR color = zCOLOR(255,255,255,255);

	if( game->GetShowPlayerStatus() )
	{
		if( input->KeyPressed(KEY_F1) )
		{
			if( this->isShowing == false )
			{
				if( chat->IsShowing() == true )
					chat->Show(false);
				screen->InsertItem(window);
				window->SetSize(windowMaxPosX,windowMaxPosY);
				this->isShowing = true;
			}
		}
		else
		{
			if( this->isShowing == true )
			{
				if( chat->IsShowing() == false )
					chat->Show(true);
				screen->RemoveItem(window);
				this->isShowing = false;
			}
		}

		//Teraz faktyczne renderowanie
		if( this->isShowing == true )
		{
			screen->SetFont(zSTRING("Font_Old_20_White_Hi.TGA"));
			screen->SetFontColor(zCOLOR(247,243,115,255));
			screen->Print(0,0,zSTRING("W³aœciwoœci sieci"));
			screen->SetFontColor(color);
			screen->SetFont(font);
			if( net->IsConnected() == true )
			{
				RakNetStatistics rns;
				net->GetPeer()->GetStatistics(0,&rns);
				//screen->Print(0,400,zSTRING(RakString("Ping: %dms",core.GetMultiplayer()->pingTime).C_String()));
				screen->Print(0,400,zSTRING(RakString("Ping: %dms",core.GetNetwork()->GetPeer()->GetLastPing(net->GetServerAddress())).C_String()));
				screen->Print(0,600,zSTRING(RakString("FPS: %d",vidGetFPSRate()).C_String()));
				screen->Print(0,800,zSTRING(RakString("Odebrane pakiety: %d",this->receivedPacketCount).C_String()));
				screen->Print(0,1000,zSTRING(RakString("Pakiety zagubione: %f%",rns.packetlossTotal).C_String()));
				screen->Print(0,1200,zSTRING(RakString("Pakiety zagubione w ostatniej sekundzie: %f%",rns.packetlossLastSecond).C_String()));
				screen->Print(0,1400,zSTRING(RakString("Bufor wiadomoœci: %d",rns.messagesInResendBuffer).C_String()));
				screen->Print(0,1600,zSTRING(RakString("Bufor bajtów do wys³ania: %d",rns.bytesInResendBuffer).C_String()));
				screen->Print(0,1800,zSTRING(RakString("Utworzeni gracze: %d",playerManager.GetNumberOfPlayers()).C_String()));
				screen->Print(0,2000,zSTRING(RakString("Utworzone przedmioty: %d", itemManager.GetNumberOfItems()).C_String()));
			}
			else
			{
				screen->SetFontColor(zCOLOR(255,0,0,255));
				screen->Print((windowMaxPosX/2),(windowMaxPosY/2),zSTRING("Brak po³¹czenia!"));
				screen->SetFontColor(color);
			}
		}
	}

	screen->SetFont(font);
	screen->SetFontColor(color);
};