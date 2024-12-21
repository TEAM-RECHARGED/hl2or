#include "cbase.h"
#ifdef CLIENT_DLL
#include "beamdraw.h"
#include "c_basehlcombatweapon.h"
#include "c_weapon__stubs.h"
#include "clienteffectprecachesystem.h"	
#include "decals.h"						
#include "iefx.h"
#include "tier0/memdbgon.h"

CLIENTEFFECT_REGISTER_BEGIN(PrecacheEffectIontau)
CLIENTEFFECT_MATERIAL("sprites/bluelaser1") 
CLIENTEFFECT_REGISTER_END()

class C_IontauBeam : public CDefaultClientRenderable
{
public:
	C_IontauBeam();

	void Update(C_BaseEntity* pOwner);
	void AddDecal(trace_t& tr);

	matrix3x4_t z;
	const matrix3x4_t& RenderableToWorldTransform() { return z; }

	virtual const Vector& GetRenderOrigin(void) { return m_worldPosition; }
	virtual const QAngle& GetRenderAngles(void) { return vec3_angle; }
	virtual bool ShouldDraw(void) { return true; }
	virtual bool IsTransparent(void) { return true; }
	virtual bool ShouldReceiveProjectedTextures(int flags) { return false; }
	virtual int DrawModel(int flags);

	virtual void GetRenderBounds(Vector& mins, Vector& maxs)
	{
		mins.Init(-32, -32, -32);
		maxs.Init(32, 32, 32);
	}

	C_BaseEntity* m_pOwner;
	Vector m_targetPosition;
	Vector m_worldPosition;
	int m_active;
	int m_viewModelIndex;
};

class C_WeaponIontau : public C_BaseHLCombatWeapon
{
	DECLARE_CLASS(C_WeaponIontau, C_BaseHLCombatWeapon);
public:
	C_WeaponIontau() {}
	DECLARE_CLIENTCLASS();
	DECLARE_PREDICTABLE();
	void OnDataChanged(DataUpdateType_t updateType)
	{
		BaseClass::OnDataChanged(updateType);
		m_beam.Update(this); 
	}

private:
	C_WeaponIontau(const C_WeaponIontau&);
	C_IontauBeam m_beam;
};

STUB_WEAPON_CLASS_IMPLEMENT(weapon_iontau, C_WeaponIontau);

IMPLEMENT_CLIENTCLASS_DT(C_WeaponIontau, DT_WeaponIontau, CWeaponIontau)
RecvPropVector(RECVINFO_NAME(m_beam.m_targetPosition, m_targetPosition)),
RecvPropVector(RECVINFO_NAME(m_beam.m_worldPosition, m_worldPosition)),
RecvPropInt(RECVINFO_NAME(m_beam.m_active, m_active)),
RecvPropInt(RECVINFO_NAME(m_beam.m_viewModelIndex, m_viewModelIndex)),
END_RECV_TABLE()

C_IontauBeam::C_IontauBeam()
{
	m_pOwner = NULL;
	m_hRenderHandle = INVALID_CLIENT_RENDER_HANDLE;
}

void C_IontauBeam::Update(C_BaseEntity* pOwner)
{
	m_pOwner = pOwner;
	if (m_active)
	{
		if (m_hRenderHandle == INVALID_CLIENT_RENDER_HANDLE)
			ClientLeafSystem()->AddRenderable(this, RENDER_GROUP_TRANSLUCENT_ENTITY);
		else
			ClientLeafSystem()->RenderableChanged(m_hRenderHandle);
	}
	else if (!m_active && m_hRenderHandle != INVALID_CLIENT_RENDER_HANDLE)
	{
		ClientLeafSystem()->RemoveRenderable(m_hRenderHandle);
		m_hRenderHandle = INVALID_CLIENT_RENDER_HANDLE;
	}
}
void C_IontauBeam::AddDecal(trace_t& tr)
{
	C_BaseEntity* ent = cl_entitylist->GetEnt(0); 
	if (ent != NULL)
	{
		int index = decalsystem->GetDecalIndexForName("RedGlowFade"); 
		if (index >= 0)
		{
			Vector endPos;
			endPos.Random(-4.0f, 4.0f);
			endPos += tr.endpos;

			effects->DecalShoot(index, 0, ent->GetModel(), ent->GetAbsOrigin(), ent->GetAbsAngles(), endPos, 0, 0);
		}
	}
}

