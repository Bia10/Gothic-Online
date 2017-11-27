#ifndef CNETWORK_H
#define CNETWORK_H

class CNetwork
{
private:
	RakPeerInterface* peer;
	CReceiver* pReceiver;
public:
	CNetwork();
	~CNetwork();

	bool InitNetwork();
	RakPeerInterface* GetPeer() const {return this->peer;};
	CReceiver* GetReceiver() const {return this->pReceiver;};

	void SendToAll(BitStream& stream, PacketPriority priority, PacketReliability reliability);
	void SendToPlayersOnList(BitStream& stream, PacketPriority priority, PacketReliability reliability, List<CPlayer*>* targetPlayerList);
	void SendToAllWithoutPlayer(BitStream& stream, PacketPriority priority, PacketReliability reliability, CPlayer* player);
	void SendToAllInWorld(BitStream& stream, PacketPriority priority, PacketReliability reliability, RakString world, CPlayer *player = NULL);
};	

#endif //CNETWORK_H