#ifndef SSCRIPT_H
#define SSCRIPT_H

class SScript
{
private:
	List<SDraw*> drawList;
	List<STexture*> textureList;
	zCView *drawView;
	
public:
	SScript();
	~SScript(){};

	inline List<SDraw*>* GetDrawList() { return &this->drawList;};
	inline List<STexture*>* GetTextureList() { return &this->textureList;};
	inline zCView* GetView() { return this->drawView; };
	void SetFreeze(bool _enable);
	void DrawTop();

	void OnRender();

	bool isFrozen;
	bool isSavingActive;
	bool isKeyEnabled;
	bool isUnconsciousEnabled;
	bool isInterfaceEnabled;
	bool isEqEnabled;
	bool isResetModelEnabled;
	bool isSpawningEnabled;
	bool isMarvinEnabled;
};

#endif //SSCRIPT_H