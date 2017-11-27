#include "../stdafx.h"


void SFunction::bindGOFunctions(HSQUIRRELVM vm)
{
	SQ_REGISTER_GLOBAL_FUNC(vm, "getTickCount", SFunction::getTickCount);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getPlayerName", SFunction::getPlayerName);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getPlayerPing", SFunction::getPlayerPing);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setPlayerVirtualWorld", SFunction::setPlayerVirtualWorld);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getPlayerVirtualWorld", SFunction::getPlayerVirtualWorld);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isConnected", SFunction::isConnected);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sendMessageToAll", SFunction::sendMessageToAll);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sendMessage", SFunction::sendMessage);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sendPacket", SFunction::sendPacket);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getPosition", SFunction::getPosition);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getDistance3D", SFunction::getDistance3D);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getDistance2D", SFunction::getDistance2D);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isAdmin", SFunction::isAdmin);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getMaxSlots", SFunction::getMaxSlots);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getPlayersCount", SFunction::getPlayersCount);
	SQ_REGISTER_GLOBAL_FUNC(vm, "sscanf", SFunction::sscanf);
	SQ_REGISTER_GLOBAL_FUNC(vm, "rgbToHex", SFunction::rgbToHex);
	SQ_REGISTER_GLOBAL_FUNC(vm, "hexToRGB", SFunction::hexToRGB);
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
	SQ_REGISTER_GLOBAL_FUNC(vm, "getServerDescription", SFunction::getServerDescription);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setServerDescription", SFunction::setServerDescription);
	SQ_REGISTER_GLOBAL_FUNC(vm, "getServerWorld", SFunction::getServerWorld);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setServerWorld", SFunction::setServerWorld);
	SQ_REGISTER_GLOBAL_FUNC(vm, "ban", SFunction::ban);
	SQ_REGISTER_GLOBAL_FUNC(vm, "kick", SFunction::kick);
	SQ_REGISTER_GLOBAL_FUNC(vm, "enableUnconscious", SFunction::enableUnconscious);
	SQ_REGISTER_GLOBAL_FUNC(vm, "createItem", SFunction::createItem);
	SQ_REGISTER_GLOBAL_FUNC(vm, "destroyItem", SFunction::destroyItem);
	SQ_REGISTER_GLOBAL_FUNC(vm, "callClientFunc", SFunction::callClientFunc);
	SQ_REGISTER_GLOBAL_FUNC(vm, "setPlayerInvisible", SFunction::setPlayerInvisible);
	SQ_REGISTER_GLOBAL_FUNC(vm, "isPlayerInvisible", SFunction::isPlayerInvisible);
};

SQInteger SFunction::getTickCount(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, (int)::GetTickCount());
	return 1;
};

SQInteger SFunction::getPlayerName(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
		sq_pushstring(vm, player->name.C_String(), -1);
	else
		sq_pushstring(vm, "NULL", -1);

	return 1;
};

SQInteger SFunction::getPlayerPing(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
		sq_pushinteger(vm, core.GetNetwork()->GetPeer()->GetLastPing(player->GetAddress()));
	else
		sq_pushinteger(vm, -1);

	return 1;
};

SQInteger SFunction::setPlayerVirtualWorld(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);
	SQ_CHECK_PARAM_INT(vm, virtualWorld, 1);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
	{
		player->SetVirtualWorld(virtualWorld);

		BitStream s;
		s.Write((MessageID)GO_PLAYER);
		s.Write((MessageID)DESTROY_PLAYER);
		s.Write(player->GetID());
		core.GetNetwork()->SendToPlayersOnList(s, MEDIUM_PRIORITY, RELIABLE, &player->streamedPlayers);

		for (int i = 0; i < player->streamedPlayers.Num(); ++i)
		{
			CPlayer *streamed = player->streamedPlayers[i];

			BitStream s;
			s.Write((MessageID)GO_PLAYER);
			s.Write((MessageID)DESTROY_PLAYER);
			s.Write(streamed->GetID());

			streamed->streamedPlayers.Remove(player);
			core.GetNetwork()->GetPeer()->Send(&s, MEDIUM_PRIORITY, RELIABLE, 0, player->GetAddress(), false);
		}
		
		player->streamedPlayers.Clear();

		// Stream players again, without waiting
		core.GetStreamer()->StreamPlayers(false);
	}

	return 0;
};

