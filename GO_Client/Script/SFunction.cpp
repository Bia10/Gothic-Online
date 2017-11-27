#include "..\\stdafx.h"

void SFunction::bindGOFunctions(HSQUIRRELVM &vm)
{
	SQ_REGISTER_GLOBAL_FUNC(vm, "addMessage", SFunction::addMessage);
	SQ_REGISTER_GLOBAL_FUNC(vm, "showChat", SFunction::showChat);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isChatShowed", SFunction::isChatShowed);
	SQ_REGISTER_GLOBAL_FUNC(vm, "clearChat", SFunction::clearChat);
	SQ_REGISTER_GLOBAL_FUNC(vm, "exitGame", SFunction::exit);
	SQ_REGISTER_GLOBAL_FUNC(vm, "disableKey", SFunction::disableKey);
	SQ_REGISTER_GLOBAL_FUNC(vm, "enableGameNpcs", SFunction::enableGameNpcs);
	SQ_REGISTER_GLOBAL_FUNC(vm, "enableGameKeys", SFunction::enableGameKeys);
	SQ_REGISTER_GLOBAL_FUNC(vm, "enableInterface", SFunction::enableInterface);
	SQ_REGISTER_GLOBAL_FUNC(vm, "enableEq", SFunction::enableEq);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setTime", SFunction::setTime);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getTime", SFunction::getTime);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getPing", SFunction::getPing);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getTickCount", SFunction::getTickCount);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sendPacket", SFunction::sendPacket);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getDistance3D", SFunction::getDistance3D);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getDistance2D", SFunction::getDistance2D);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sscanf", SFunction::sscanf);
	SQ_REGISTER_GLOBAL_FUNC(vm, "rgbToHex", SFunction::rgbToHex);
	SQ_REGISTER_GLOBAL_FUNC(vm, "hexToRGB", SFunction::hexToRGB);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getResolution", SFunction::getResolution);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getName", SFunction::getName);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getHealth", SFunction::getHealth);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getMaxHealth", SFunction::getMaxHealth);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getMana", SFunction::getMana);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getMaxMana", SFunction::getMaxMana);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getDexterity", SFunction::getDexterity);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getStrength", SFunction::getStrength);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setHealth", SFunction::setHealth);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setMaxHealth", SFunction::setMaxHealth);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setMana", SFunction::setMana);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setMaxMana", SFunction::setMaxMana);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setDexterity", SFunction::setDexterity);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setStrength", SFunction::setStrength);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getPosition", SFunction::getPosition);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setPosition", SFunction::setPosition);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getAngle", SFunction::getAngle);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setAngle", SFunction::setAngle);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setLevel", SFunction::setLevel);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getLevel", SFunction::getLevel);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setExperience", SFunction::setExperience);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getExperience", SFunction::getExperience);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setNextLevelExperience", SFunction::setNextLevelExperience);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getNextLevelExperience", SFunction::getNextLevelExperience);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setLearnPoints", SFunction::setLearnPoints);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getLearnPoints", SFunction::getLearnPoints);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setSkillOpenLocks", SFunction::setSkillOpenLocks);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getSkillOpenLocksLevel", SFunction::getSkillOpenLocksLevel);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getSkillOpenLocksValue", SFunction::getSkillOpenLocksValue);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setSkillPickPocket", SFunction::setSkillPickPocket);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getSkillPickPocketLevel", SFunction::getSkillPickPocketLevel);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getSkillPickPocketValue", SFunction::getSkillPickPocketValue);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setMagicLevel", SFunction::setMagicLevel);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getMagicLevel", SFunction::getMagicLevel);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setAcrobatic", SFunction::setAcrobatic);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getAcrobatic", SFunction::getAcrobatic);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setSneak", SFunction::setSneak);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getSneak", SFunction::getSneak);
	/*
	SQ_REGISTER_GLOBAL_FUNC(vm, "setProtection", SFunction::setProtection);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getProtection", SFunction::getProtection);
	*/
	SQ_REGISTER_GLOBAL_FUNC(vm, "completeHeal", SFunction::completeHeal);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isDead", SFunction::isDead);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isUnconscious", SFunction::isUnconscious);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setFreeze", SFunction::setFreeze);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isFrozen", SFunction::isFrozen);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getFocus", SFunction::getFocus);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getItemName", SFunction::getItemName);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getItemDescription", SFunction::getItemDescription);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getItemValue", SFunction::getItemValue);
	SQ_REGISTER_GLOBAL_FUNC(vm, "giveItem", SFunction::giveItem);
	SQ_REGISTER_GLOBAL_FUNC(vm, "removeItem", SFunction::removeItem);
	SQ_REGISTER_GLOBAL_FUNC(vm, "equipArmor", SFunction::equipArmor);
	SQ_REGISTER_GLOBAL_FUNC(vm, "unequipArmor", SFunction::unequipArmor);
	SQ_REGISTER_GLOBAL_FUNC(vm, "equipMeleeWeapon", SFunction::equipMeleeWeapon);
	SQ_REGISTER_GLOBAL_FUNC(vm, "unequipMeleeWeapon", SFunction::unequipMeleeWeapon);
	SQ_REGISTER_GLOBAL_FUNC(vm, "equipRangedWeapon", SFunction::equipRangedWeapon);
	SQ_REGISTER_GLOBAL_FUNC(vm, "unequipRangedWeapon", SFunction::unequipRangedWeapon);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getArmorInstance", SFunction::getArmorInstance);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getMeleeInstance", SFunction::getMeleeInstance);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getRangedInstance", SFunction::getRangedInstance);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getWeaponMode", SFunction::getWeaponMode);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setWeaponMode", SFunction::setWeaponMode);
	SQ_REGISTER_GLOBAL_FUNC(vm, "clearInventory", SFunction::clearInventory);
	SQ_REGISTER_GLOBAL_FUNC(vm, "openInventory", SFunction::openInventory);
	SQ_REGISTER_GLOBAL_FUNC(vm, "closeInventory", SFunction::closeInventory);
	SQ_REGISTER_GLOBAL_FUNC(vm, "playAnimation", SFunction::playAnimation);
	SQ_REGISTER_GLOBAL_FUNC(vm, "createDraw", SFunction::createDraw);
	SQ_REGISTER_GLOBAL_FUNC(vm, "destroyDraw", SFunction::destroyDraw);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setDrawVisible", SFunction::setDrawVisible);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isDrawVisible", SFunction::isDrawVisible);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setDrawPosition", SFunction::setDrawPosition);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getDrawPosition", SFunction::getDrawPosition);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setDrawText", SFunction::setDrawText);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setDrawFont", SFunction::setDrawFont);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setDrawColor", SFunction::setDrawColor);
	SQ_REGISTER_GLOBAL_FUNC(vm, "createTexture", SFunction::createTexture);
	SQ_REGISTER_GLOBAL_FUNC(vm, "destroyTexture", SFunction::destroyTexture);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setTexture", SFunction::setTexture);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getTexture", SFunction::getTexture);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setTexturePosition", SFunction::setTexturePosition);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getTexturePosition", SFunction::getTexturePosition);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setTextureSize", SFunction::setTextureSize);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getTextureSize", SFunction::getTextureSize);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setTextureVisible", SFunction::setTextureVisible);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isTextureVisible", SFunction::isTextureVisible);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setCursorVisible", SFunction::setCursorVisible);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isCursorVisible", SFunction::isCursorVisible);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getCursorPosition", SFunction::getCursorPos);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setCursorPosition", SFunction::setCursorPos);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getCursorSensitivity", SFunction::getCursorSensitivity);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setCursorSensitivity", SFunction::setCursorSensitivity);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setCursorTexture", SFunction::setCursorTexture);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getCursorTexture", SFunction::getCursorTexture);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isClicked", SFunction::isClicked);
	SQ_REGISTER_GLOBAL_FUNC(vm, "md5File", SFunction::md5File);
	SQ_REGISTER_GLOBAL_FUNC(vm, "md5", SFunction::md5);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sha1", SFunction::sha1);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sha256", SFunction::sha256);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sha384", SFunction::sha384);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sha512", SFunction::sha512);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setTimer", SFunction::setTimer);
	SQ_REGISTER_GLOBAL_FUNC(vm, "killTimer", SFunction::killTimer);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setTimerInterval", SFunction::setTimerInterval);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setTimerRepeat", SFunction::setTimerRepeat);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setTimerData", SFunction::setTimerData);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setCameraBeforeHero", SFunction::setCameraBeforeHero);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setDefaultCamera", SFunction::setDefaultCamera);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setWorld", SFunction::setWorld);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getWorld", SFunction::getWorld);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setSavingEnabled", SFunction::setSavingEnabled);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isSavingEnabled", SFunction::isSavingEnabled);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getInstance", SFunction::getInstance);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setInstance", SFunction::setInstance);
	SQ_REGISTER_GLOBAL_FUNC(vm, "checkPrograms", SFunction::checkPrograms);
	SQ_REGISTER_GLOBAL_FUNC(vm, "createVob", SFunction::createVob);
	SQ_REGISTER_GLOBAL_FUNC(vm, "destroyVob", SFunction::destroyVob);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getVobRotation", SFunction::getVobRotation);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setVobRotation", SFunction::setVobRotation);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getVobPosition", SFunction::getVobPosition);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setVobPosition", SFunction::setVobPosition);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setCameraBehindVob", SFunction::setCameraBehindVob);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setVobCollision", SFunction::setVobCollision);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setWeaponSkill", SFunction::setWeaponSkill);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getWeaponSkill", SFunction::getWeaponSkill);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getAnimationID", SFunction::getAnimationID);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getAnimationName", SFunction::getAnimationName);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getAdditionalVisual", SFunction::getAdditionalVisual);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setAdditionalVisual", SFunction::setAdditionalVisual);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sendVisual", SFunction::sendVisual);
	SQ_REGISTER_GLOBAL_FUNC(vm, "hasItem", SFunction::hasItem);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getEq", SFunction::getEq);
	SQ_REGISTER_GLOBAL_FUNC(vm, "applyOverlay", SFunction::applyOverlay);
	SQ_REGISTER_GLOBAL_FUNC(vm, "removeOverlay", SFunction::removeOverlay);
	SQ_REGISTER_GLOBAL_FUNC(vm, "destroyAllVobInWorld", SFunction::destroyAllVobInWorld);
	SQ_REGISTER_GLOBAL_FUNC(vm, "destroyVobsInWorld", SFunction::destroyVobsInWorld);
	SQ_REGISTER_GLOBAL_FUNC(vm, "enableCameraMovement", SFunction::enableCameraMovement);
	SQ_REGISTER_GLOBAL_FUNC(vm, "enableResetModel", SFunction::enableResetModel);
	SQ_REGISTER_GLOBAL_FUNC(vm, "resetModel", SFunction::resetModel);
	SQ_REGISTER_GLOBAL_FUNC(vm, "enableMarvin", SFunction::enableMarvin);
	SQ_REGISTER_GLOBAL_FUNC(vm, "showPlayerStatus", SFunction::showPlayerStatus);
	SQ_REGISTER_GLOBAL_FUNC(vm, "callServerFunc", SFunction::callServerFunc);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getTextWidth", SFunction::getTextWidth);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getFontHeight", SFunction::getFontHeight);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getLetterWidth", SFunction::getLetterWidth);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getLetterDistance", SFunction::getLetterDistance);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getLanguage", SFunction::getLanguage);
};

