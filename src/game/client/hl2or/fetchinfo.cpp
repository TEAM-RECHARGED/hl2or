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


// Final include, required for debugging.
#include "tier0/memdbgon.h"

static ConVar oc_crash_now("oc_crash_now", "1", 1, "Crashes the mod, useful for noclick who fakes stuff");
static ConVar oc_firstperson("oc_firstperson", "1", 1, "Displays The First Person Model");
static ConVar oc_lua_enable("oc_lua_enable", "0", 0, "Enables a Lua-like interface for console");
static ConVar oc_realism("oc_realism", "1", 1, "Enables Realism");


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
	Msg("Engine Version: Source 2013 (AetherSrc Engine)\n");
	Msg("Platform: %s\n", GetPlatform());
	Msg("Arch: %s\n", GetArch());
	Msg("Game: Half-Life 2 ReCharged");
}


void FUNCTION_FIRSTPERSON()
{
	if (oc_firstperson.GetBool() == 1)
	{
		DevMsg("Firstperson has been enabled!");
		engine->ClientCmd("cl_first_person_uses_world_model 1");
	}
	else if (oc_firstperson.GetBool() == 0)
	{
		DevMsg("Firstperson has been disabled!");
		engine->ClientCmd("cl_first_person_uses_world_model 0");
	}
}

void FUNCTION_OC_LUA()
{
	if (oc_lua_enable.GetBool() == 1)
	{
		if (steamapicontext->SteamUser()->GetSteamID().ConvertToUint64() == 76561198356280039)
		{
			Error("Nocuck you cringe cunt, there is no lua yet!");
		}
		else
		{
			DevMsg("Lua hasn't been implemented yet");
		}
	}
	else if (oc_lua_enable.GetBool() == 0)
	{
		if (steamapicontext->SteamUser()->GetSteamID().ConvertToUint64() == 76561198356280039)
		{
			Error("Nocuck you cringe cunt, there is no lua yet!");
		}
		else
		{
			DevMsg("Lua hasn't been implemented yet");
		}
	}
}

void FUNCTION_FUN()
{
	// Just a silly fun void-based function for experiments
	#define nocuck 76561198356280039
    #define INITCMD	engine->ClientCmd
    #define elif	else if
	if (oc_crash_now.GetBool() == 1)
	{
		int i = NULL;
		if (steamapicontext->SteamUser()->GetSteamID().ConvertToUint64() == nocuck)
		{
			for (; NULL < 3; ++i) {
				Error("Typical Noclick behavior.");
			}
		}
		else
		{
			Error("Force crashing?, typical youtuber.");
		}
	}
	if (oc_crash_now.GetBool() == 0)
	{
		Msg("Good!!!!");
	}

	if (oc_realism.GetBool() == 1)
	{
		INITCMD("exec autoexec");
		INITCMD("mat_monitorgamma 2.6");
		INITCMD("mat_hdr_level 2");
		INITCMD("mat_dxlevel 95");
		INITCMD("oc_firstperson 1");
	}

	elif(oc_realism.GetBool() == 0)
	{
		Msg("Realism Not Enabled");
		// Or maybe comment this block :/
	}
}