int C_IontauBeam::DrawModel(int flags)
{
	Vector points[3];
	QAngle tmpAngle;
	if (!m_active)
		return 0;
	C_BaseEntity* pEnt = cl_entitylist->GetEnt(m_viewModelIndex);
	if (!pEnt)
		return 0;
	pEnt->GetAttachment(1, points[0], tmpAngle);
	points[1] = 0.5 * (m_targetPosition + points[0]);
	points[1].z += 4 * sin(gpGlobals->curtime * 11) + 5 * cos(gpGlobals->curtime * 13);
	points[2] = m_worldPosition;
	trace_t tr;
	UTIL_TraceLine(points[0], points[2], MASK_SHOT, NULL, COLLISION_GROUP_NONE, &tr);
	AddDecal(tr);
	IMaterial* pMat = materials->FindMaterial("sprites/bluelaser1", TEXTURE_GROUP_CLIENT_EFFECTS);
	Vector color;
	color.Init(0, 0, 1);
	float scrollOffset = gpGlobals->curtime - (int)gpGlobals->curtime;
	CMatRenderContextPtr pRenderContext(materials);
	pRenderContext->Bind(pMat);

	DrawBeamQuadratic(points[0], points[1], points[2], 13, color, scrollOffset);

	return 1;
}
#else
#include "basehlcombatweapon.h"	
#include "ammodef.h"			
#include "in_buttons.h"

#define IONTAU_AMMO_RATE 0.2						
#define IONTAU_BEAM_SPRITE "sprites/bluelaser1.vmt"	
#define IONTAU_ATTACK_RATE 0.0625f					
static int g_iontauBeam;					
class CWeaponIontau : public CBaseHLCombatWeapon
{
	DECLARE_DATADESC();
public:
	DECLARE_CLASS(CWeaponIontau, CBaseHLCombatWeapon);
	CWeaponIontau();			
	void Spawn(void);			
	void Precache(void);		
	void PrimaryAttack(void);	
	void WeaponIdle(void);		
	void ItemPostFrame(void);	

	virtual bool Holster(CBaseCombatWeapon* pSwitchingTo)
	{
		m_active = false;
		return BaseClass::Holster(pSwitchingTo);
	}

	void EffectUpdate(void); 
	void AddViewKick(void);	 
	DECLARE_SERVERCLASS();

protected:
	CNetworkVector(m_targetPosition);	
	CNetworkVector(m_worldPosition);	
	CNetworkVar(int, m_active);			
	CNetworkVar(int, m_viewModelIndex);	
	float m_flNextAttackTime;			
};

IMPLEMENT_SERVERCLASS_ST(CWeaponIontau, DT_WeaponIontau)
SendPropVector(SENDINFO_NAME(m_targetPosition, m_targetPosition), -1, SPROP_COORD),
SendPropVector(SENDINFO_NAME(m_worldPosition, m_worldPosition), -1, SPROP_COORD),
SendPropInt(SENDINFO(m_active), 1, SPROP_UNSIGNED),
SendPropModelIndex(SENDINFO(m_viewModelIndex)),
END_SEND_TABLE()
LINK_ENTITY_TO_CLASS(weapon_iontau, CWeaponIontau);
PRECACHE_WEAPON_REGISTER(weapon_iontau);
BEGIN_DATADESC(CWeaponIontau)
DEFINE_FIELD(m_active, FIELD_INTEGER),
DEFINE_FIELD(m_viewModelIndex, FIELD_INTEGER),
DEFINE_FIELD(m_targetPosition, FIELD_POSITION_VECTOR),
DEFINE_FIELD(m_worldPosition, FIELD_POSITION_VECTOR),
DEFINE_FIELD(m_flNextAttackTime, FIELD_TIME),
END_DATADESC()
CWeaponIontau::CWeaponIontau(void)
{
	m_active = false;
	m_targetPosition = vec3_origin;
	m_worldPosition = vec3_origin;
	m_flNextAttackTime = 0;
}

