#ifndef STEXTURE_H
#define STEXTURE_H

class STexture
{
public:
	bool isVisible;
	int pos[4];
	zSTRING texName;

	zCView* texture;
	STexture(const char* textureName, int x, int y, int w, int h);
	~STexture();

	void SetVisible(bool val);
};

#endif //STEXTURE_H