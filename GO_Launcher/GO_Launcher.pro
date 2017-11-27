#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T20:38:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GO_Launcher
TEMPLATE = app

LIBS += ws2_32.lib

INCLUDEPATH += RakNet

DEFINES += _ATL_XP_TARGETING \
            D_ATL_XP_TARGETING \
            NOMINMAX

RC_ICONS += go_icon.ico

SOURCES += main.cpp\
        SLauncher.cpp \
    Style/CCustomWindow.cpp \
    Style/CWindowButton.cpp \
    Style/CWindowTitleBar.cpp \
    CServerInfo.cpp \
    CServerManager.cpp \
    CSettings.cpp \
    CAddons.cpp \
    COptions.cpp \
    CMessageBox.cpp \
    CFavoriteManager.cpp \
    CFavorite.cpp \
    CNetwork.cpp \
    CNetworkThread.cpp \
    RakNet/_FindFirst.cpp \
    RakNet/Base64Encoder.cpp \
    RakNet/BitStream.cpp \
    RakNet/CCRakNetSlidingWindow.cpp \
    RakNet/CCRakNetUDT.cpp \
    RakNet/CheckSum.cpp \
    RakNet/CloudClient.cpp \
    RakNet/CloudCommon.cpp \
    RakNet/CloudServer.cpp \
    RakNet/CommandParserInterface.cpp \
    RakNet/ConnectionGraph2.cpp \
    RakNet/ConsoleServer.cpp \
    RakNet/DataCompressor.cpp \
    RakNet/DirectoryDeltaTransfer.cpp \
    RakNet/DR_SHA1.cpp \
    RakNet/DS_BytePool.cpp \
    RakNet/DS_ByteQueue.cpp \
    RakNet/DS_HuffmanEncodingTree.cpp \
    RakNet/DS_Table.cpp \
    RakNet/DynDNS.cpp \
    RakNet/EmailSender.cpp \
    RakNet/EpochTimeToString.cpp \
    RakNet/FileList.cpp \
    RakNet/FileListTransfer.cpp \
    RakNet/FileOperations.cpp \
    RakNet/FormatString.cpp \
    RakNet/FullyConnectedMesh2.cpp \
    RakNet/Getche.cpp \
    RakNet/Gets.cpp \
    RakNet/GetTime.cpp \
    RakNet/gettimeofday.cpp \
    RakNet/GridSectorizer.cpp \
    RakNet/HTTPConnection.cpp \
    RakNet/HTTPConnection2.cpp \
    RakNet/IncrementalReadInterface.cpp \
    RakNet/Itoa.cpp \
    RakNet/LinuxStrings.cpp \
    RakNet/LocklessTypes.cpp \
    RakNet/LogCommandParser.cpp \
    RakNet/MessageFilter.cpp \
    RakNet/NatPunchthroughClient.cpp \
    RakNet/NatPunchthroughServer.cpp \
    RakNet/NatTypeDetectionClient.cpp \
    RakNet/NatTypeDetectionCommon.cpp \
    RakNet/NatTypeDetectionServer.cpp \
    RakNet/NetworkIDManager.cpp \
    RakNet/NetworkIDObject.cpp \
    RakNet/PacketConsoleLogger.cpp \
    RakNet/PacketFileLogger.cpp \
    RakNet/PacketizedTCP.cpp \
    RakNet/PacketLogger.cpp \
    RakNet/PacketOutputWindowLogger.cpp \
    RakNet/PluginInterface2.cpp \
    RakNet/PS4Includes.cpp \
    RakNet/Rackspace.cpp \
    RakNet/RakMemoryOverride.cpp \
    RakNet/RakNetCommandParser.cpp \
    RakNet/RakNetSocket.cpp \
    RakNet/RakNetSocket2.cpp \
    RakNet/RakNetSocket2_360_720.cpp \
    RakNet/RakNetSocket2_Berkley.cpp \
    RakNet/RakNetSocket2_Berkley_NativeClient.cpp \
    RakNet/RakNetSocket2_NativeClient.cpp \
    RakNet/RakNetSocket2_PS3_PS4.cpp \
    RakNet/RakNetSocket2_PS4.cpp \
    RakNet/RakNetSocket2_Vita.cpp \
    RakNet/RakNetSocket2_Windows_Linux.cpp \
    RakNet/RakNetSocket2_Windows_Linux_360.cpp \
    RakNet/RakNetSocket2_WindowsStore8.cpp \
    RakNet/RakNetStatistics.cpp \
    RakNet/RakNetTransport2.cpp \
    RakNet/RakNetTypes.cpp \
    RakNet/RakPeer.cpp \
    RakNet/RakSleep.cpp \
    RakNet/RakString.cpp \
    RakNet/RakThread.cpp \
    RakNet/RakWString.cpp \
    RakNet/Rand.cpp \
    RakNet/RandSync.cpp \
    RakNet/ReadyEvent.cpp \
    RakNet/RelayPlugin.cpp \
    RakNet/ReliabilityLayer.cpp \
    RakNet/ReplicaManager3.cpp \
    RakNet/Router2.cpp \
    RakNet/RPC4Plugin.cpp \
    RakNet/SecureHandshake.cpp \
    RakNet/SendToThread.cpp \
    RakNet/SignaledEvent.cpp \
    RakNet/SimpleMutex.cpp \
    RakNet/SocketLayer.cpp \
    RakNet/StatisticsHistory.cpp \
    RakNet/StringCompressor.cpp \
    RakNet/StringTable.cpp \
    RakNet/SuperFastHash.cpp \
    RakNet/TableSerializer.cpp \
    RakNet/TCPInterface.cpp \
    RakNet/TeamBalancer.cpp \
    RakNet/TeamManager.cpp \
    RakNet/TelnetTransport.cpp \
    RakNet/ThreadsafePacketLogger.cpp \
    RakNet/TwoWayAuthentication.cpp \
    RakNet/UDPForwarder.cpp \
    RakNet/UDPProxyClient.cpp \
    RakNet/UDPProxyCoordinator.cpp \
    RakNet/UDPProxyServer.cpp \
    RakNet/VariableDeltaSerializer.cpp \
    RakNet/VariableListDeltaTracker.cpp \
    RakNet/VariadicSQLParser.cpp \
    RakNet/VitaIncludes.cpp \
    RakNet/WSAStartupSingleton.cpp \
    CDownloader.cpp \
    CFileTransferCallback.cpp \
    CInternetManager.cpp \
    CUrlDownloader.cpp \
    CMasterServerList.cpp \
    RPC/CRPCDownloader.cpp \
    RPC/CRPCFavorite.cpp \
    RPC/CRPCInternet.cpp \
    CInject.cpp \
    CLanguage.cpp \
    CVersion.cpp \
    SLog.cpp

