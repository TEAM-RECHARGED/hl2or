#include "cbase.h"
#include "convar.h"

#ifdef CLIENT_DLL

ConVar bullettime("bullettime", "0", FCVAR_CLIENTDLL, "Enable BulletTime (slow motion).");
void ToggleBulletTime()
{
    if (bullettime.GetBool())
    {
        engine->ClientCmd("host_timescale 0.6");
        Msg("BulletTime enabled. Note: This is in beta and may cause issues. To restore normal time, run 'host_timescale 1' or disable BulletTime.\n");
    }
    else
    {
        engine->ClientCmd("host_timescale 1");
        Msg("BulletTime disabled. Time restored to normal.\n");
    }
}

CON_COMMAND(toggle_bullettime, "Toggle BulletTime (slow motion).")
{
    ToggleBulletTime();
}

#endif // CLIENT_DLL