SQInteger SFunction::addMessage(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 4);
	SQ_CHECK_PARAM_INT(vm, r, 0);
	SQ_CHECK_PARAM_INT(vm, g, 1);
	SQ_CHECK_PARAM_INT(vm, b, 2);
	SQ_CHECK_PARAM_STRING(vm, message, 3);
	
	core.GetChat()->AddLine(RakString(message),zCOLOR(r,g,b,255));

	return 0;
};

SQInteger SFunction::showChat(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	core.GetChat()->Show(enable);

	return 0;
}

SQInteger SFunction::isChatShowed(HSQUIRRELVM vm)
{
	sq_pushbool(vm, core.GetChat()->IsShowing());
	return 1;
}

SQInteger SFunction::exit(HSQUIRRELVM vm)
{
	core.GetNetwork()->Disconnect();
	CGameManager::GetGameManager()->ExitGame();
	ExitProcess(0);

	return 0;
};

SQInteger SFunction::disableKey(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, key, 0);
	SQ_CHECK_PARAM_BOOL(vm, toggle, 1);
	
	//SetKeyEnabled enables key, disableKey disables key, so must be !toggle
	scr.GetScriptKeys()->SetKeyEnabled(key, !toggle);

	return 0;
};

SQInteger SFunction::enableGameNpcs(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	oCSpawnManager* spawnManager = oCGame::GetGame()->GetSpawnManager();
	if (spawnManager)
	{
		spawnManager->SetSpawningEnabled(enable);
		scr.GetScriptVars()->isSpawningEnabled = enable;
	}
	//Chujowa metoda, nie polecam, gdy diego nie chce zniknac
	if (!enable)
	{
		oCNpc* focus = oCNpc::GetHero()->GetFocusNpc();
		if (focus)
			focus->DestroyNpc();
		else if ((focus = oCNpc::GetHero()->GetNextEnemy()))
			focus->DestroyNpc();
	}

	return 0;
};

SQInteger SFunction::enableGameKeys(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	scr.GetScriptVars()->isKeyEnabled = enable;

	return 0;
};

SQInteger SFunction::enableInterface(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	scr.GetScriptVars()->isInterfaceEnabled = enable;

	return 0;
};

SQInteger SFunction::enableEq(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	scr.GetScriptVars()->isEqEnabled = enable;

	return 0;
};

SQInteger SFunction::setTime(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, hour, 0);
	SQ_CHECK_PARAM_INT(vm, minute, 1);

	oCGame::GetGame()->SetTime(0, hour, minute);

	return 0;
};

SQInteger SFunction::getTime(HSQUIRRELVM vm)
{
	int day, hour, minute;
	oCGame::GetGame()->GetTime(day, hour, minute);

	sq_newtable(vm);
	SQ_TABLE_SET_INT(vm, "hour", hour);
	SQ_TABLE_SET_INT(vm, "min", minute);

	return 1;
};

SQInteger SFunction::getPing(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, core.GetNetwork()->GetPeer()->GetLastPing(core.GetNetwork()->GetServerAddress()));

	return 1;
};

SQInteger SFunction::getTickCount(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, (int)::GetTickCount());

	return 1;
};

SQInteger SFunction::sendPacket(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, priority, 0);
	SQ_CHECK_PARAM_STRING(vm, data, 1);

	CNetwork* net = core.GetNetwork();
	if( net->IsConnected() == true )
	{
		BitStream s;
		s.Write((MessageID)GO_SCRIPT);
		s.Write((MessageID)SCRIPT_PACKET);
		s.Write(RakString(data));

		switch (priority)
		{
		case 0:
			net->GetPeer()->Send(&s, LOW_PRIORITY, UNRELIABLE, 0, net->GetServerAddress(), false);
			break;

		case 1:
			net->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
			break;

		case 2:
			net->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE_ORDERED, 0, net->GetServerAddress(), false);
			break;
		}
		
	}

	return 0;
};

SQInteger SFunction::getDistance3D(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 6);
	SQ_CHECK_PARAM_FLOAT(vm, x, 0);
	SQ_CHECK_PARAM_FLOAT(vm, y, 1);
	SQ_CHECK_PARAM_FLOAT(vm, z, 2);
	SQ_CHECK_PARAM_FLOAT(vm, x2, 3);
	SQ_CHECK_PARAM_FLOAT(vm, y2, 4);
	SQ_CHECK_PARAM_FLOAT(vm, z2, 5);

	sq_pushfloat(vm, goMath::GetDistance3D(x, y, z, x2, y2, z2));

	return 1;
};

