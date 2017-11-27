#ifndef SFUNCTION_H
#define SFUNCTION_H

namespace SFunction
{
	void bindGOFunctions(HSQUIRRELVM &VM);
	
	SQInteger addMessage(HSQUIRRELVM vm);
	SQInteger showChat(HSQUIRRELVM vm);
	SQInteger isChatShowed(HSQUIRRELVM vm);
	SQInteger clearChat(HSQUIRRELVM vm);
	
	SQInteger disableKey(HSQUIRRELVM vm);
	SQInteger exit(HSQUIRRELVM vm);
	SQInteger enableGameNpcs(HSQUIRRELVM vm);
	SQInteger enableGameKeys(HSQUIRRELVM vm);
	SQInteger enableInterface(HSQUIRRELVM vm);
	SQInteger enableEq(HSQUIRRELVM vm);
	SQInteger setTime(HSQUIRRELVM vm);
	SQInteger getTime(HSQUIRRELVM vm);
	SQInteger getPing(HSQUIRRELVM vm);

	SQInteger getTickCount(HSQUIRRELVM vm);
	SQInteger sendPacket(HSQUIRRELVM vm);
	SQInteger getDistance3D(HSQUIRRELVM vm);
	SQInteger getDistance2D(HSQUIRRELVM vm);
	SQInteger sscanf(HSQUIRRELVM vm);
	SQInteger rgbToHex(HSQUIRRELVM vm);
	SQInteger hexToRGB(HSQUIRRELVM vm);
	SQInteger getResolution(HSQUIRRELVM vm);

	SQInteger getName(HSQUIRRELVM vm);
	SQInteger getHealth(HSQUIRRELVM vm);
	SQInteger getMaxHealth(HSQUIRRELVM vm);
	SQInteger getMana(HSQUIRRELVM vm);
	SQInteger getMaxMana(HSQUIRRELVM vm);
	SQInteger getStrength(HSQUIRRELVM vm);
	SQInteger getDexterity(HSQUIRRELVM vm);
	SQInteger setHealth(HSQUIRRELVM vm);
	SQInteger setMaxHealth(HSQUIRRELVM vm);
	SQInteger setMana(HSQUIRRELVM vm);
	SQInteger setMaxMana(HSQUIRRELVM vm);
	SQInteger setStrength(HSQUIRRELVM vm);
	SQInteger setDexterity(HSQUIRRELVM vm);
	SQInteger getPosition(HSQUIRRELVM vm);
	SQInteger setPosition(HSQUIRRELVM vm);
	SQInteger getAngle(HSQUIRRELVM vm);
	SQInteger setAngle(HSQUIRRELVM vm);
	SQInteger setLevel(HSQUIRRELVM vm);
	SQInteger getLevel(HSQUIRRELVM vm);
	SQInteger setExperience(HSQUIRRELVM vm);
	SQInteger getExperience(HSQUIRRELVM vm);
	SQInteger setNextLevelExperience(HSQUIRRELVM vm);
	SQInteger getNextLevelExperience(HSQUIRRELVM vm);
	SQInteger setLearnPoints(HSQUIRRELVM vm);
	SQInteger getLearnPoints(HSQUIRRELVM vm);
	SQInteger setSkillOpenLocks(HSQUIRRELVM vm);
	SQInteger getSkillOpenLocksLevel(HSQUIRRELVM vm);
	SQInteger getSkillOpenLocksValue(HSQUIRRELVM vm);
	SQInteger setSkillPickPocket(HSQUIRRELVM vm);
	SQInteger getSkillPickPocketLevel(HSQUIRRELVM vm);
	SQInteger getSkillPickPocketValue(HSQUIRRELVM vm);
	SQInteger setMagicLevel(HSQUIRRELVM vm);
	SQInteger getMagicLevel(HSQUIRRELVM vm);
	SQInteger setAcrobatic(HSQUIRRELVM vm);
	SQInteger getAcrobatic(HSQUIRRELVM vm);
	SQInteger setSneak(HSQUIRRELVM vm);
	SQInteger getSneak(HSQUIRRELVM vm);
	//SQInteger setProtection(HSQUIRRELVM vm);
	//SQInteger getProtection(HSQUIRRELVM vm);
	SQInteger completeHeal(HSQUIRRELVM vm);
	SQInteger isDead(HSQUIRRELVM vm);
	SQInteger isUnconscious(HSQUIRRELVM vm);
	SQInteger setFreeze(HSQUIRRELVM vm);
	SQInteger isFrozen(HSQUIRRELVM vm);
	SQInteger getFocus(HSQUIRRELVM vm);

	SQInteger clearInventory(HSQUIRRELVM vm);
	SQInteger openInventory(HSQUIRRELVM vm);
	SQInteger closeInventory(HSQUIRRELVM vm);

	SQInteger getItemName(HSQUIRRELVM vm);
	SQInteger getItemDescription(HSQUIRRELVM vm);
	SQInteger getItemValue(HSQUIRRELVM vm);
	SQInteger giveItem(HSQUIRRELVM vm);
	SQInteger removeItem(HSQUIRRELVM vm);
	SQInteger equipArmor(HSQUIRRELVM vm);
	SQInteger unequipArmor(HSQUIRRELVM vm);
	SQInteger equipMeleeWeapon(HSQUIRRELVM vm);
	SQInteger unequipMeleeWeapon(HSQUIRRELVM vm);
	SQInteger equipRangedWeapon(HSQUIRRELVM vm);
	SQInteger unequipRangedWeapon(HSQUIRRELVM vm);
	SQInteger getArmorInstance(HSQUIRRELVM vm);
	SQInteger getMeleeInstance(HSQUIRRELVM vm);
	SQInteger getRangedInstance(HSQUIRRELVM vm);
	SQInteger getWeaponMode(HSQUIRRELVM vm);
	SQInteger setWeaponMode(HSQUIRRELVM vm);
	SQInteger playAnimation(HSQUIRRELVM vm);

