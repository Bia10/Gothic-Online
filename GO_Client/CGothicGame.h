#ifndef CGOTHICGAME_H
#define CGOTHICGAME_H

class CGothicGame
{
public:
	bool bIsFirstFrame; //U�ywa� podczas wykonywania pierwszej klatki w renderze
						//Je�li warto�� jest r�wna true, wtedy rozpocz�� procedur� ��czenia z serwerem
public:
	CGothicGame();
	~CGothicGame() {}; //P�ki co, zostawi� t� funkcj� pust�

	void InitGame();
};

#endif //CGOTHICGAME_H