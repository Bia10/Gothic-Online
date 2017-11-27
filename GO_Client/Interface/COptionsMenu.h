#ifndef COPTIONSMENU_H
#define COPTIONSMENU_H

#define OPTION_COLOR_DEFAULT zCOLOR(255,255,255,255)
#define OPTION_COLOR_SELECTED zCOLOR(247,243,115,255) //zCOLOR(162,255,0,255)
#define MAX_MENU_OPTIONS 3

/*	Menu opcji - menu g³ówne multiplayera dostêpne pod klawiszem esc
	Opcje:
	Back to game
	Change apperance //To póŸniej, bo przyda siê jeszcze jedno menu
	Video options
	Exit game

	Po otwarciu kamera ustawia siê w innym miejscu oraz na œrodku wyœwietla siê logo Gothic Online pobierane z VDF'a
	Blokowanie otwierania innych menu i blokowanie game_drawall
*/
//Tablice
static const char MenuOptions[MAX_MENU_OPTIONS][30] =
{
	{"Back to game"},
	{"Video options"},
	{"Exit game"}
};

typedef struct{
	zVEC3 pos;
	zVEC3 angle;
} CAM_SCENE;

static CAM_SCENE SCENES_WORLD_ZEN[3] = 
{

};
class COptionsMenu
{
private:
	unsigned int currentOption; //Pozycja na liscie
	zCView* goLogo; //instancja logo gothic online wyœwietlana z gry
	zCView* background; //T³o
	bool isVisible; //Widocznoœæ menu

	//singletone
	COptionsMenu();
	COptionsMenu( const COptionsMenu& ) {};
	~COptionsMenu();
public:
	static COptionsMenu & GetInstance()
	{
		static COptionsMenu optionsmenu;
		return optionsmenu;
	}

	bool IsVisible(){ return this->isVisible;};
	void Render();
	void SetVisible(bool enable);

};

#endif //COPTIONSMENU_H