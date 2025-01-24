//========= Copyright Team ReCharged, All rights reserved. ============//
//
// Purpose: Boreal Revive's implementation of AK-47 in HL2 ReCharged
//
//=============================================================================//
#include "cbase.h"
#include "basehlcombatweapon.h"
#include "npcevent.h"
#include "basecombatcharacter.h"
#include "ai_basenpc.h"
#include "player.h"
#include "game.h"
#include "in_buttons.h"
#include "ai_memory.h"
#include "soundent.h"
#include "rumble_shared.h"
#include "gamestats.h"

#define ROF 0.075f // Rate of Fire

class CWeaponAK47 : public CBaseHLCombatWeapon
{
public:
	DECLARE_CLASS(CWeaponAK47, CBaseHLCombatWeapon);

	CWeaponAK47();

	DECLARE_DATADESC();

	void Precache();
	void PrimaryAttack();
	void AddViewKick();
	bool Reload();
	bool Holster(CBaseCombatWeapon *pSwitchingTo = NULL);
	Activity GetPrimaryAttackActivity();

	int GetMinBurst() { return 2; }
	int GetMaxBurst() { return 5; }
	int	m_nShotsFired;
	float GetFireRate() { return ROF; }

	virtual const Vector &GetBulletSpread();

private:
	float m_flAttackEnds;
	int m_iStance;
};

LINK_ENTITY_TO_CLASS(weapon_ak47, CWeaponAK47);
PRECACHE_WEAPON_REGISTER(weapon_ak47);

BEGIN_DATADESC(CWeaponAK47)
DEFINE_FIELD(m_flAttackEnds, FIELD_TIME),
DEFINE_FIELD(m_iStance, FIELD_INTEGER),
END_DATADESC()

CWeaponAK47::CWeaponAK47()
{
	m_fMinRange1 = 1;
	m_fMaxRange1 = 1500;
	m_fMinRange2 = 1;
	m_fMaxRange2 = 200;
	m_bFiresUnderwater = false;
}

void CWeaponAK47::Precache()
{
	BaseClass::Precache();
}

Activity CWeaponAK47::GetPrimaryAttackActivity(void)
{
	if (m_nShotsFired < 2)
		return ACT_VM_PRIMARYATTACK;

	if (m_nShotsFired < 3)
		return ACT_VM_RECOIL1;

	if (m_nShotsFired < 4)
		return ACT_VM_RECOIL2;

	return ACT_VM_RECOIL3;
}

void CWeaponAK47::PrimaryAttack()
{
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
	if (!pPlayer)
		return;

	WeaponSound(SINGLE);
	pPlayer->DoMuzzleFlash();
	SendWeaponAnim(ACT_VM_PRIMARYATTACK);
	pPlayer->SetAnimation(PLAYER_ATTACK1);

	BaseClass::PrimaryAttack();

	m_flNextPrimaryAttack = gpGlobals->curtime + ROF;
	m_flAttackEnds = gpGlobals->curtime + SequenceDuration();
}

bool CWeaponAK47::Reload()
{
	bool fRet = DefaultReload(GetMaxClip1(), GetMaxClip2(), ACT_VM_RELOAD);
	if (fRet)
	{
		WeaponSound(RELOAD);
	}
	return fRet;
}

bool CWeaponAK47::Holster(CBaseCombatWeapon *pSwitchingTo)
{
	return BaseClass::Holster(pSwitchingTo);
}

void CWeaponAK47::AddViewKick()
{
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
	if (!pPlayer)
		return;

	QAngle viewPunch;
	viewPunch.x = random->RandomFloat(0.25f, 0.5f);
	viewPunch.y = random->RandomFloat(-.6f, .6f);
	viewPunch.z = 0.0f;

	pPlayer->ViewPunch(viewPunch);
}

const Vector &CWeaponAK47::GetBulletSpread()
{
	static Vector cone = VECTOR_CONE_3DEGREES;
	return cone;
}