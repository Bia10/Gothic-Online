#ifndef CBAN_H
#define CBAN_H

class CBan
{
private:
	List<const char*> banList;
public:
	CBan();
	~CBan();

	bool LoadBanList(RakString fileName);
	bool SaveBanList(RakString fileName);
	bool PushToBanList(RakString address);
	bool PopFromBanList(RakString address);

	bool BanPlayer(CPlayer* player, RakString fileName);
};

#endif //CBAN_H