//========= Copyright Half-Life 2 Overcharged: Redux, All rights reserved. ============//
//
// Purpose: Implements bullet time functionality for the client.
// This functionality is in beta and might cause irreversible issues if not handled properly.
// Use host_timescale 1 to restore normal time after enabling bullet time.
//=============================================================================//
#include "cbase.h"
#include "convar.h"

#ifdef CLIENT_DLL
#endif // CLIENT_DLL