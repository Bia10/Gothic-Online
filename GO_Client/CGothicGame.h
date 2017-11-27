#ifndef CGOTHICGAME_H
#define CGOTHICGAME_H

class CGothicGame
{
public:
	bool bIsFirstFrame; //U¿ywaæ podczas wykonywania pierwszej klatki w renderze
						//Jeœli wartoœæ jest równa true, wtedy rozpocz¹æ procedurê ³¹czenia z serwerem
public:
	CGothicGame();
	~CGothicGame() {}; //Póki co, zostawiê tê funkcjê pust¹

	void InitGame();
};

#endif //CGOTHICGAME_H