SQInteger SFunction::getPlayerVirtualWorld(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
		sq_pushinteger(vm, player->GetVirutalWorld());
	else
		sq_pushinteger(vm, -1);

	return 1;
};

SQInteger SFunction::isConnected(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
		sq_pushbool(vm, true);
	else
		sq_pushbool(vm, false);

	return 1;
};

SQInteger SFunction::sendMessageToAll(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 4);
	SQ_CHECK_PARAM_INT(vm, r, 0);
	SQ_CHECK_PARAM_INT(vm, g, 1);
	SQ_CHECK_PARAM_INT(vm, b, 2);
	SQ_CHECK_PARAM_STRING(vm, message, 3);

	BitStream s;
	s.Write((MessageID)GO_CHAT);
	s.Write((MessageID)MESSAGE_RGB);
	s.Write(RakString(message));
	s.Write(r);
	s.Write(g);
	s.Write(b);

	core.GetNetwork()->SendToAll(s, LOW_PRIORITY, RELIABLE);

	return 0;
};

SQInteger SFunction::sendMessage(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 5);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);
	SQ_CHECK_PARAM_INT(vm, r, 1);
	SQ_CHECK_PARAM_INT(vm, g, 2);
	SQ_CHECK_PARAM_INT(vm, b, 3);
	SQ_CHECK_PARAM_STRING(vm, message, 4);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
	{
		BitStream s;
		s.Write((MessageID)GO_CHAT);
		s.Write((MessageID)MESSAGE_RGB);
		s.Write(RakString(message));
		s.Write(r);
		s.Write(g);
		s.Write(b);
		core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0, player->GetAddress(), false);
	}

	return 0;
};

SQInteger SFunction::sendPacket(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 3);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);
	SQ_CHECK_PARAM_INT(vm, priority, 1);
	SQ_CHECK_PARAM_STRING(vm, data, 2);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
	{
		BitStream s;
		s.Write((MessageID)GO_SCRIPT);
		s.Write((MessageID)SCRIPT_PACKET);
		s.Write(RakString(data));

		switch (priority)
		{
		case 0:
			core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, UNRELIABLE, 0, player->GetAddress(), false);
			break;

		case 1:
			core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE, 0, player->GetAddress(), false);
			break;

		case 2:
			core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE_ORDERED, 0, player->GetAddress(), false);
			break;
		}
	}

	return 0;
};

SQInteger SFunction::getPosition(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);
	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
	{
		sq_newtable(vm);
		SQ_TABLE_SET_FLOAT(vm, "x", player->x);
		SQ_TABLE_SET_FLOAT(vm, "y", player->y);
		SQ_TABLE_SET_FLOAT(vm, "z", player->z);
	}
	else
		sq_pushbool(vm, false);

	return 1;
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

SQInteger SFunction::isAdmin(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
		sq_pushbool(vm, player->isAdmin);
	else
		sq_pushbool(vm, false);

	return 1;
};

SQInteger SFunction::getMaxSlots(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, atoi(core.GetConfig()->GetMaxSlots().C_String()));
	return 1;
};

SQInteger SFunction::getPlayersCount(HSQUIRRELVM vm)
{
	sq_pushinteger(vm, playerManager.GetNumberOfPlayers());
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
	sq_pushstring(vm, colorHex.c_str(), colorHex.length());

	return 1;
};

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