	SQInteger createDraw(HSQUIRRELVM vm);
	SQInteger destroyDraw(HSQUIRRELVM vm);
	SQInteger setDrawVisible(HSQUIRRELVM vm);
	SQInteger isDrawVisible(HSQUIRRELVM vm);
	SQInteger setDrawPosition(HSQUIRRELVM vm);
	SQInteger setDrawText(HSQUIRRELVM vm);
	SQInteger setDrawFont(HSQUIRRELVM vm);
	SQInteger setDrawColor(HSQUIRRELVM vm);
	SQInteger getDrawPosition(HSQUIRRELVM vm);

	SQInteger setCursorVisible(HSQUIRRELVM vm);
	SQInteger isCursorVisible(HSQUIRRELVM vm);
	SQInteger getCursorPos(HSQUIRRELVM vm);
	SQInteger setCursorPos(HSQUIRRELVM vm);
	SQInteger getCursorSensitivity(HSQUIRRELVM vm);
	SQInteger setCursorSensitivity(HSQUIRRELVM vm);
	SQInteger setCursorTexture(HSQUIRRELVM vm);
	SQInteger getCursorTexture(HSQUIRRELVM vm);
	SQInteger isClicked(HSQUIRRELVM vm);

	SQInteger createTexture(HSQUIRRELVM vm);
	SQInteger destroyTexture(HSQUIRRELVM vm);
	SQInteger setTexture(HSQUIRRELVM vm);
	SQInteger getTexture(HSQUIRRELVM vm);
	SQInteger setTexturePosition(HSQUIRRELVM vm);
	SQInteger getTexturePosition(HSQUIRRELVM vm);
	SQInteger setTextureSize(HSQUIRRELVM vm);
	SQInteger getTextureSize(HSQUIRRELVM vm);
	SQInteger setTextureVisible(HSQUIRRELVM vm);
	SQInteger isTextureVisible(HSQUIRRELVM vm);
	
	SQInteger md5File(HSQUIRRELVM vm);
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

	SQInteger setCameraBeforeHero(HSQUIRRELVM vm);
	SQInteger setDefaultCamera(HSQUIRRELVM vm);

	SQInteger setWorld(HSQUIRRELVM vm);
	SQInteger getWorld(HSQUIRRELVM vm);

	SQInteger setSavingEnabled(HSQUIRRELVM vm);
	SQInteger isSavingEnabled(HSQUIRRELVM vm);

	SQInteger setInstance(HSQUIRRELVM vm);
	SQInteger getInstance(HSQUIRRELVM vm);

	SQInteger setWeaponSkill(HSQUIRRELVM vm);
	SQInteger getWeaponSkill(HSQUIRRELVM vm);
	SQInteger getAnimationID(HSQUIRRELVM vm);
	SQInteger getAnimationName(HSQUIRRELVM vm);
	SQInteger getAdditionalVisual(HSQUIRRELVM vm);
	SQInteger setAdditionalVisual(HSQUIRRELVM vm);
	SQInteger hasItem(HSQUIRRELVM vm);
	SQInteger getEq(HSQUIRRELVM vm);
	SQInteger sendVisual(HSQUIRRELVM vm);
	SQInteger applyOverlay(HSQUIRRELVM vm);
	SQInteger removeOverlay(HSQUIRRELVM vm);

	SQInteger checkPrograms(HSQUIRRELVM vm);

	SQInteger createVob(HSQUIRRELVM vm);
	SQInteger destroyVob(HSQUIRRELVM vm);
	SQInteger getVobRotation(HSQUIRRELVM vm);
	SQInteger setVobRotation(HSQUIRRELVM vm);
	SQInteger getVobPosition(HSQUIRRELVM vm);
	SQInteger setVobPosition(HSQUIRRELVM vm);
	SQInteger setVobCollision(HSQUIRRELVM vm);
	SQInteger setCameraBehindVob(HSQUIRRELVM vm);
	SQInteger destroyAllVobInWorld(HSQUIRRELVM vm);
	SQInteger destroyVobsInWorld(HSQUIRRELVM vm);
	SQInteger enableCameraMovement(HSQUIRRELVM vm);
	SQInteger enableResetModel(HSQUIRRELVM vm);
	SQInteger resetModel(HSQUIRRELVM vm);
	SQInteger enableMarvin(HSQUIRRELVM vm);
	SQInteger showPlayerStatus(HSQUIRRELVM vm);
	SQInteger callServerFunc(HSQUIRRELVM vm);
	SQInteger getTextWidth(HSQUIRRELVM vm);
	SQInteger getFontHeight(HSQUIRRELVM vm);
	SQInteger getLetterWidth(HSQUIRRELVM vm);
	SQInteger getLetterDistance(HSQUIRRELVM vm);
	SQInteger getLanguage(HSQUIRRELVM vm);
};

#endif //SFUNCTION_H