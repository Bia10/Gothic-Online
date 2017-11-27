#ifndef SCALLBACK_H
#define SCALLBACK_H

namespace SCallback
{
	SQInteger onInit();
	SQInteger onTick();
	SQInteger onJoin(int playerID);
	SQInteger onHit(int playerID, int targetID);
	SQInteger onDie(int playerID, int killerID);
	SQInteger onUnconscious(int playerID, int killerID);
	SQInteger onRespawn(int playerID);
	SQInteger onStandUp(int playerID);
	SQInteger onDisconnect(int playerID, const char* reason);
	SQInteger onCommand(int playerID, const char* command, const char* params);
	SQInteger onPacket(int playerID, const char* data);
	SQInteger onAdminCommand(int playerID, const char* command);
	SQInteger onMessage(int playerID, const char* message);
	SQInteger onTake(int playerID, int itemID, const char* itemInstance, int amount, const char* world);
	SQInteger onDrop(int playerID, int itemID, const char* itemInstance, int amount, const char* world);
	SQInteger onTakeFocus(int playerID, int focusID);
	SQInteger onLostFocus(int playerID, int focusID);
};

#endif //SCALLBACK_H