SQInteger SFunction::setTimer(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 3);
	SQ_CHECK_PARAM_FUNC(vm, function, 0);
	SQ_CHECK_PARAM_INT(vm, time, 1);
	SQ_CHECK_PARAM_BOOL(vm, repeat, 2);
	SQ_PARAM_ANY(vm, data, 3);
	
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

SQInteger SFunction::getServerDescription(HSQUIRRELVM vm)
{
	sq_pushstring(vm, core.GetDescription().C_String(), -1);
	return 1;
};

SQInteger SFunction::setServerDescription(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, desc, 0);

	core.SetDescription(desc);

	return 0;
};

SQInteger SFunction::getServerWorld(HSQUIRRELVM vm)
{
	sq_pushstring(vm, core.GetWorld().C_String(), -1);
	return 1;
};

SQInteger SFunction::setServerWorld(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_STRING(vm, world, 0);

	//RakString newWorld = utility::replaceString(world, "/", "\\").c_str();
	core.SetWorld(world);

	return 0;
};

SQInteger SFunction::ban(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
	{
		core.GetBanSystem()->BanPlayer(player, BAN_LIST);
	}

	return 0;
};

SQInteger SFunction::kick(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
		player->Disconnect();

	return 0;
};

SQInteger SFunction::enableUnconscious(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_BOOL(vm, enable, 0);

	core.SetUnconscious(enable);

	return 0;
};

SQInteger SFunction::createItem(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 6);
	SQ_CHECK_PARAM_STRING(vm, itemInstance, 0);
	SQ_CHECK_PARAM_INT(vm, amount, 1);
	SQ_CHECK_PARAM_FLOAT(vm, x, 2);
	SQ_CHECK_PARAM_FLOAT(vm, y, 3);
	SQ_CHECK_PARAM_FLOAT(vm, z, 4);
	SQ_CHECK_PARAM_STRING(vm, world, 5);

	CItem* item = itemManager.CreateItem(itemInstance, amount, x, y, z, world);
	if (item)
		sq_pushinteger(vm, item->GetID());
	else
		sq_pushinteger(vm, -1);

	return 1;
};

SQInteger SFunction::destroyItem(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, itemID, 0);

	itemManager.DestroyItem(itemID);

	return 0;
};

SQInteger SFunction::callClientFunc(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);
	SQ_CHECK_PARAM_STRING(vm, function, 1);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
	{
		RakString format = "0"; // Coœ trzeba przes³aæ

		for (SQInteger i = 4; i <= stack_size; i++)
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

		for (SQInteger i = 4; i <= stack_size; i++)
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

		core.GetNetwork()->GetPeer()->Send(&s, LOW_PRIORITY, RELIABLE_ORDERED, 0, player->GetAddress(), false);
		sq_pushbool(vm, true);
		return 1;
	}

	sq_pushbool(vm, false);
	return 1;
}

SQInteger SFunction::setPlayerInvisible(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 2);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);
	SQ_CHECK_PARAM_BOOL(vm, invisible, 1);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
	{
		player->isInvisible = invisible;
		// Stream players again, without waiting

		if (player->isInvisible)
		{
			BitStream s;
			s.Write((MessageID)GO_PLAYER);
			s.Write((MessageID)DESTROY_PLAYER);
			s.Write(player->GetID());
			core.GetNetwork()->SendToPlayersOnList(s, MEDIUM_PRIORITY, RELIABLE, &player->streamedPlayers);

			for (int i = 0; i < player->streamedPlayers.Num(); ++i)
				player->streamedPlayers[i]->streamedPlayers.Remove(player);
		}
	}

	return 0;
}

SQInteger SFunction::isPlayerInvisible(HSQUIRRELVM vm)
{
	SQ_CHECK_PARAM_COUNT(vm, 1);
	SQ_CHECK_PARAM_INT(vm, playerID, 0);

	CPlayer* player = playerManager.GetPlayer(playerID);
	if (player)
		sq_pushbool(vm, player->isInvisible);
	else
		sq_pushbool(vm, false);

	return 1;
}