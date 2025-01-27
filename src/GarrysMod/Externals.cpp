// Doesn't exist in Gmod.
#include "cbase.h"
#include "Externals.h"

IGet* get;
ILuaInterface* g_Lua;
CLuaGamemode* gGM;

#if defined(GAME_DLL) || defined(CLIENT_DLL)
CLuaNetworkedVars* g_LuaNetworkedVars;
#endif

#if !defined(GAME_DLL) && !defined(CLIENT_DLL) && !defined(MENUSYSTEM)
IGarrysMod* igarrysmod;
#endif

#ifdef MENUSYSTEM
CGlobalVarsBase* gpGlobals;
#endif