#ifndef SFUNCTION_H
#define SFUNCTION_H

namespace SFunction
{
	void bindGOFunctions(HSQUIRRELVM vm);

	SQInteger getTickCount(HSQUIRRELVM vm);
	SQInteger getPlayerName(HSQUIRRELVM vm);
	SQInteger getPlayerPing(HSQUIRRELVM vm);
	SQInteger setPlayerVirtualWorld(HSQUIRRELVM vm);
	SQInteger getPlayerVirtualWorld(HSQUIRRELVM vm);
	SQInteger isConnected(HSQUIRRELVM vm);
	SQInteger sendMessageToAll(HSQUIRRELVM vm);
	SQInteger sendMessage(HSQUIRRELVM vm);
	SQInteger sendPacket(HSQUIRRELVM vm);
	SQInteger getPosition(HSQUIRRELVM vm);
	SQInteger getDistance3D(HSQUIRRELVM vm);
	SQInteger getDistance2D(HSQUIRRELVM vm);
	SQInteger isAdmin(HSQUIRRELVM vm);
	SQInteger getMaxSlots(HSQUIRRELVM vm);
	SQInteger getPlayersCount(HSQUIRRELVM vm);
	SQInteger sscanf(HSQUIRRELVM vm);
	SQInteger rgbToHex(HSQUIRRELVM vm);
	SQInteger hexToRGB(HSQUIRRELVM vm);
	SQInteger md5(HSQUIRRELVM vm);
	SQInteger sha1(HSQUIRRELVM vm);
	SQInteger sha256(HSQUIRRELVM vm);
	SQInteger sha384(HSQUIRRELVM vm);
	SQInteger sha512(HSQUIRRELVM vm);
	SQInteger setTimer(HSQUIRRELVM vm);
	SQInteger killTimer(HSQUIRRELVM vm);
	SQInteger setTimerInterval(HSQUIRRELVM vm);
	SQInteger setTimerRepeat(HSQUIRRELVM vm);
	SQInteger setTimerData(HSQUIRRELVM vm);
	SQInteger getServerDescription(HSQUIRRELVM vm);
	SQInteger setServerDescription(HSQUIRRELVM vm);
	SQInteger getServerWorld(HSQUIRRELVM vm);
	SQInteger setServerWorld(HSQUIRRELVM vm);
	SQInteger kick(HSQUIRRELVM vm);
	SQInteger ban(HSQUIRRELVM vm);
	SQInteger enableUnconscious(HSQUIRRELVM vm);
	SQInteger createItem(HSQUIRRELVM vm);
	SQInteger destroyItem(HSQUIRRELVM vm);
	SQInteger callClientFunc(HSQUIRRELVM vm);
	SQInteger setPlayerInvisible(HSQUIRRELVM vm);
	SQInteger isPlayerInvisible(HSQUIRRELVM vm);
};

#endif //SFUNCTION_H