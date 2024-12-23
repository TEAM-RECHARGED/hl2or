//========= Copyright Half-Life 2 Overcharged: Redux, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//
#include "cbase.h"
#include "convar.h"
#ifdef CLIENT_DLL
ConVar bullettime("bulltime", 0, 1, "Enable BulletTime");
void bulletemit(void)
{
	engine->ClientCmd("host_timescale 0.6");
	Msg("Note that this is in beta and can cause irreversable issues. to restore normal time run host_timescale 1 or run this command again, thanks in advance");
}
#endif // CLIENT_DLL