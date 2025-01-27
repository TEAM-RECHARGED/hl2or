// GMOD_OpenURLInSteam
// GMOD_AskConnect
// CleanupExploits
// CleanupUserTempFiles
// CleanupWipeFolder
// LUA_ReloadLegacyAddons
// CallLuaHook(const std::string&)

// dumpstringtables_new
// stringtabletotals

#include "cbase.h"
#include "garrysmod.h"
#include "Lua/gmod_lua.h"
#include "GModMaterialProxyFactory.h"
#include "CLuaClass.h"
#include "sv_autorefresh.h"
#include "Externals.h"
#ifdef CLIENT_DLL
#include "networkstringtable_clientdll.h"
#else
#include "networkstringtable_gamedll.h"
#endif

ILuaShared* LuaShared()
{
	return (ILuaShared*)get->LuaShared();
}

CGarrysMod garrysmod;
IGarrysMod* igarrysmod = &garrysmod;

CGarrysMod::CGarrysMod()
{
	//SteamAPI_RegisterCallback(); Register p2p stuff
}

#ifdef CLIENT_DLL
void CGarrysMod::OnGameRichPresenceJoinRequested( GameRichPresenceJoinRequested_t* )
{
	// ToDo
}

void CGarrysMod::OnGameOverlayActivated( GameOverlayActivated_t* )
{
	// ToDo
}
#endif

void CGarrysMod::OnP2PSessionRequest( P2PSessionRequest_t* request )
{
	// ToDo
}

void CGarrysMod::OnP2PSessionConnectFail( P2PSessionConnectFail_t* request )
{
	// ToDo
}

void CleanupExploits()
{
	// Not needed.
}

void CleanupWipeFolder( const char* folder )
{
	// ToDo
}

void CGarrysMod::InitializeMod( CreateInterfaceFn fn )
{
	// Bootil::Startup()
	// Bootil::Debug::IListener::Add()
	// CLoadTimer::CLoadTimer("CGarrysMod::InitializeMod", false);

	CleanupExploits();

	// ToDo

#ifdef CLIENT_DLL
	GarrysMod::MaterialProxyFactory::Init();
#endif

	//GarrysMod::AutoRefresh::Init();

	CleanupWipeFolder( "downloads/server/" );
}

void CGarrysMod::Shutdown()
{
	CleanupWipeFolder( "downloads/server/" );

#ifdef CLIENT_DLL
	GarrysMod::MaterialProxyFactory::Shutdown();
#endif

	// ToDo
	// Funnies with map.pack
}

#ifdef CLIENT_DLL
void CGarrysMod::FullScreenVGUI( bool unknown )
{
	// ToDo
}

void CGarrysMod::VGUIDrawMode( bool unknown, IMatRenderContext* context )
{
	// ToDo
}

void CGarrysMod::PaintVGUIOverlay( IMatRenderContext* context )
{
	// ToDo
}

void CGarrysMod::RenderView( const CViewSetup& viewSetup, int x, int y )
{
	// ToDo
}
#endif

void CGarrysMod::LevelInit( const char *pMapName, char const *pMapEntities, char const *pOldLevel, char const *pLandmarkName, bool loadGame, bool background )
{
#ifndef CLIENT_DLL
	Lua::Create();
	Lua::OnLoaded();
#endif
}

#ifdef CLIENT_DLL
void CGarrysMod::LevelShutdown()
{
	// ToDo
	// ResetNetLibrary();

	// Some other stuff

	// CleanupLuaBoundMaterials();
	// CleanupLuaCreatedMaterials();
	// CleanupLuaCreatedRenderTargets();
	// CleanupShaderParams();
}
#else
const char* CGarrysMod::GetGameDescription() // Called from CGMODRules::GetGameDescription()
{
	return "the funnies"; // ToDo
}
#endif

void CGarrysMod::PostInitialize() // Called from CServerGameDLL::DLLInit
{

}

void CGarrysMod::EntityRemoved( CBaseEntity* ent ) // Called from CBaseEntity::UpdateOnRemove
{
	// ToDo
	// Make da lua call
}

