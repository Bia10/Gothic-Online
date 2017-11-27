#ifndef CCHAT_H
#define CCHAT_H

struct ChatLine
{
	RakString text;
	zCOLOR color;
};

class CChat
{
private:
	bool bIsInitiated;
	bool bIsShowing;
	bool bIsInputActive;
	RakString currentText; //obecnie wprowadzane znaki z klawiatury;
	unsigned int chatLines;
	vector<ChatLine> lines;
	RakString lastMessage;
	//Key eventy
	unsigned int timeLastKey;
	RakString lastLetter;
	//Animacja gestykulacji
	unsigned int timeGesticulation;
public:
	CChat();
	~CChat();

	void InitChat();
	void Render();
	bool IsInitiated() const { return this->bIsInitiated;};
	bool IsShowing() const { return this->bIsShowing; };
	bool IsInputActive() const { return this->bIsInputActive; };
	unsigned int GetLines() const { return this->chatLines; };
	void AddLine(RakString text, zCOLOR color);
	void Show(bool enable){ this->bIsShowing = enable;};
	void KeyEvent(int key);
	void Clear();
};

#endif //CCHAT_H