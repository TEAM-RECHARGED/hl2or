//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//

#ifndef WEAPON_WRENCH_H
#define WEAPON_WRENCH_H

#include "basebludgeonweapon.h"

#if defined( _WIN32 )
#pragma once
#endif

#ifdef HL2MP
#error weapon_crowbar.h must not be included in hl2mp. The windows compiler will use the wrong class elsewhere if it is.
#endif

#define	WRENCH_RANGE	75.0f
#define	WRENCH_REFIRE	0.4f

//-----------------------------------------------------------------------------
// CWeaponWrench
//-----------------------------------------------------------------------------

class CWeaponWrench : public CBaseHLBludgeonWeapon
{
public:
	DECLARE_CLASS(CWeaponWrench, CBaseHLBludgeonWeapon);

	DECLARE_SERVERCLASS();
	DECLARE_ACTTABLE();

	CWeaponWrench();

	float		GetRange(void) { return	WRENCH_RANGE; }
	float		GetFireRate(void) { return	WRENCH_REFIRE; }

	void		AddViewKick(void);
	float		GetDamageForActivity(Activity hitActivity);

	virtual int WeaponMeleeAttack1Condition(float flDot, float flDist);
	void		SecondaryAttack(void) { return; }

	// Animation event
	virtual void Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator);

private:
	// Animation event handlers
	void HandleAnimEventMeleeHit(animevent_t* pEvent, CBaseCombatCharacter* pOperator);
};

#endif // WEAPON_WRENCH_H