SQInteger SFunction::getDistance2D(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 4);
	SQ_CHECK_PARAM_FLOAT(vm, a, 0);
	SQ_CHECK_PARAM_FLOAT(vm, b, 1);
	SQ_CHECK_PARAM_FLOAT(vm, c, 2);
	SQ_CHECK_PARAM_FLOAT(vm, d, 3);

	sq_pushfloat(vm, goMath::GetDistance2D(a, b, c, d));

	return 1;
};

SQInteger SFunction::sscanf(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_STRING(vm, params, 0);
	SQ_CHECK_PARAM_STRING(vm, command, 1);

	std::vector<std::string> elements;
	if (utility::sscanf(params, command, elements))
	{
		int stackTop = sq_gettop(vm);
		sq_newarray(vm, 0);

		int p1;
		float p2;

		for (int i = 0; i < strlen(params); ++i)
		{
			switch (params[i])
			{
			case 'd':
				if (std::sscanf(elements[i].c_str(), "%d", &p1))
				{
					SQ_ARRAY_INT(vm, p1);
				}
				else
				{
					sq_settop(vm, stackTop);
					sq_pushbool(vm, false);

					return 1;
				}
				break;

			case 'f':
				if (std::sscanf(elements[i].c_str(), "%f", &p2))
				{
					SQ_ARRAY_FLOAT(vm, p2);
				}
				else
				{
					sq_settop(vm, stackTop);
					sq_pushbool(vm, false);

					return 1;
				}
				break;

			case 's':
				SQ_ARRAY_STRING(vm, elements[i].c_str());
				break;
			}
		}
	}
	else
		sq_pushbool(vm, false);

	return 1;
}

SQInteger SFunction::rgbToHex(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 3);
	SQ_CHECK_PARAM_INT(vm, r, 0);
	SQ_CHECK_PARAM_INT(vm, g, 1);
	SQ_CHECK_PARAM_INT(vm, b, 2);

	std::string colorHex = utility::RGBtoHex(r, g, b);

	sq_pushstring(vm, colorHex.c_str(), -1);

	return 1;
}

SQInteger SFunction::hexToRGB(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, hexColor, 0);

	int r, g, b;
	utility::HextoRGB(hexColor, &r, &g, &b);

	sq_newtable(vm);
	SQ_TABLE_SET_INT(vm, "r", r);
	SQ_TABLE_SET_INT(vm, "g", g);
	SQ_TABLE_SET_INT(vm, "b", b);

	return 1;
}

SQInteger SFunction::getResolution(HSQUIRRELVM vm)
{
	int width, height;

	zCView *view = scr.GetScriptVars()->GetView();
	view->GetPixelSize(width, height);

	sq_newtable(vm);
	SQ_TABLE_SET_INT(vm, "width", width);
	SQ_TABLE_SET_INT(vm, "height", height);

	return 1;
}

SQInteger SFunction::getName(HSQUIRRELVM vm)
{
	sq_pushstring(vm, core.GetConfig()->GetPlayerName().C_String(), -1);
	return 1;
};

SQInteger SFunction::getHealth(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetAttribute(NPC_ATR_HITPOINTS));
	return 1;
};

SQInteger SFunction::getMaxHealth(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetAttribute(NPC_ATR_HITPOINTS_MAX));
	return 1;
};

SQInteger SFunction::getMana(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetAttribute(NPC_ATR_MANA));
	return 1;
};

SQInteger SFunction::getMaxMana(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetAttribute(NPC_ATR_MANA_MAX));
	return 1;
};

SQInteger SFunction::getStrength(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetAttribute(NPC_ATR_STRENGTH));
	return 1;
};

SQInteger SFunction::getDexterity(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetAttribute(NPC_ATR_DEXTERITY));
	return 1;
};

SQInteger SFunction::setHealth(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, health, 0);

	oCNpc::GetHero()->SetAttribute(NPC_ATR_HITPOINTS, health);

	return 0;
};

SQInteger SFunction::setMaxHealth(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, maxhealth, 0);

	oCNpc::GetHero()->SetAttribute(NPC_ATR_HITPOINTS_MAX, maxhealth);

	return 0;
};

SQInteger SFunction::setMana(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, mana, 0);

	oCNpc::GetHero()->SetAttribute(NPC_ATR_MANA, mana);

	return 0;
};

SQInteger SFunction::setMaxMana(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, maxmana, 0);

	oCNpc::GetHero()->SetAttribute(NPC_ATR_MANA_MAX, maxmana);

	return 0;
};

SQInteger SFunction::setStrength(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, strength, 0);

	oCNpc::GetHero()->SetAttribute(NPC_ATR_STRENGTH, strength);

	return 0;
};

SQInteger SFunction::setDexterity(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, dexterity, 0);

	oCNpc::GetHero()->SetAttribute(NPC_ATR_DEXTERITY, dexterity);

	return 0;
};

SQInteger SFunction::getPosition(HSQUIRRELVM vm)
{
	zVEC3 pos = oCNpc::GetHero()->GetPosition();
	
	sq_newtable(vm);
	SQ_TABLE_SET_FLOAT(vm, "x", pos.x);
	SQ_TABLE_SET_FLOAT(vm, "y", pos.y);
	SQ_TABLE_SET_FLOAT(vm, "z", pos.z);

	return 1;
};

SQInteger SFunction::setPosition(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 3);
	SQ_CHECK_PARAM_FLOAT(vm, x, 0);
	SQ_CHECK_PARAM_FLOAT(vm, y, 1);
	SQ_CHECK_PARAM_FLOAT(vm, z, 2);

	// Lag fix
	CLocalPlayer *player = playerManager.GetLocalPlayer();
	player->pos.x = x; player->pos.y = y; player->pos.z = z;
	
	oCNpc::GetHero()->SetPosition(x, y, z);

	return 0;
};

SQInteger SFunction::getAngle(HSQUIRRELVM vm)
{
	sq_pushfloat(vm, oCNpc::GetHero()->GetHeading());
	return 1;
};

SQInteger SFunction::setAngle(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_FLOAT(vm, angle, 0);

	oCNpc::GetHero()->SetHeading(angle);

	return 0;
};

SQInteger SFunction::setLevel(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, level, 0);

	oCNpc::GetHero()->SetLevel(level >= 0 ? level : 0);

	return 0;
}

SQInteger SFunction::getLevel(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetLevel());
	return 1;
}

SQInteger SFunction::setExperience(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, experience, 0);

	oCNpc::GetHero()->SetExperience(experience >= 0 ? experience : 0);

	return 0;
}

SQInteger SFunction::getExperience(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetExperience());
	return 1;
}

SQInteger SFunction::setNextLevelExperience(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, experience, 0);

	oCNpc::GetHero()->SetExperienceNextLevel(experience >= 0 ? experience : 0);

	return 0;
}

SQInteger SFunction::getNextLevelExperience(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetExperienceNextLevel());
	return 1;
}

SQInteger SFunction::setLearnPoints(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, lp, 0);

	oCNpc::GetHero()->SetLearnPoints(lp >= 0 ? lp : 0);

	return 0;
}

SQInteger SFunction::getLearnPoints(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetLearnPoints());
	return 1;
}

SQInteger SFunction::setSkillOpenLocks(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, skill, 0);
	SQ_CHECK_PARAM_INT(vm, value, 1);

	oCNpc::GetHero()->SetOpenLock(skill, value);

	return 0;
}

SQInteger SFunction::getSkillOpenLocksLevel(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetTalentSkill(NPC_TALENT_PICKLOCK));
	return 1;
}

SQInteger SFunction::getSkillOpenLocksValue(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetTalentValue(NPC_TALENT_PICKLOCK));
	return 1;
}

SQInteger SFunction::setSkillPickPocket(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, skill, 0);
	SQ_CHECK_PARAM_INT(vm, value, 1);

	oCNpc::GetHero()->SetPickPocket(skill, value);

	return 0;
}

SQInteger SFunction::getSkillPickPocketLevel(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetTalentSkill(NPC_TALENT_PICKPOCKET));
	return 1;
}