#ifdef CLIENT_DLL
void CGarrysMod::OnNewUserCmd()
{
	// ToDo
}
#endif

void CGarrysMod::Think() // Called from CLuaGameSystem::FrameUpdatePreEntityThink
{
	// CheckForFilesystemChanges();
#ifdef GAME_DLL
	g_LuaNetworkedVars->Cycle();
#endif
	// GarrysMod::Lua::Libraries::Timer::Cycle();
	GarrysMod::Lua::Libraries::File::AsyncCycle();
	// GarrysMod::Lua::Libraries::HTTP::Cycle();
	//GarrysMod::AutoRefresh::Cycle();
}

void CGarrysMod::MenuThink()
{
	// ToDo
}

#ifdef CLIENT_DLL
void CGarrysMod::ClearVertexLighting( IMatRenderContext* context, float unknown )
{
	// ToDo
}

void CGarrysMod::EndClearVertexLighting( IMatRenderContext* context )
{
	// ToDo
}
#endif

// NOTE: Since we fixed the bug in the Physics engine that broke it entirely if CollisionRulesChanged was never called properly, we don't need any safety
bool CGarrysMod::ShouldCollide( CBaseEntity* ent1, CBaseEntity* ent2 ) // Called from PassServerEntityFilter(IHandleEntity const*,IHandleEntity const*) and CCollisionEvent::ShouldCollide(IPhysicsObject *,IPhysicsObject *,void *,void *)
{
	return true; // ToDo
}

void CGarrysMod::MD5String( char* out, const char*, const char*, const char* )
{
	// ToDo
}

void CGarrysMod::PlaySound( const char* sound )
{
	// ToDo
}

const char* CGarrysMod::GetMapName()
{
#ifdef CLIENT_DLL
	return engine->GetLevelName();
#else
	return gpGlobals->mapname.ToCStr();
#endif
}

void CGarrysMod::RunConsoleCommand( const char* cmd )
{
	// engine->GMOD_RawConsoleCommand( cmd );
}

void CGarrysMod::StartVideoScale( int x, int y )
{
	// Unused
}

void CGarrysMod::EndVideoScale( int x, int y )
{
	// Unused
}

void CGarrysMod::FireGameEvent( IGameEvent* event )
{
	// if name == client_disconnect
	// GarrysMod::StringTable::Reset()

	// if name == server_spawn
	// Do some print
}

void dumpstringtables_newCmd( const CCommand &args )
{
	if ( args.ArgC() > 0 )
	{
		INetworkStringTable* pTable = networkstringtable->FindTable( args.Arg( 1 ) );
		if ( !pTable )
		{
			Msg( "Table %s not found.\n", args.Arg( 1 ) );
			return;
		}

		for ( int i=0; i<pTable->GetNumStrings(); ++i )
		{
			int iLength;
			const void* pUserData = pTable->GetStringUserData( i, &iLength );
			if (iLength > 0)
				Msg( "%i: '%s'(data %i bytes)\n", i, pTable->GetString( i ), iLength );
			else
				Msg( "%i: '%s'\n", i, pTable->GetString( i ) );
		}

		Msg( "Max Strings: %i\n", pTable->GetMaxStrings() );
		Msg( "Num Strings: %i\n", pTable->GetNumStrings() );
		Msg( "Total String Bytes: %i\n", 0 );  // ToDo: Finish this later.
		Msg( "Total Data Bytes: %i\n", 0 );
		return;
	}

	for ( int i=0; i<networkstringtable->GetNumTables(); ++i )
	{
		INetworkStringTable* pTable = networkstringtable->GetTable( i );
		Msg( "%i: %s\n	strings: %i\n	strdata: %i\n	databts: %i\n", i, pTable->GetTableName(), pTable->GetNumStrings(), 0, pTable->GetEntryBits() ); // ToDo: get strdata properly
	}
}

#ifdef CLIENT_DLL
ConCommand dumpstringtables_new( "cl_dumpstringtables_new", dumpstringtables_newCmd, "", 0 );
#else
ConCommand dumpstringtables_new( "dumpstringtables_new", dumpstringtables_newCmd, "", 0 );
#endif
