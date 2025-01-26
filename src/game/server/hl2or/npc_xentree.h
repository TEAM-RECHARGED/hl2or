//========= Copyright Half-Life 2 ReCharged Team, All rights reserved. ============//
//
// Purpose: 
//
// 
//
//===========================================================================//
#include "ai_basenpc.h"
#include "hl2or\npc_baseflora.h"

class CNPC_XenTree : public CNPC_BaseFlora
{
	DECLARE_CLASS( CNPC_XenTree, CNPC_BaseFlora );

public:
	void Spawn();
	void Precache( void );

	void OnChangeActivity( Activity eNewActivity );
	void HandleAnimEvent( animevent_t *pEvent );

	virtual int SelectExtendSchedule() { return SCHED_MELEE_ATTACK1; }
	virtual int SelectRetractSchedule() { return SCHED_MELEE_ATTACK1; }

protected:
	virtual float GetViewDistance() { return 128.0f; }
	virtual float GetFieldOfView() { return 0.35f; }

private:
};