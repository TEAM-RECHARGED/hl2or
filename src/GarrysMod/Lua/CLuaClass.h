#ifndef LUA_CLASS_H
#define LUA_CLASS_H

#include "ILuaInterface.h"
#include "mathlib/vector.h"
#include <vector>
#include "Bootil/Bootil.h"
#include <list>
#include <filesystem.h>
#include <materialsystem/itexture.h>

class CBaseEntity;
class CLuaObject : public ILuaObject
{
public:
	virtual void Set( ILuaObject *obj );
	virtual void SetFromStack( int i );
	virtual void UnReference( );

	virtual int GetType( );
	virtual const char *GetString( );
	virtual float GetFloat( );
	virtual int GetInt( );
	virtual void *GetUserData( );

	virtual void SetMember( const char *name );
	virtual void SetMember( const char *name, ILuaObject *obj );
	virtual void SetMember( const char *name, float val );
	virtual void SetMember( const char *name, bool val );
	virtual void SetMember( const char *name, const char *val );
	virtual void SetMember( const char *name, CFunc f );

	virtual bool GetMemberBool( const char *name, bool b = true );
	virtual int GetMemberInt( const char *name, int i = 0 );
	virtual float GetMemberFloat( const char *name, float f = 0.0f );
	virtual const char *GetMemberStr( const char *name, const char *s = "" );
	virtual void *GetMemberUserData( const char *name, void *u = 0 );
	virtual void *GetMemberUserData( float name, void *u = 0 );
	virtual ILuaObject *GetMember( const char *name, ILuaObject *obj );
	virtual ILuaObject *GetMember( ILuaObject *key, ILuaObject *obj );

	virtual void SetMetaTable( ILuaObject *obj );
	virtual void SetUserData( void *obj );

	virtual void Push( );

	virtual bool isNil( );
	virtual bool isTable( );
	virtual bool isString( );
	virtual bool isNumber( );
	virtual bool isFunction( );
	virtual bool isUserData( );

	virtual ILuaObject *GetMember( float fKey, ILuaObject* obj );

	virtual void *Remove_Me_1( const char *name, void * = 0 );

	virtual void SetMember( float fKey );
	virtual void SetMember( float fKey, ILuaObject *obj );
	virtual void SetMember( float fKey, float val );
	virtual void SetMember( float fKey, bool val );
	virtual void SetMember( float fKey, const char *val );
	virtual void SetMember( float fKey, CFunc f );

	virtual const char *GetMemberStr( float name, const char *s = "" );

	virtual void SetMember( ILuaObject *k, ILuaObject *v );
	virtual bool GetBool( );

	virtual bool PushMemberFast( int iStackPos );
	virtual void SetMemberFast( int iKey, int iValue );

	virtual void SetFloat( float val );
	virtual void SetString( const char *val );

	virtual double GetDouble( );

	virtual void SetMember_FixKey( const char *, float );
	virtual void SetMember_FixKey( const char *, const char * );
	virtual void SetMember_FixKey( const char *, ILuaObject * );
	virtual void SetMember_FixKey( const char *, double );
	virtual void SetMember_FixKey( const char *, int );

	virtual bool isBool( );

	virtual void SetMemberDouble( const char *, double );

	virtual void SetMemberNil( const char * );
	virtual void SetMemberNil( float );

	virtual bool RemoveMe( );

	virtual void Init( );

	virtual void SetFromGlobal( const char * );

	virtual int GetStringLen( unsigned int * );

	virtual unsigned int GetMemberUInt( const char *, unsigned int );

	virtual void SetMember( const char *, unsigned long long );
	virtual void SetMember( const char *, int );
	virtual void SetReference( int );

	virtual void RemoveMember( const char * );
	virtual void RemoveMember( float );

	virtual bool MemberIsNil( const char * );

	virtual void SetMemberDouble( float, double );
	virtual double GetMemberDouble( const char *, double );

	virtual BaseEntity *GetMemberEntity( const char *, BaseEntity * );
	virtual void SetMemberEntity( float, BaseEntity * );
	virtual void SetMemberEntity( const char *, BaseEntity * );
	virtual bool isEntity( );
	virtual BaseEntity *GetEntity( );
	virtual void SetEntity( BaseEntity * );

	virtual void SetMemberVector( const char *, Vector * );
	virtual void SetMemberVector( const char *, Vector & );
	virtual void SetMemberVector( float, Vector * );
	virtual Vector *GetMemberVector( const char *, const Vector * );
	virtual Vector *GetMemberVector( int );
	virtual Vector *GetVector( );
	virtual bool isVector( );