HEADERS  += SLauncher.h \
    Style/CCustomWindow.h \
    Style/CWindowButton.h \
    Style/CWindowTitleBar.h \
    Style/StyleDefines.h \
    ServerUnknow.h \
    PCH.h \
    CServerInfo.h \
    CServerManager.h \
    CSettings.h \
    SettingUnknow.h \
    CAddons.h \
    COptions.h \
    CMessageBox.h \
    CFavoriteManager.h \
    CFavorite.h \
    CNetwork.h \
    CNetworkThread.h \
    RakNet/_FindFirst.h \
    RakNet/AutopatcherPatchContext.h \
    RakNet/AutopatcherRepositoryInterface.h \
    RakNet/Base64Encoder.h \
    RakNet/BitStream.h \
    RakNet/CCRakNetSlidingWindow.h \
    RakNet/CCRakNetUDT.h \
    RakNet/CheckSum.h \
    RakNet/CloudClient.h \
    RakNet/CloudCommon.h \
    RakNet/CloudServer.h \
    RakNet/CommandParserInterface.h \
    RakNet/ConnectionGraph2.h \
    RakNet/ConsoleServer.h \
    RakNet/DataCompressor.h \
    RakNet/DirectoryDeltaTransfer.h \
    RakNet/DR_SHA1.h \
    RakNet/DS_BinarySearchTree.h \
    RakNet/DS_BPlusTree.h \
    RakNet/DS_BytePool.h \
    RakNet/DS_ByteQueue.h \
    RakNet/DS_Hash.h \
    RakNet/DS_Heap.h \
    RakNet/DS_HuffmanEncodingTree.h \
    RakNet/DS_HuffmanEncodingTreeFactory.h \
    RakNet/DS_HuffmanEncodingTreeNode.h \
    RakNet/DS_LinkedList.h \
    RakNet/DS_List.h \
    RakNet/DS_Map.h \
    RakNet/DS_MemoryPool.h \
    RakNet/DS_Multilist.h \
    RakNet/DS_OrderedChannelHeap.h \
    RakNet/DS_OrderedList.h \
    RakNet/DS_Queue.h \
    RakNet/DS_QueueLinkedList.h \
    RakNet/DS_RangeList.h \
    RakNet/DS_Table.h \
    RakNet/DS_ThreadsafeAllocatingQueue.h \
    RakNet/DS_Tree.h \
    RakNet/DS_WeightedGraph.h \
    RakNet/DynDNS.h \
    RakNet/EmailSender.h \
    RakNet/EmptyHeader.h \
    RakNet/EpochTimeToString.h \
    RakNet/Export.h \
    RakNet/FileList.h \
    RakNet/FileListNodeContext.h \
    RakNet/FileListTransfer.h \
    RakNet/FileListTransferCBInterface.h \
    RakNet/FileOperations.h \
    RakNet/FormatString.h \
    RakNet/FullyConnectedMesh2.h \
    RakNet/Getche.h \
    RakNet/Gets.h \
    RakNet/GetTime.h \
    RakNet/gettimeofday.h \
    RakNet/GridSectorizer.h \
    RakNet/HTTPConnection.h \
    RakNet/HTTPConnection2.h \
    RakNet/IncrementalReadInterface.h \
    RakNet/InternalPacket.h \
    RakNet/Itoa.h \
    RakNet/Kbhit.h \
    RakNet/LinuxStrings.h \
    RakNet/LocklessTypes.h \
    RakNet/LogCommandParser.h \
    RakNet/MessageFilter.h \
    RakNet/MessageIdentifiers.h \
    RakNet/MTUSize.h \
    RakNet/NativeFeatureIncludes.h \
    RakNet/NativeFeatureIncludesOverrides.h \
    RakNet/NativeTypes.h \
    RakNet/NatPunchthroughClient.h \
    RakNet/NatPunchthroughServer.h \
    RakNet/NatTypeDetectionClient.h \
    RakNet/NatTypeDetectionCommon.h \
    RakNet/NatTypeDetectionServer.h \
    RakNet/NetworkIDManager.h \
    RakNet/NetworkIDObject.h \
    RakNet/PacketConsoleLogger.h \
    RakNet/PacketFileLogger.h \
    RakNet/PacketizedTCP.h \
    RakNet/PacketLogger.h \
    RakNet/PacketOutputWindowLogger.h \
    RakNet/PacketPool.h \
    RakNet/PacketPriority.h \
    RakNet/PluginInterface2.h \
    RakNet/PS3Includes.h \
    RakNet/PS4Includes.h \
    RakNet/Rackspace.h \
    RakNet/RakAlloca.h \
    RakNet/RakAssert.h \
    RakNet/RakMemoryOverride.h \
    RakNet/RakNetCommandParser.h \
    RakNet/RakNetDefines.h \
    RakNet/RakNetDefinesOverrides.h \
    RakNet/RakNetSmartPtr.h \
    RakNet/RakNetSocket.h \
    RakNet/RakNetSocket2.h \
    RakNet/RakNetStatistics.h \
    RakNet/RakNetTime.h \
    RakNet/RakNetTransport2.h \
    RakNet/RakNetTypes.h \
    RakNet/RakNetVersion.h \
    RakNet/RakPeer.h \
    RakNet/RakPeerInterface.h \
    RakNet/RakSleep.h \
    RakNet/RakString.h \
    RakNet/RakThread.h \
    RakNet/RakWString.h \
    RakNet/Rand.h \
    RakNet/RandSync.h \
    RakNet/ReadyEvent.h \
    RakNet/RefCountedObj.h \
    RakNet/RelayPlugin.h \
    RakNet/ReliabilityLayer.h \
    RakNet/ReplicaEnums.h \
    RakNet/ReplicaManager3.h \
    RakNet/Router2.h \
    RakNet/RPC4Plugin.h \
    RakNet/SecureHandshake.h \
    RakNet/SendToThread.h \
    RakNet/SignaledEvent.h \
    RakNet/SimpleMutex.h \
    RakNet/SimpleTCPServer.h \
    RakNet/SingleProducerConsumer.h \
    RakNet/SocketDefines.h \
    RakNet/SocketIncludes.h \
    RakNet/SocketLayer.h \
    RakNet/StatisticsHistory.h \
    RakNet/StringCompressor.h \
    RakNet/StringTable.h \
    RakNet/SuperFastHash.h \
    RakNet/TableSerializer.h \
    RakNet/TCPInterface.h \
    RakNet/TeamBalancer.h \
    RakNet/TeamManager.h \
    RakNet/TelnetTransport.h \
    RakNet/ThreadPool.h \
    RakNet/ThreadsafePacketLogger.h \
    RakNet/TransportInterface.h \
    RakNet/TwoWayAuthentication.h \
    RakNet/UDPForwarder.h \
    RakNet/UDPProxyClient.h \
    RakNet/UDPProxyCommon.h \
    RakNet/UDPProxyCoordinator.h \
    RakNet/UDPProxyServer.h \
    RakNet/VariableDeltaSerializer.h \
    RakNet/VariableListDeltaTracker.h \
    RakNet/VariadicSQLParser.h \
    RakNet/VitaIncludes.h \
    RakNet/WindowsIncludes.h \
    RakNet/WSAStartupSingleton.h \
    RakNet/XBox360Includes.h \
    RakNetInclude.h \
    CDownloader.h \
    CFileTransferCallback.h \
    CInternetManager.h \
    CUrlDownloader.h \
    CMasterServerList.h \
    RPC/CRPCDownloader.h \
    RPC/CRPCFavorite.h \
    RPC/CRPCInternet.h \
    CInject.h \
    CLanguage.h \
    GlobalDefines.h \
    Macros.h \
    CVersion.h \
    SLog.h

FORMS    += SLauncher.ui \
    CAddons.ui \
    COptions.ui \
    CMessageBox.ui \
    CFavorite.ui \
    CDownloader.ui \
    CUrlDownloader.ui

RESOURCES += \
    resource.qrc

DISTFILES +=

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
