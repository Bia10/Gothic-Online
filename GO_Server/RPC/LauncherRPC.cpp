#include "../stdafx.h"

void LauncherRPC::HandleLauncherRPC(CNetwork* network, Packet* packet)
{
	LOG("[info] Sending server information to launcher...");
	CConfig* cfg = core.GetConfig();
	BitStream s;
	s.Write((MessageID)GO_LAUNCHER);
	s.Write(cfg->GetServerName());
	s.Write(playerManager.GetNumberOfPlayers());
	s.Write(cfg->GetMaxSlots());
	s.Write(core.GetDescription());
	s.Write(cfg->GetClientScript());
	s.Write(RakString(versionString));
	s.Write(core.GetWorld());
	network->GetPeer()->Send(&s,MEDIUM_PRIORITY,RELIABLE,0,packet->systemAddress,false);
	//network->GetPeer()->CloseConnection(packet->systemAddress,true);
};