SQInteger SFunction::getSkillPickPocketValue(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetTalentValue(NPC_TALENT_PICKPOCKET));
	return 1;
}

SQInteger SFunction::setMagicLevel(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, magic, 0);

	oCNpc::GetHero()->SetMagicLvl(magic >= 0 ? magic : 0);

	return 0;
}

SQInteger SFunction::getMagicLevel(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetMagicLvl());
	return 1;
}

SQInteger SFunction::setAcrobatic(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, acrobatic, 0);

	oCNpc::GetHero()->SetAcrobatic(acrobatic);

	return 0;
}

SQInteger SFunction::getAcrobatic(HSQUIRRELVM vm)
{
	sq_pushbool(vm, oCNpc::GetHero()->GetAcrobatic());
	return 1;
}

SQInteger SFunction::setSneak(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, sneak, 0);

	oCNpc::GetHero()->SetSneak(sneak);

	return 0;
}

SQInteger SFunction::getSneak(HSQUIRRELVM vm)
{
	sq_pushbool(vm, oCNpc::GetHero()->GetSneak());
	return 1;
}
/*
SQInteger SFunction::setProtection(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, type, 0);
	SQ_CHECK_PARAM_INT(vm, value, 1);

	oCNpc::GetHero()->SetProtection(type, value);

	return 0;
}

SQInteger SFunction::getProtection(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, type, 0);

	sq_pushinteger(vm, oCNpc::GetHero()->GetProtection(type));

	return 1;
}
*/
SQInteger SFunction::completeHeal(HSQUIRRELVM vm)
{
	oCNpc::GetHero()->CompleteHeal();
	return 0;
};

SQInteger SFunction::isDead(HSQUIRRELVM vm)
{
	sq_pushbool(vm, oCNpc::GetHero()->IsDead());
	return 0;
};

SQInteger SFunction::isUnconscious(HSQUIRRELVM vm)
{
	sq_pushbool(vm, oCNpc::GetHero()->IsUnconscious());
	return 0;
};

SQInteger SFunction::setFreeze(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, freeze, 0);

	scr.GetScriptVars()->SetFreeze(freeze);
	if (freeze) oCNpc::GetHero()->CloseInventory();

	return 0;
}

SQInteger SFunction::isFrozen(HSQUIRRELVM vm)
{
	sq_pushbool(vm, scr.GetScriptVars()->isFrozen);
	return 1;
}

SQInteger SFunction::getFocus(HSQUIRRELVM vm)
{
	oCNpc *focus = oCNpc::GetHero()->GetFocusNpc();
	if (focus)
	{
		sq_pushstring(vm, focus->GetName(0).ToChar(), -1);
	}
	else
		sq_pushbool(vm, false);

	return 1;
}

SQInteger SFunction::clearInventory(HSQUIRRELVM vm)
{
	oCNpc::GetHero()->ClearInventory();
	return 0;
};

SQInteger SFunction::openInventory(HSQUIRRELVM vm)
{
	oCNpc::GetHero()->OpenInventory();
	return 0;
};

SQInteger SFunction::closeInventory(HSQUIRRELVM vm)
{
	oCNpc::GetHero()->CloseInventory();
	return 0;
};

SQInteger SFunction::createDraw(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 7);
	SQ_CHECK_PARAM_STRING(vm, text, 0);
	SQ_CHECK_PARAM_STRING(vm, font, 1);
	SQ_CHECK_PARAM_INT(vm, x, 2);
	SQ_CHECK_PARAM_INT(vm, y, 3);
	SQ_CHECK_PARAM_INT(vm, r, 4);
	SQ_CHECK_PARAM_INT(vm, g, 5);
	SQ_CHECK_PARAM_INT(vm, b, 6);

	SDraw* new_Draw = new SDraw(text, font, x, y, zCOLOR(r, g, b, 255));
	if (new_Draw)
	{
		scr.GetScriptVars()->GetDrawList()->PushBack(new_Draw);
		int drawID = (long)new_Draw;
		sq_pushinteger(vm, drawID);

		return 1;
	}

	sq_error(vm, "(%s) cannot create new draw", __FUNCTION__);
	return 0;
};

SQInteger SFunction::destroyDraw(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, drawID, 0);

	if (drawID != 0)
	{
		SDraw* draw = (SDraw*)(long)drawID;
		if (draw)
		{
			scr.GetScriptVars()->GetDrawList()->Remove(draw);
			delete draw;
		}
	}

	return 0;
};

SQInteger SFunction::setDrawVisible(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, drawID, 0);
	SQ_CHECK_PARAM_BOOL(vm, enable, 1);

	if (drawID != 0)
	{
		SDraw* draw = (SDraw*)(long)drawID;
		if (draw)
		{
			draw->isVisible = enable;
		}
	}

	return 0;
};

SQInteger SFunction::isDrawVisible(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, drawID, 0);

	if (drawID != 0)
	{
		SDraw* draw = (SDraw*)(long)drawID;
		if (draw)
		{
			sq_pushbool(vm, draw->isVisible);
		}
	}

	return 1;
};

SQInteger SFunction::setDrawColor(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 4);
	SQ_CHECK_PARAM_INT(vm, drawID, 0);
	SQ_CHECK_PARAM_INT(vm, r, 1);
	SQ_CHECK_PARAM_INT(vm, g, 2);
	SQ_CHECK_PARAM_INT(vm, b, 3);

	if (drawID != 0)
	{
		SDraw* draw = (SDraw*)(long)drawID;
		if (draw)
		{
			draw->color = zCOLOR(r, g, b, 255);
		}
	}

	return 0;
};

SQInteger SFunction::setDrawFont(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, drawID, 0);
	SQ_CHECK_PARAM_STRING(vm, font, 1);

	if (drawID != 0)
	{
		SDraw* draw = (SDraw*)(long)drawID;
		if (draw)
		{
			draw->font = zSTRING(font);
		}
	}

	return 0;
};

SQInteger SFunction::setDrawPosition(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 3);
	SQ_CHECK_PARAM_INT(vm, drawID, 0);
	SQ_CHECK_PARAM_INT(vm, x, 1);
	SQ_CHECK_PARAM_INT(vm, y, 2);

	if (drawID != 0)
	{
		SDraw* draw = (SDraw*)(long)drawID;
		if (draw)
		{
			draw->pos[1] = x;
			draw->pos[2] = y;
		}
	}

	return 0;
};

SQInteger SFunction::setDrawText(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, drawID, 0);
	SQ_CHECK_PARAM_STRING(vm, text, 1);

	if (drawID != 0)
	{
		SDraw* draw = (SDraw*)(long)drawID;
		if (draw)
		{
			draw->text = zSTRING(text);
		}
	}

	return 0;
};

SQInteger SFunction::getDrawPosition(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, drawID, 0);

	if (drawID != 0)
	{
		SDraw* draw = (SDraw*)(long)drawID;
		if (draw)
		{
			sq_newtable(vm);
			SQ_TABLE_SET_INT(vm, "x", draw->pos[1]);
			SQ_TABLE_SET_INT(vm, "y", draw->pos[2]);

			return 1;
		}
	}

	return 0;
};

SQInteger SFunction::setCursorVisible(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, show, 0);

	zCursor::GetCursor().SetShowing(show);

	return 0;
};

SQInteger SFunction::isCursorVisible(HSQUIRRELVM vm)
{
	sq_pushbool(vm, zCursor::GetCursor().IsShowing());
	return 1;
};

SQInteger SFunction::getCursorPos(HSQUIRRELVM vm)
{
	MOUSEPOS pos = zCursor::GetCursor().GetPosition();

	sq_newtable(vm);
	SQ_TABLE_SET_INT(vm, "x", pos.x);
	SQ_TABLE_SET_INT(vm, "y", pos.y);
	SQ_TABLE_SET_FLOAT(vm, "wheel", pos.wheel);

	return 1;
};

