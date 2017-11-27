#include "stdafx.h"

void CNetworkError::DisplayDetails(StartupResult result)
{
	switch(result)
	{
		case RAKNET_ALREADY_STARTED:          LOG("[error] Raknet already started.\n"); break;
		case INVALID_SOCKET_DESCRIPTORS:      LOG("[error] Invalid socket descriptors.\n"); break;
		case INVALID_MAX_CONNECTIONS:         LOG("[error] Invalid max connections.\n"); break;
		case SOCKET_FAMILY_NOT_SUPPORTED:     LOG("[error] Invalid socket family.\n"); break;
		case SOCKET_PORT_ALREADY_IN_USE:      LOG("[error] Port already in use.\n"); break;
		case SOCKET_FAILED_TO_BIND:           LOG("[error] Can not socket to bind.\n"); break;
		case PORT_CANNOT_BE_ZERO:             LOG("[error] Port can not be zero.\n"); break;
		case FAILED_TO_CREATE_NETWORK_THREAD: LOG("[error] Can not create network thread.\n"); break;
		case STARTUP_OTHER_FAILURE:           LOG("[error] Unknown failure.\n"); break;
	}
};