	virtual void SetMemberAngle( const char *, QAngle * );
	virtual void SetMemberAngle( const char *, QAngle & );
	virtual QAngle *GetMemberAngle( const char *, QAngle * );
	virtual QAngle *GetAngle( );
	virtual bool isAngle( );

	virtual void SetMemberMatrix( const char *, VMatrix const * );
	virtual void SetMemberMatrix( const char *, VMatrix const & );
	virtual void SetMemberMatrix( float, VMatrix const * );
	virtual void SetMemberMatrix( int, VMatrix const * );

	virtual void SetMemberPhysObject( const char *, IPhysicsObject * );
public:
	void Init(ILuaInterface*);
protected:
	bool m_bUserData;
	int m_iLUA_TYPE;
	int m_reference;
	ILuaInterface* m_pLua;
};

#define CLuaFunc GarrysMod::Lua::CFunc
typedef void (*CLuaClassFunc)();

class CLuaClass // This is somewhat how gmod does it but not exactly.
{
public:
	CLuaClass(const char* name, int type, CLuaClassFunc func, const char* baseclass = NULL); // const char*
	//void Add(CLuaClassFunc func);
	void* Get(int index);
	void Push(void*);
	void MetaTableDerive();

public:
	void InitClass();

private:
	const char* m_strName = NULL;
	const char* m_strBaseClass = NULL;
	unsigned char m_iType = NULL;
	CLuaClassFunc m_pInitFunc;
	int m_iReference = -1;
};

extern void InitLuaClasses(ILuaInterface* LUA);

class CLuaLibrary // Not how Gmod does it but I want it to work for now.
{
public:
	CLuaLibrary(const char* name, CLuaClassFunc func);
	void Add(CLuaClassFunc func);
	void Push();

private:
	const char* m_strName;
	std::vector<CLuaClassFunc> m_pFuncs;
};
extern void InitLuaLibraries(ILuaInterface* LUA);

// Lua classes. Fix this later. ToDo: Rename classes to LC_Vector, LC_Angle and so on.
extern CLuaClass angle_class;
extern CLuaClass vector_class;
extern CLuaClass entity_class;
extern CLuaClass texture_class;
extern CLuaClass material_class;
extern CLuaClass recipientfilter_class;
extern CLuaClass LC_bf_read;
extern CLuaClass LC_ConVar;

namespace Lua
{
	extern CLuaClass LC_File;
}

// Lua Libraries. Fix this later
extern CLuaLibrary ents_library;
extern CLuaLibrary umsg_library;
extern CLuaLibrary file_library;
extern CLuaLibrary LL_Global;
#ifdef CLIENT_DLL
extern CLuaLibrary LL_Render;
#endif

#ifdef GAME_DLL
extern CLuaLibrary LL_Engine;
#endif


// Lua push functions

extern QAngle* Get_Angle(int index);
// Pushes the given QAngle and deletes it when it's unused!
extern void Push_Angle(const QAngle* ang);

// Pushes the given QAngle and deletes it when it's unused!
class ConVar;
extern void Push_ConVar(const ConVar* convar);


extern Vector* Get_Vector(int index);
// Pushes the given Vector and deletes it when it's unused!
extern void Push_Vector(const Vector* vec);

extern ITexture* Get_Texture(int index);
extern void Push_Texture(const ITexture *vec);

extern IMaterial *Get_Material(int index);
extern void Push_Material(const IMaterial *vec);


#ifndef MENUSYSTEM
extern CBaseEntity* Get_Entity(int index);
extern void Push_Entity(CBaseEntity* ent);

#ifdef GAME_DLL
extern CRecipientFilter* Get_CRecipientFilter(int index);
// Pushes the given Vector and deletes it when it's unused!
extern void Push_CRecipientFilter(CRecipientFilter* filter);
#else
class bf_read;
extern void Push_bf_read( const bf_read* msg );
#endif
#endif

// File library
namespace GarrysMod::Lua::Libraries::File
{
	 // ToDo: get Gmod's struct. 
	 // Until then use this version. 
	 // 
	 // BUG: What if multiple ILuaInterfaces use the same version? 
	 // It would probably break it by trying to call the callback from the registry 123 which could be anything since the registry will be different in each ILuaInterface.
	struct FileAsyncCallback
	{
		int iCallback = -1;
		int iBytesRead = 0;
		int iStatus = -1;
		const char* strContent = NULL;
		const char* strFileName = NULL;
		const char* strPathID = NULL;
	};

	extern void AsyncCycle();
	extern void FileAsyncReadCallback( const FileAsyncRequest_t &request, int nBytesRead, FSAsyncStatus_t err );
	extern Bootil::Threads::Mutex FileAsyncCallbackListMutex;
	extern std::list<FileAsyncCallback*> FileAsyncCallbackList;
}

#endif