void CWeaponIontau::Spawn(void)
{
	BaseClass::Spawn();
	FallInit();
}

void CWeaponIontau::Precache(void)
{
	BaseClass::Precache();
	g_iontauBeam = PrecacheModel(IONTAU_BEAM_SPRITE);
}

void CWeaponIontau::EffectUpdate(void)
{
	m_active = true;
	Vector start, forward, right, up; 
	trace_t tr;						  
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
		return;

	m_viewModelIndex = pOwner->entindex();
	CBaseViewModel* vm = pOwner->GetViewModel();
	if (vm)
		m_viewModelIndex = vm->entindex();

	pOwner->EyeVectors(&forward, &right, &up);
	start = pOwner->Weapon_ShootPosition();
	Vector aimDir = pOwner->GetAutoaimVector(AUTOAIM_5DEGREES);
	Vector end = start + forward * 4096;
	VectorVectors(aimDir, right, up);
	UTIL_TraceLine(start, end, MASK_SHOT, pOwner, COLLISION_GROUP_NONE, &tr);
	end = m_worldPosition = tr.endpos;		 
	m_targetPosition = start + forward * 25; 

	ClearMultiDamage();
	CBaseEntity* pHit = tr.m_pEnt;

	if (m_flNextAttackTime < gpGlobals->curtime)
	{
		if (pHit != NULL)
		{
			CTakeDamageInfo dmgInfo(this, pOwner, 3, DMG_SHOCK); 
			CalculateBulletDamageForce(&dmgInfo, m_iPrimaryAmmoType, aimDir, tr.endpos);
			pHit->DispatchTraceAttack(dmgInfo, aimDir, &tr);
		}

		if (tr.DidHitWorld() && !(tr.surface.flags & SURF_SKY))
		{
			UTIL_ImpactTrace(&tr, GetAmmoDef()->DamageType(m_iPrimaryAmmoType), "ImpactGauss");
			CPVSFilter filter(tr.endpos);
			te->GaussExplosion(filter, 0.0f, tr.endpos, tr.plane.normal, 0);
		}

		ApplyMultiDamage();

		Vector recoilForce = pOwner->BodyDirection2D() * -(2 * 10.0f);
		recoilForce[2] += 5.0f;

		pOwner->ApplyAbsVelocityImpulse(recoilForce);
		AddViewKick();
		m_flNextAttackTime = gpGlobals->curtime + IONTAU_ATTACK_RATE;
	}
}
void CWeaponIontau::AddViewKick(void)
{
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());
	if (!pPlayer)
		return;

	QAngle viewPunch;
	viewPunch.x = random->RandomFloat(-0.4f, 0.4f); 
	viewPunch.y = random->RandomFloat(-0.4f, 0.4f);
	viewPunch.z = 0;

	pPlayer->ViewPunch(viewPunch);
}

void CWeaponIontau::PrimaryAttack(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
		return;

	if (pOwner->GetAmmoCount(m_iPrimaryAmmoType) <= 0)
	{
		m_active = false;
		return;
	}
	else
	{
		if (!m_active)
		{
			SendWeaponAnim(ACT_VM_PULLBACK); 
			pOwner->SetAnimation(PLAYER_ATTACK1);
			m_active = true;
		}
		else
			EffectUpdate();
	}

	if (m_flNextPrimaryAttack < gpGlobals->curtime)
	{
		pOwner->RemoveAmmo(1, m_iPrimaryAmmoType);
		WeaponSound(SINGLE);
		AddViewKick();
		m_flNextPrimaryAttack = gpGlobals->curtime + IONTAU_AMMO_RATE;
	}
}

void CWeaponIontau::WeaponIdle(void)
{
	SendWeaponAnim(ACT_VM_IDLE);
	if (m_active)
		m_active = false;
}

void CWeaponIontau::ItemPostFrame(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
		return;

	if (pOwner->GetAmmoCount(m_iPrimaryAmmoType) <= 0 || (pOwner->m_afButtonReleased & IN_ATTACK))
	{
		m_active = false;
		WeaponIdle();
		return;
	}

	if (pOwner->m_nButtons & IN_ATTACK)
		PrimaryAttack();
	else
	{
		WeaponIdle();
		return;
	}
}
#endif