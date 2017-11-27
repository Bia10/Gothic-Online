#ifndef CSCRIPTDOWNLOAD_H
#define CSCRIPTDOWNLOAD_H

class CScriptDownload
{
public:
	PacketizedTCP* tcp;
	DirectoryDeltaTransfer* deltaTransfer;
	FileListTransfer* fileListTransfer;
	IncrementalReadInterface* partTime;
public:
	CScriptDownload();
	~CScriptDownload();
	
	void StartUp();

	static void Thread(void* pScriptDownload);
};

#endif //CSCRIPTDOWNLOAD_H
