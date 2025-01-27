//========= Copyright Half-Life 2 ReCharged Team, All rights reserved. ============//
//
// Purpose: 
//
// Commands and more(tm)
//
//===========================================================================//
#include "cbase.h"
#include "filesystem.h"
#ifdef CLIENT_DLL
#include "clientsteamcontext.h"
#endif // CLIENT_DLL

//#define OVR_COMMAND( name, description ) \
   static void name( const CCommand &args ); \
   static ConCommand name##_command( #name, name, description ); \
   static void name( const CCommand &args )

// Final include, required for debugging.
#include "tier0/memdbgon.h"

static ConVar oc_crash_now("oc_crash_now", "1", 1, "Crashes the mod, useful for noclick who fakes stuff");
static ConVar oc_firstperson("oc_firstperson", "1", 1, "Displays The First Person Model");
static ConVar oc_lua_enable("oc_lua_enable", "0", 0, "Enables a Lua-like interface for console");
static ConVar oc_realism("oc_realism", "1", 1, "Enables Realism");
static ConVar oc_friendlyfire("oc_friendlyfire", "1", 1, "Friendly Fire");

const char* GetArch()
{
#if defined( __x86_64__) || defined( _M_X64 )
	return "amd64";
#elif defined(__i386__) || defined(_X86_) || defined(_M_IX86)
	return "i386";
#elif defined __aarch64__
	return "aarch64";
#elif defined __arm__ || defined _M_ARM
	return "arm";
#else
	return "Unknown (THE FUCK?)";
#endif
}

const char* GetPlatform()
{
#ifdef LINUX	
	return "Linux";
#elif WIN32
	return "Windows";
#elif OSX
	return "OSX";
#else
	return "Unknown Platform (THE FUCK?)"
#endif
}

const char* GetGame()
{
	const char* var = nullptr;  // Initialize var to nullptr in case no match is found.
	KeyValues* kv = new KeyValues("KeyValues");
	kv->LoadFromFile(g_pFullFileSystem, "gameinfo.txt");

	if (kv)
	{
		for (KeyValues* control = kv->GetFirstSubKey(); control != NULL; control = control->GetNextKey())
		{
			if (!Q_strcasecmp(control->GetName(), "game"))
			{
				var = control->GetString();
			}
		}
	}

	if (Q_stricmp(var, "HALF-LIFE 2: ReCharged") != 0)
	{
		Error("Buddy, stop stealing mods. You have been reported!");
	}
	return var;
}

ConVarRef cl_name("cl_name");

CON_COMMAND_F(neofetch, "Print info about engine", FCVAR_NONE)
{
	Color orange(128, 0, 128, 255);

	ConColorMsg(orange, "        @@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	ConColorMsg(orange, "  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	ConColorMsg(orange, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	ConColorMsg(orange, "@@@@@@@        @@@@@@@@@@@@@@@@@@@@@@@@\n");
	ConColorMsg(orange, " @@                @@@@@@@@@@@@@@@@@@@@\n");
	ConColorMsg(orange, "                      @@@@@@@@@@@@@@@@@\n");
	Msg("   @@@@@@@@@@@@@");
	ConColorMsg(orange, "        @@@@@@@@@@@@@@ \n");
	Msg("  @@@@@@@@@@@@@@@@");
	ConColorMsg(orange, "       @@@@@@@@@@@@@ \n");
	Msg(" @@@@@@@   @@@@@@@@");
	ConColorMsg(orange, "       @@@@@@@@@@@  \n");
	Msg(" @@@@@@@     @@@@@@");
	ConColorMsg(orange, "        @@@@@@@@@   \n");
	Msg(" @@@@@@@@@@@@@@@");
	ConColorMsg(orange, "           @@@@@@@@    \n");
	Msg("  @@@@@@@@@@@@@@@@");
	ConColorMsg(orange, "          @@@@@@     \n");
	Msg("     @@@@@@@@@@@@@@");
	ConColorMsg(orange, "         @@@@@@     \n");
	Msg("@@@@@@      @@@@@@@@");
	ConColorMsg(orange, "       @@@@@@      \n");
	Msg(" @@@@@@      @@@@@@");
	ConColorMsg(orange, "        @@@@@       \n");
	Msg(" @@@@@@@@@@@@@@@@@@");
	ConColorMsg(orange, "       @@@@@        \n");
	Msg("   @@@@@@@@@@@@@@");
	ConColorMsg(orange, "        @@@@@@        \n");
	Msg("       @@@@@@");
	ConColorMsg(orange, "           @@@@@@         \n");
	ConColorMsg(orange, "                      @@@@@@           \n");
	ConColorMsg(orange, "                     @@@@@@            \n");
	ConColorMsg(orange, "                       @@@             \n\n");
	Msg("Engine Version: Source 2013\n");
	Msg("OS/Platform: %s\n", GetPlatform());
	Msg("Architecture: %s\n", GetArch());
	Msg("Game: Half-Life 2: ReCharged");
}

void FUNCTION_EVERYTHING()
{
	#define nocuck 76561198356280039
    #define INITCMD	engine->ClientCmd
    #define elif	else if
	if (oc_crash_now.GetFloat() == 1)
	{
		int i = 0;
		if (steamapicontext->SteamUser()->GetSteamID().ConvertToUint64() == nocuck)
		{
			for (; i < 5; ++i) {
				Error("UNEXPECTED CRASH. DEFINETLY NOT FORCED BY THE FUCKING CONVAR");
			}
		}
		else
		{
			Warning("Force crashing?, typical youtuber.");
		}
	}

	if (oc_realism.GetFloat() == 1)
	{
		INITCMD("exec autoexec");
		INITCMD("mat_monitorgamma 2.6");
		INITCMD("mat_hdr_level 2");
		INITCMD("mat_dxlevel 95");
		INITCMD("oc_firstperson 1");
		INITCMD("oc_friendlyfire 1");
	}

	if (oc_friendlyfire.GetFloat() == 1)
	{
		INITCMD("ent_create ai_relationship subject !player target * disposition 1 rank 99 reciprocal 0 startactive 1");
	}

	if (oc_firstperson.GetFloat() == 1)
	{
		DevMsg("Firstperson has been enabled!");
		engine->ClientCmd("cl_first_person_uses_world_model 1");
	}
	else // if (oc_firstperson.GetFloat() == 0)
	{
		DevMsg("Firstperson has been disabled!");
		engine->ClientCmd("cl_first_person_uses_world_model 0");
	}
}