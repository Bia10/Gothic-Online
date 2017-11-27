#include "stdafx.h"

CScriptDownload::CScriptDownload()
{
	deltaTransfer = new DirectoryDeltaTransfer;
	tcp = new PacketizedTCP;
	fileListTransfer = new FileListTransfer;
	partTime = new IncrementalReadInterface;
	deltaTransfer->SetDownloadRequestIncrementalReadInterface(partTime, 10000000); // 10 mb
	tcp->AttachPlugin(deltaTransfer);
	tcp->AttachPlugin(fileListTransfer);
	deltaTransfer->SetFileListTransferPlugin(fileListTransfer);
};

CScriptDownload::~CScriptDownload()
{
	/*tcp->DetachPlugin(deltaTransfer);
	tcp->DetachPlugin(fileListTransfer);
	tcp->Stop();
	delete deltaTransfer;
	delete tcp;
	delete fileListTransfer;
	delete partTime;*/
};

void CScriptDownload::StartUp()
{
	deltaTransfer->SetApplicationDirectory("");
	deltaTransfer->AddUploadsFromSubdirectory("client-scripts");
	deltaTransfer->AddUploadsFromSubdirectory("download");
	LOG("[Downloader] Number of files to download: %d", deltaTransfer->GetNumberOfFilesForUpload());

	thread downloaderThread(CScriptDownload::Thread,(void*)this);
	downloaderThread.detach();
};

void CScriptDownload::Thread(void* pThis)
{
	CScriptDownload* pScriptDownload = (CScriptDownload*)pThis;
	LOG("[Downloader] Thread started, waiting for peers..");
	if( pScriptDownload->tcp->Start(atoi(core.GetConfig()->GetServerPort().C_String()), atoi(core.GetConfig()->GetMaxSlots().C_String())+10) )
	{
		Packet* packet;
		while(true)
		{
			for(packet = pScriptDownload->tcp->Receive(); packet; pScriptDownload->tcp->DeallocatePacket(packet), packet = pScriptDownload->tcp->Receive());
			SystemAddress sa;
			if(pScriptDownload->tcp->HasNewIncomingConnection() != UNASSIGNED_SYSTEM_ADDRESS )
				LOG("[Downloader] New connection!");
			if(pScriptDownload->tcp->HasLostConnection() != UNASSIGNED_SYSTEM_ADDRESS)
				LOG("[Downloader] Peer disconnected.");
			if(pScriptDownload->tcp->HasFailedConnectionAttempt() != UNASSIGNED_SYSTEM_ADDRESS)
				LOG("[Downloader] Connection to server failure.");
			if(pScriptDownload->tcp->HasCompletedConnectionAttempt() != UNASSIGNED_SYSTEM_ADDRESS)
				LOG("[Downloader] Connection complete.");
			RakSleep(5);
		}
	}
};