SQInteger SFunction::setCursorPos(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, x, 0);
	SQ_CHECK_PARAM_INT(vm, y, 1);

	zCursor::GetCursor().SetPosition(x, y);

	return 0;
}

SQInteger SFunction::getCursorSensitivity(HSQUIRRELVM vm)
{
	sq_pushfloat(vm, zCursor::GetCursor().GetSensitivity());
	return 1;
}

SQInteger SFunction::setCursorSensitivity(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_FLOAT(vm, sensitivity, 0);

	if (sensitivity > 0.0f)
		zCursor::GetCursor().SetSensitivity(sensitivity);

	return 0;
}

SQInteger SFunction::setCursorTexture(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, texName, 0);

	zCursor::GetCursor().SetTexture(texName);

	return 0;
}

SQInteger SFunction::getCursorTexture(HSQUIRRELVM vm)
{
	sq_pushstring(vm, zCursor::GetCursor().GetTexture().ToChar(), -1);
	return 1;
}

SQInteger SFunction::isClicked(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, button, 0);

	if (strcmp(button, "LEFT") == 0)
		sq_pushbool(vm, zCursor::GetCursor().IsLeftBtnClicked());
	else if (strcmp(button, "RIGHT") == 0)
		sq_pushbool(vm, zCursor::GetCursor().IsRightBtnClicked());
	else if (strcmp(button, "WHEEL") == 0)
		sq_pushbool(vm, zCursor::GetCursor().IsWheelClicked());
	else
		sq_pushbool(vm, false);

	return 1;
};

SQInteger SFunction::createTexture(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 5);
	SQ_CHECK_PARAM_INT(vm, x, 0);
	SQ_CHECK_PARAM_INT(vm, y, 1);
	SQ_CHECK_PARAM_INT(vm, w, 2);
	SQ_CHECK_PARAM_INT(vm, h, 3);
	SQ_CHECK_PARAM_STRING(vm, textureString, 4);

	STexture* new_texture = new STexture(textureString, x, y, w, h);
	if (new_texture)
	{
		scr.GetScriptVars()->GetTextureList()->PushBack(new_texture);
		int texID = (long)new_texture;
		sq_pushinteger(vm, texID);
		return 1;
	}

	return 0;
};

SQInteger SFunction::destroyTexture(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, texID, 0);

	if (texID != 0)
	{
		STexture* tex = (STexture*)(long)texID;
		if (tex)
		{
			scr.GetScriptVars()->GetTextureList()->Remove(tex);
			delete tex;
		}
	}

	return 0;
};

SQInteger SFunction::setTexture(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, texID, 0);
	SQ_CHECK_PARAM_STRING(vm, texName, 1);

	if (texID != 0)
	{
		STexture* tex = (STexture*)(long)texID;
		if (tex)
		{
			tex->texName = texName;

			if (tex->isVisible == true)
			{
				zCView::GetScreen()->RemoveItem(tex);
				tex->texture->InsertBack(zSTRING(texName));
				zCView::GetScreen()->InsertItem(tex, true);
			}
			else
				tex->texture->InsertBack(zSTRING(texName));
		}
	}

	return 0;
};

SQInteger SFunction::getTexture(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, texID, 0);

	if (texID != 0)
	{
		STexture* tex = (STexture*)(long)texID;
		if (tex)
		{
			sq_pushstring(vm, tex->texName.ToChar(), -1);
		}
		else
			sq_pushbool(vm, false);
	}
	else
		sq_pushbool(vm, false);

	return 1;
};

SQInteger SFunction::setTexturePosition(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 3);
	SQ_CHECK_PARAM_INT(vm, texID, 0);
	SQ_CHECK_PARAM_INT(vm, x, 1);
	SQ_CHECK_PARAM_INT(vm, y, 2);

	if (texID != 0)
	{
		STexture* tex = (STexture*)(long)texID;
		if (tex)
		{
			tex->pos[1] = x;
			tex->pos[2] = y;
			
			if (tex->isVisible == true)
				tex->texture->SetPos(x, y);
		}
	}

	return 0;
};

SQInteger SFunction::getTexturePosition(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, texID, 0);

	if (texID != 0)
	{
		STexture* tex = (STexture*)(long)texID;
		if (tex)
		{
			sq_newtable(vm);
			SQ_TABLE_SET_INT(vm, "x", tex->pos[1]);
			SQ_TABLE_SET_INT(vm, "y", tex->pos[2]);
		}
		else
			sq_pushbool(vm, false);
	}
	else
		sq_pushbool(vm, false);

	return 1;
};

SQInteger SFunction::setTextureSize(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 3);
	SQ_CHECK_PARAM_INT(vm, texID, 0);
	SQ_CHECK_PARAM_INT(vm, w, 1);
	SQ_CHECK_PARAM_INT(vm, h, 2);

	if (texID != 0)
	{
		STexture* tex = (STexture*)(long)texID;
		if (tex)
		{
			tex->pos[3] = w;
			tex->pos[4] = h;
			
			if (tex->isVisible == true)
				tex->texture->SetSize(w, h);
		}
	}

	return 0;
};

SQInteger SFunction::getTextureSize(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, texID, 0);

	if (texID != 0)
	{
		STexture* tex = (STexture*)(long)texID;
		if (tex)
		{
			sq_newtable(vm);
			SQ_TABLE_SET_INT(vm, "width", tex->pos[3]);
			SQ_TABLE_SET_INT(vm, "height", tex->pos[4]);
		}
		else
			sq_pushbool(vm, false);
	}
	else
		sq_pushbool(vm, false);

	return 1;
};

SQInteger SFunction::setTextureVisible(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, texID, 0);
	SQ_CHECK_PARAM_BOOL(vm, enable, 1);

	if (texID != 0)
	{
		STexture* tex = (STexture*)(long)texID;
		if (tex)
		{
			if (enable == 0 && tex->isVisible == true)
				tex->SetVisible(false);
			else if (enable == 1 && tex->isVisible == false)
				tex->SetVisible(true);
		}
	}

	return 0;
};

SQInteger SFunction::isTextureVisible(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, texID, 0);

	if (texID != 0)
	{
		STexture* tex = (STexture*)(long)texID;
		if (tex)
		{
			sq_pushbool(vm, tex->isVisible);
		}
	}
	else
		sq_pushbool(vm, false);

	return 2;
};

SQInteger SFunction::md5File(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, filename, 0);

	md5wrapper md5;
	sq_pushstring(vm, md5.getHashFromFile(filename).c_str(), -1);

	return 1;
};

SQInteger SFunction::md5(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, text, 0);

	md5wrapper md5;
	sq_pushstring(vm, md5.getHashFromString(text).c_str(), -1);

	return 1;
};

SQInteger SFunction::sha1(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, text, 0);

	sha1wrapper sha1;
	sq_pushstring(vm, sha1.getHashFromString(text).c_str(), -1);

	return 1;
};

SQInteger SFunction::sha256(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, text, 0);

	sha256wrapper sha256;
	sq_pushstring(vm, sha256.getHashFromString(text).c_str(), -1);

	return 1;
};

SQInteger SFunction::sha384(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, text, 0);

	sha384wrapper sha384;
	sq_pushstring(vm, sha384.getHashFromString(text).c_str(), -1);

	return 1;
};

SQInteger SFunction::sha512(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, text, 0);

	sha512wrapper sha512;
	sq_pushstring(vm, sha512.getHashFromString(text).c_str(), -1);

	return 1;
};

SQInteger SFunction::equipArmor(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);

	oCNpc* hero = oCNpc::GetHero();
	oCItem* currentArmor = hero->GetEquippedArmor();
	if (currentArmor != 0)
	{
		hero->UnequipItem(currentArmor);
		currentArmor = 0;
	}

	currentArmor = hero->CreateItem(zSTRING(instance), 1);
	if (currentArmor)
	{
		hero->Equip(currentArmor);
		sq_pushbool(vm, true);
	}
	else
		sq_pushbool(vm, false);

	return 1;
};

