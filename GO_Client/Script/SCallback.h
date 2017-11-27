#ifndef SCALLBACK_H
#define SCALLBACK_H

namespace SCallback
{
	int onInit();
	int onRender();
	int onCommand(RakString command, RakString params);
	int onPacket(const char* data);
	int onClick(const char* button, int x, int y, int wheel);
	int onKey(int key);
	int onHit();
	int onDie();
	int onRespawn();
	int onUnconscious();
	int onStandUp();
	int onProgramName(const char* windowText);
	int onOpenInventory();
	int onCloseInventory();
	int onMobTrigger(oCMobInter *mob);
	int onMobUntrigger(oCMobInter *mob);
	int onUseItem(const char *instance, int amount, int hand);
	int onTakeFocus(int id, const char *name, float x, float y, float z);
	int onLostFocus(int id, const char *name);
	int onRenderNickname(int id, const char *name, int x, int y);
};

#endif //SCALLBACK_H