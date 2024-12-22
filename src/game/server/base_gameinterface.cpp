//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "gameinterface.h"
#include "mapentities.h"
#ifdef OVERCHARGED
#include "mapadd.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

void CServerGameClients::GetPlayerLimits( int& minplayers, int& maxplayers, int &defaultMaxPlayers ) const
{
	minplayers = defaultMaxPlayers = 1; 
	maxplayers = MAX_PLAYERS;
}


// -------------------------------------------------------------------------------------------- //
// Mod-specific CServerGameDLL implementation.
// -------------------------------------------------------------------------------------------- //

void CServerGameDLL::LevelInit_ParseAllEntities( const char *pMapEntities )
{
#ifdef OVERCHARGED
	CMapAdd* pMapadd = GetMapAddEntity();

	if (!pMapadd)
	{
		pMapadd = CreateMapAddEntity();
		pMapadd->RunLabel("Init");
	}
	else
	{
		pMapadd->RunLabel("Init");
	}

	if (pMapadd)
	{
		pMapadd->RunLabel("Default");
	}
#endif
}