SQInteger SFunction::unequipArmor(HSQUIRRELVM vm)
{
	oCItem* item = oCNpc::GetHero()->GetEquippedArmor();
	if (item)
		oCNpc::GetHero()->UnequipItem(item);

	return 0;
};

SQInteger SFunction::equipMeleeWeapon(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);
	oCNpc* hero = oCNpc::GetHero();
	oCItem* currentWeapon = hero->GetEquippedMeleeWeapon();

	if (currentWeapon != 0)
	{
		hero->UnequipItem(currentWeapon);
		currentWeapon = 0;
	}
	currentWeapon = hero->CreateItem(zSTRING(instance), 1);
	if (currentWeapon)
	{
		hero->Equip(currentWeapon);
		sq_pushbool(vm, true);
	}
	else
		sq_pushbool(vm, false);

	return 1;
};

SQInteger SFunction::unequipMeleeWeapon(HSQUIRRELVM vm)
{
	oCItem* item = oCNpc::GetHero()->GetEquippedMeleeWeapon();
	if (item)
		oCNpc::GetHero()->UnequipItem(item);

	return 0;
};

SQInteger SFunction::equipRangedWeapon(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);
	oCNpc* hero = oCNpc::GetHero();
	oCItem* currentWeapon = hero->GetEquippedRangedWeapon();

	if (currentWeapon != 0)
	{
		hero->UnequipItem(currentWeapon);
		currentWeapon = 0;
	}

	currentWeapon = hero->CreateItem(zSTRING(instance), 1);
	if (currentWeapon)
	{
		hero->Equip(currentWeapon);
		sq_pushbool(vm, true);
	}
	else
		sq_pushbool(vm, false);

	return 1;
};

SQInteger SFunction::unequipRangedWeapon(HSQUIRRELVM vm)
{
	oCItem* item = oCNpc::GetHero()->GetEquippedRangedWeapon();
	if (item)
		oCNpc::GetHero()->UnequipItem(item);

	return 0;
};

SQInteger SFunction::getArmorInstance(HSQUIRRELVM vm)
{
	oCItem* item = oCNpc::GetHero()->GetEquippedArmor();
	if (item)
		sq_pushstring(vm, item->GetInstanceName().ToChar(), -1);
	else
		sq_pushstring(vm, "NULL", -1);

	return 1;
};

SQInteger SFunction::getMeleeInstance(HSQUIRRELVM vm)
{
	oCItem* item = oCNpc::GetHero()->GetEquippedMeleeWeapon();

	if (item)
		sq_pushstring(vm, item->GetInstanceName().ToChar(), -1);
	else
		sq_pushstring(vm, "NULL", -1);

	return 1;
};

SQInteger SFunction::getRangedInstance(HSQUIRRELVM vm)
{
	oCItem* item = oCNpc::GetHero()->GetEquippedRangedWeapon();

	if (item)
		sq_pushstring(vm, item->GetInstanceName().ToChar(), -1);
	else
		sq_pushstring(vm, "NULL", -1);

	return 1;
};

SQInteger SFunction::clearChat(HSQUIRRELVM vm)
{
	core.GetChat()->Clear();
	return 0;
}

SQInteger SFunction::giveItem(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);
	SQ_CHECK_PARAM_INT(vm, amount, 1);

	oCNpc::GetHero()->CreateItem(zSTRING(instance), amount);

	return 0;
};

SQInteger SFunction::removeItem(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);
	SQ_CHECK_PARAM_INT(vm, amount, 1);

	oCNpc* hero = oCNpc::GetHero();
	int index = zCParser::GetParser()->GetIndex(zSTRING(instance));
	if (index != 0)
	{
		oCItem* item = hero->IsInInv(index, 1);
		if (item->GetAmount() > amount)
			item->SetAmount(item->GetAmount() - amount);
		else if (item->GetAmount() <= amount)
		{
			hero->DoDropVob(item);
			item->RemoveVobFromWorld();
		}
	}

	return 0;
};

SQInteger SFunction::getWeaponMode(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, (int)oCNpc::GetHero()->GetWeaponMode());
	return 1;
};

SQInteger SFunction::setWeaponMode(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, weaponMode, 0);

	oCNpc::GetHero()->SetWeaponMode2((oCNpc_WeaponMode)weaponMode);

	return 0;
};

SQInteger SFunction::playAnimation(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, animation, 0);

	oCNpc::GetHero()->GetModel()->StartAni(zSTRING(animation), 0);

	return 0;
};

SQInteger SFunction::setTimer(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 3);
	SQ_CHECK_PARAM_FUNC(vm, function, 0);
	SQ_CHECK_PARAM_INT(vm, time, 1);
	SQ_CHECK_PARAM_BOOL(vm, repeat, 2);
	SQ_PARAM_ANY(vm, data, 3);

	// Checking last arg, because he initialize itself
	if (stack_size <= 4)
		data._type = OT_NULL;

	sq_pushinteger(vm, timer.Add(function, time, repeat, data));

	return 1;
};

SQInteger SFunction::killTimer(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, timerId, 0);

	timer.Remove(timerId);

	return 0;
};

SQInteger SFunction::setTimerInterval(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, timerId, 0);
	SQ_CHECK_PARAM_INT(vm, interval, 1);

	timer.SetInterval(timerId, interval);

	return 0;
};

SQInteger SFunction::setTimerRepeat(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, timerId, 0);
	SQ_CHECK_PARAM_INT(vm, repeat, 1);

	timer.SetRepeat(timerId, repeat);

	return 0;
};

SQInteger SFunction::setTimerData(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, timerId, 0);
	SQ_CHECK_PARAM_TABLE(vm, data, 1);

	timer.SetData(timerId, data);

	return 0;
};

SQInteger SFunction::setCameraBeforeHero(HSQUIRRELVM vm)
{
	zVEC3 position = oCNpc::GetHero()->GetPosition();
	float angle = oCNpc::GetHero()->GetHeading();

	// 50 to dystans od kamerki
	position.x += sin(angle * 3.14 / 180.0) * 50;
	position.z += cos(angle * 3.14 / 180.0) * 50;

	angle += 180.0f;
	if (angle > 360.0f) angle -= 360.0f;

	zCVob *vob = oCObjectFactory::GetFactory()->CreateVob(zSTRING("INVISIBLE_DEFAULT.3DS"), false, position, zVEC3(0.0f, angle, 0.0f));
	if (vob) zCAICamera::GetCurrent()->SetTarget(vob);

	return 0;
};

SQInteger SFunction::setDefaultCamera(HSQUIRRELVM vm)
{
	// Chyba jeszcze trzeba tutaj zwolniæ pamiêæ tego voba od kamerki
	zCAICamera::GetCurrent()->SetTarget(oCNpc::GetHero());
	return 0;
};

SQInteger SFunction::setWorld(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, world, 0);

	oCGame::GetGame()->ChangeLevel(zSTRING(world), zSTRING("start"));

	return 0;
};

SQInteger SFunction::getWorld(HSQUIRRELVM vm)
{
	zSTRING world = oCGame::GetGame()->GetGameWorld()->GetWorldName();
	sq_pushstring(vm, world.ToChar(), -1);

	return 1;
};

SQInteger SFunction::setSavingEnabled(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	scr.GetScriptVars()->isSavingActive = enable;

	return 0;
};

SQInteger SFunction::isSavingEnabled(HSQUIRRELVM vm)
{
	sq_pushbool(vm, scr.GetScriptVars()->isSavingActive);
	return 1;
};

SQInteger SFunction::getItemName(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);
	oCNpc* hero = oCNpc::GetHero();
	oCItem* item = hero->CreateItem(zSTRING(instance), 1);

	if (item)
	{
		sq_pushstring(vm, item->GetName(0).ToChar(), -1);
		hero->DoDropVob(item);
		item->RemoveVobFromWorld();
	}
	else
		sq_pushstring(vm, "NULL", -1);

	return 1;
};

