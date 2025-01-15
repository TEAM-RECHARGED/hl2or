//========= Copyright Half-Life 2 ReCharged Team, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//
#include "cbase.h"
#include "filesystem.h"
#include "mount.h"

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
	Msg("Platform: %s\n", GetPlatform());
	Msg("Arch: %s\n", GetArch());
	Msg("Game: Half-Life 2 ReCharged");
}

CON_COMMAND(oc_firstperson_enable, "Creates first person ragdoll, WARNING BETA!")
{
	Msg("Enabling OVR Firstperson...");
	engine->ClientCmd("cl_first_person_uses_world_model 1");
}

CON_COMMAND(oc_firstperson_disable, "Disables the first person ragdoll.")
{
	Msg("Disabling OVR Firstperson...");
	engine->ClientCmd("cl_first_person_uses_world_model 0");
}