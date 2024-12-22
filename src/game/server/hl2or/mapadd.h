//========= Copyright Overcharged Redux Team, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================
#ifndef MAPADD_H
#define MAPADD_H
#ifdef _WIN32
#pragma once
#endif

class CMapAdd : public CBaseEntity
{
public:
	DECLARE_CLASS(CMapAdd, CBaseEntity);
	DECLARE_DATADESC();

	CMapAdd()
	{
		bFirstRun = true;
	}

	virtual void Precache(void);
	bool RunLabel(const char* szLabel);
	bool HandlePlayerEntity(KeyValues* playerEntity, bool initLevel = false);
	bool HandleSpecialEnitity(KeyValues* specialEntity);
	bool HandleRemoveEnitity(KeyValues* mapaddValue);
	void InputRunLabel(inputdata_t& inputData);
private:
	bool bFirstRun;
};
CMapAdd* GetMapAddEntity();
CMapAdd* CreateMapAddEntity();


#endif	//HL2_PLAYER_H