SQInteger SFunction::getItemDescription(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);
	SQ_CHECK_PARAM_INT(vm, index, 1);

	if (index >= 0 && index <= 5)
	{
		oCNpc* hero = oCNpc::GetHero();
		oCItem* item = hero->CreateItem(zSTRING(instance), 1);

		if (item && !item->GetText(index).IsEmpty())
		{
			sq_pushstring(vm, item->GetText(index).ToChar(), -1);
			hero->DoDropVob(item);
			item->RemoveVobFromWorld();
		}
		else
			sq_pushstring(vm, "NULL", -1);
	}
	else
		sq_pushstring(vm, "NULL", -1);

	return 1;
};

SQInteger SFunction::getItemValue(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);
	SQ_CHECK_PARAM_INT(vm, index, 1);

	if (index >= 0 && index <= 5)
	{
		oCNpc* hero = oCNpc::GetHero();
		oCItem* item = hero->CreateItem(zSTRING(instance), 1);

		if (item)
		{
			sq_pushinteger(vm, item->GetCount(index));
			hero->DoDropVob(item);
			item->RemoveVobFromWorld();
		}
		else
			sq_pushinteger(vm, -1);
	}
	else
		sq_pushinteger(vm, -1);

	return 1;
};

SQInteger SFunction::getInstance(HSQUIRRELVM vm)
{
	sq_pushstring(vm, oCNpc::GetHero()->GetInstanceName().ToChar(), -1);
	return 1;
};

SQInteger SFunction::setInstance(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);

	oCNpc* hero = oCNpc::GetHero();
	zVEC3 pos = hero->GetPosition();
	oCNpc* new_hero = oCGame::GetGame()->CreateNPC(zSTRING(instance), pos.x, pos.y + 30, pos.z);
	if (new_hero)
	{
		zSTRING bodyModel, headModel;
		int bodyTexture, headTexture;

		CLocalPlayer *player = playerManager.GetLocalPlayer();
		player->GetAdditionalVisuals(bodyModel, bodyTexture, headModel, headTexture);

		new_hero->SetAsPlayer();
		hero->DestroyNpc();

		player->SetAdditionalVisuals(bodyModel, bodyTexture, headModel, headTexture);
	}

	return 0;
};

SQInteger SFunction::checkPrograms(HSQUIRRELVM vm)
{
	SAnticheat::enumWindows();
	return 0;
};

SQInteger SFunction::createVob(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 7);
	SQ_CHECK_PARAM_STRING(vm, visual, 0);
	SQ_CHECK_PARAM_FLOAT(vm, x, 1);
	SQ_CHECK_PARAM_FLOAT(vm, y, 2);
	SQ_CHECK_PARAM_FLOAT(vm, z, 3);
	SQ_CHECK_PARAM_FLOAT(vm, rotx, 4);
	SQ_CHECK_PARAM_FLOAT(vm, roty, 5);
	SQ_CHECK_PARAM_FLOAT(vm, rotz, 6);

	CVob* vob = vobManager.CreateVob(zSTRING(visual), zVEC3(x, y, z), zVEC3(rotx, roty, rotz));
	if (vob)
	{
		sq_pushinteger(vm, vob->GetID());
	}
	else
		sq_pushinteger(vm, -1);

	return 1;
};

SQInteger SFunction::destroyVob(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, vobID, 0);

	CVob* vob = vobManager.GetById(vobID);
	if (vob)
		vobManager.DestroyVob(vob);

	return 0;
};

SQInteger SFunction::getVobPosition(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, vobID, 0);

	CVob* vob = vobManager.GetById(vobID);

	if (vob)
	{
		zVEC3 pos = vob->GetZVob()->GetPositionWorld();

		sq_newtable(vm);
		SQ_TABLE_SET_FLOAT(vm, "x", pos.x);
		SQ_TABLE_SET_FLOAT(vm, "y", pos.y);
		SQ_TABLE_SET_FLOAT(vm, "z", pos.z);
	}
	else
		sq_pushnull(vm);

	return 1;
};

SQInteger SFunction::getVobRotation(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, vobID, 0);

	CVob* vob = vobManager.GetById(vobID);

	if (vob)
	{
		zVEC3 pos = vob->GetRotation();

		sq_newtable(vm);
		SQ_TABLE_SET_FLOAT(vm, "x", pos.x);
		SQ_TABLE_SET_FLOAT(vm, "y", pos.y);
		SQ_TABLE_SET_FLOAT(vm, "z", pos.z);
	}
	else
		sq_pushnull(vm);

	return 1;
};

SQInteger SFunction::setVobPosition(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 4);
	SQ_CHECK_PARAM_INT(vm, vobID, 0);
	SQ_CHECK_PARAM_FLOAT(vm, x, 1);
	SQ_CHECK_PARAM_FLOAT(vm, y, 2);
	SQ_CHECK_PARAM_FLOAT(vm, z, 3);

	CVob* vob = vobManager.GetById(vobID);
	if (vob)
		vob->GetZVob()->SetPositionWorld(zVEC3(x, y, z));

	return 0;
};

SQInteger SFunction::setVobRotation(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 4);
	SQ_CHECK_PARAM_INT(vm, vobID, 0);
	SQ_CHECK_PARAM_FLOAT(vm, x, 1);
	SQ_CHECK_PARAM_FLOAT(vm, y, 2);
	SQ_CHECK_PARAM_FLOAT(vm, z, 3);

	CVob* vob = vobManager.GetById(vobID);
	if (vob)
		vob->SetRotation(zVEC3(x, y, z));

	return 0;
};

SQInteger SFunction::setVobCollision(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, vobID, 0);
	SQ_CHECK_PARAM_BOOL(vm, enable, 1);

	if (vobID >= 0)
	{
		CVob* vob = vobManager.GetById(vobID);
		if (vob)
			vob->GetZVob()->SetCollDet(enable);
	}

	return 0;
};

SQInteger SFunction::setCameraBehindVob(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, vobID, 0);

	if (vobID >= 0)
	{
		CVob* vob = vobManager.GetById(vobID);
		if (vob)
			zCAICamera::GetCurrent()->SetTarget(vob->GetZVob());
	}

	return 0;
};

SQInteger SFunction::setWeaponSkill(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, skillID, 0);
	SQ_CHECK_PARAM_INT(vm, value, 1);

	oCNpc::GetHero()->SetSkillWeapon(skillID, value);

	return 0;
};

SQInteger SFunction::getWeaponSkill(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, skillID, 0);

	sq_pushinteger(vm, oCNpc::GetHero()->GetSkillWeapon(skillID));

	return 1;
}

SQInteger SFunction::getAnimationID(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, oCNpc::GetHero()->GetAnimationID());
	return 1;
}

SQInteger SFunction::getAnimationName(HSQUIRRELVM vm)
{
	sq_pushstring(vm, oCNpc::GetHero()->GetAnimationName().ToChar(), -1);
	return 1;
}

SQInteger SFunction::getAdditionalVisual(HSQUIRRELVM vm)
{
	zSTRING bodyModel, headModel;
	int bodyTexture, headTexture;

	playerManager.GetLocalPlayer()->GetAdditionalVisuals(bodyModel, bodyTexture, headModel, headTexture);

	sq_newtable(vm);
	SQ_TABLE_SET_STRING(vm, "bodyModel", bodyModel.ToChar());
	SQ_TABLE_SET_INT(vm, "bodyTexture", bodyTexture);
	SQ_TABLE_SET_STRING(vm, "headModel", headModel.ToChar());
	SQ_TABLE_SET_INT(vm, "headTexture", headTexture);

	return 1;
}

SQInteger SFunction::setAdditionalVisual(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 4);
	SQ_CHECK_PARAM_STRING(vm, bodyModel, 0);
	SQ_CHECK_PARAM_INT(vm, bodyTexture, 1);
	SQ_CHECK_PARAM_STRING(vm, headModel, 2);
	SQ_CHECK_PARAM_INT(vm, headTexture, 3);

	playerManager.GetLocalPlayer()->SetAdditionalVisuals(zSTRING(bodyModel), bodyTexture, zSTRING(headModel), headTexture);

	return 0;
}

