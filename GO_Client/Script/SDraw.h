#ifndef SDRAW_H
#define SDRAW_H

class SDraw
{
public:
	bool isVisible;
	int pos[2];
	zSTRING text;
	zSTRING font;
	zCOLOR color;
	SDraw(RakString txt, RakString fnt, int x, int y, zCOLOR clr);
	~SDraw() {};
	void OnRender(zCView* screen);
};

#endif //SDRAW_H