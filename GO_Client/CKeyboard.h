#ifndef CKEYBOARD_H
#define CKEYBOARD_H

#define MAX_KEYBOARD_LAYOUTS 2

class CKeyBoard
{
public:
	enum KeyBoardLayout
	{
		ENGLISH,
		RUSSIAN
	};

	CKeyBoard();

	void SetLayout(KeyBoardLayout layout);
	void SwitchLayout(); // SHIFT + ALT
	char GetTranslatedLetter(char letter);

private:
	KeyBoardLayout keyLayout;
};

#endif //CKEYBOARD_H