SQInteger SFunction::hasItem(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, instance, 0);

	oCNpc* hero = oCNpc::GetHero();
	int index = zCParser::GetParser()->GetIndex(zSTRING(instance));
	if (index != 0)
	{
		oCItem* item = hero->IsInInv(index, 1);
		if (item)
		{
			sq_pushinteger(vm, item->GetAmount());
			return 1;
		}
	}
	sq_pushinteger(vm, -1);

	return 1;
}

SQInteger SFunction::getEq(HSQUIRRELVM vm)
{
	oCNpc* hero = oCNpc::GetHero();
	sq_newarray(vm, 0);

	for (int i = 0; i < 5000; ++i)
	{
		oCItem* item = hero->IsInInv(i, 0);
		if (item)
		{
			sq_newtable(vm);
			SQ_TABLE_SET_STRING(vm, "instance", item->GetInstanceName().ToChar());
			SQ_TABLE_SET_INT(vm, "amount", item->GetAmount());
			sq_arrayappend(vm, -2);
		}
	}

	return 1;
}

SQInteger SFunction::sendVisual(HSQUIRRELVM vm)
{
	zSTRING bodyModel, headModel;
	int bodyTexture, headTexture;

	playerManager.GetLocalPlayer()->GetAdditionalVisuals(bodyModel, bodyTexture, headModel, headTexture);

	CNetwork* net = core.GetNetwork();
	if (net->IsConnected() == true)
	{
		BitStream s;
		s.Write((MessageID)GO_SCRIPT);
		s.Write((MessageID)SCRIPT_VISUAL);
		s.Write(RakString(bodyModel.ToChar()));
		s.Write(bodyTexture);
		s.Write(RakString(headModel.ToChar()));
		s.Write(headTexture);
		net->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0, net->GetServerAddress(), false);
	}

	return 0;
}

SQInteger SFunction::applyOverlay(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, overlay, 0);

	oCNpc::GetHero()->ApplyOverlay(zSTRING(overlay));

	return 0;
}

SQInteger SFunction::removeOverlay(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, overlay, 0);

	oCNpc::GetHero()->RemoveOverlay(zSTRING(overlay));

	return 0;
}

SQInteger SFunction::destroyAllVobInWorld(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, type, 0);

	switch (type)
	{
	case 0: type = VOB_TYPE_VT_OCMOBBED; break;
	case 1: type = VOB_TYPE_VT_OCMOBCONTAINER; break;
	case 2: type = VOB_TYPE_VT_OCMOBDOOR; break;
	case 3: type = VOB_TYPE_VT_OCMOBINTER; break;
	case 4: type = VOB_TYPE_VT_OCMOBLADDER; break;
	case 5: type = VOB_TYPE_VT_OCMOBSWITCH; break;
	case 6: type = VOB_TYPE_VT_OCMOBWHEEL; break;
	default: type = -1; break;
	}

	zCTree<zCVob> *tree = oCGame::GetGame()->GetGameWorld()->GetGlobalVobTree().firstChild;

	while (tree)
	{
		if (tree->data)
		{
			oCMobInter *mob = (oCMobInter*)tree->data;
			if ((int)::GetVobType(mob) == type)
				mob->RemoveVobFromWorld();
		}

		tree = tree->next;
	}

	return 0;
}

SQInteger SFunction::destroyVobsInWorld(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 4);
	SQ_CHECK_PARAM_FLOAT(vm, x, 0);
	SQ_CHECK_PARAM_FLOAT(vm, y, 1);
	SQ_CHECK_PARAM_FLOAT(vm, z, 2);
	SQ_CHECK_PARAM_INT(vm, range, 3);

	zCTree<zCVob> *tree = oCGame::GetGame()->GetGameWorld()->GetGlobalVobTree().firstChild;

	while (tree)
	{
		if (tree->data)
		{
			zVEC3 pos = tree->data->GetVobPosition();
			if (goMath::GetDistance3D(pos.x, pos.y, pos.z, x, y, z) <= range)
			{
				tree->data->RemoveVobFromWorld();
			}
		}

		tree = tree->next;
	}

	return 0;
}

SQInteger SFunction::enableCameraMovement(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	zCAICamera::GetCurrent()->SetMovementEnabled(enable);

	return 0;
};

SQInteger SFunction::enableResetModel(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	scr.GetScriptVars()->isResetModelEnabled = enable;

	return 0;
}

SQInteger SFunction::resetModel(HSQUIRRELVM vm)
{
	zCModel* model = oCNpc::GetHero()->GetModel();
	if (model)
		model->FadeOutAnisLayerRange(1, 2000);

	return 0;
}

SQInteger SFunction::enableMarvin(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	SScript *script = scr.GetScriptVars();
	if (script->isMarvinEnabled && !enable)
		pMemLib->ImportHook(0x4301F0, sizeof(void(*)(zSTRING)), &Fake_HandleResultString);
	else if (enable && !script->isMarvinEnabled)
		pMemLib->RemoveHook(0x4301F0);

	oCGame::GetGame()->EnableTestmode(enable);
	script->isMarvinEnabled = enable;

	return 0;
}

SQInteger SFunction::showPlayerStatus(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	oCGame::GetGame()->SetShowPlayerStatus(enable);

	return 0;
}

SQInteger SFunction::callServerFunc(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, function, 0);

	RakString format = "0";

	for (SQInteger i = 3; i <= stack_size; i++)
	{
		switch (sq_gettype(vm, i))
		{
		case OT_INTEGER:
			format += "d";
			break;
		case OT_FLOAT:
			format += "f";
			break;
		case OT_STRING:
			format += "s";
			break;
		default:
			sq_pushbool(vm, false);
			return 1;
		}
	}

	BitStream s;
	s.Write((MessageID)GO_SCRIPT);
	s.Write((MessageID)SCRIPT_CALL);
	s.Write(function);
	s.Write(format);

	int p1; float p2; const char *p3;

	for (SQInteger i = 3; i <= stack_size; i++)
	{
		switch (sq_gettype(vm, i))
		{
		case OT_INTEGER:
			sq_getinteger(vm, i, &p1);
			s.Write(p1);
			break;
		case OT_FLOAT:
			sq_getfloat(vm, i, &p2);
			s.Write(p2);
			break;
		case OT_STRING:
			sq_getstring(vm, i, &p3);
			s.Write(p3);
			break;
		}
	}

	core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0, core.GetNetwork()->GetServerAddress(), false);
	sq_pushbool(vm, true);
	return 1;
}

SQInteger SFunction::getTextWidth(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_STRING(vm, font, 0);
	SQ_CHECK_PARAM_STRING(vm, text, 1);

	zCView *view = scr.GetScriptVars()->GetView();
	view->SetFont(zSTRING(font));

	zCFont *zFont = view->GetFont();
	sq_pushinteger(vm, zFont->GetFontX(zSTRING(text)));
	return 1;
}

SQInteger SFunction::getFontHeight(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, font, 0);

	zCView *view = scr.GetScriptVars()->GetView();
	view->SetFont(zSTRING(font));

	zCFont *zFont = view->GetFont();
	sq_pushinteger(vm, zFont->GetFontY());
	return 1;
}

SQInteger SFunction::getLetterWidth(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_STRING(vm, font, 0);
	SQ_CHECK_PARAM_INT(vm, character, 1);

	zCView *view = scr.GetScriptVars()->GetView();
	view->SetFont(zSTRING(font));
	
	zCFont *zFont = view->GetFont();
	sq_pushinteger(vm, zFont->GetWidth(character));
	return 1;
}

SQInteger SFunction::getLetterDistance(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, font, 0);

	zCView *view = scr.GetScriptVars()->GetView();
	view->SetFont(zSTRING(font));

	zCFont *zFont = view->GetFont();
	sq_pushinteger(vm, zFont->GetLetterDistance());
	return 1;
}

SQInteger SFunction::getLanguage(HSQUIRRELVM vm)
{
	sq_pushstring(vm, core.GetConfig()->GetLanguage().C_String(), -1);
	return 1;
}