/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __API_G2_ZCOBJECT_H__
#define __API_G2_ZCOBJECT_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"

class zCArchiver;

/** ZenGin object base class. */
class zCObject
{
private:
	int		_vtbl;
protected:
	int		refCtr;
	int		hashIndex;
	int		hashNext;
	zSTRING objectName;
public:    
	//.text:00401ED0 ; public: virtual void __thiscall zCObject::Archive(class zCArchiver &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Archive(zCArchiver & pA)
	{
		XCALL(0x00401D90);
	};

	//.text:005A90A0 ; public: class zCObject * __thiscall zCObject::CreateCopy(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	zCObject* CreateCopy(void)
	{
		XCALL(0x00589630);
	};

	//.text:005A9CD0 ; public: class zSTRING const & __thiscall zCObject::GetObjectName(void)const
	/** Insert description. 
	* @usable Ingame only
	*/
	zSTRING & GetObjectName(void)
	{
		XCALL(0x0058A160);
	};

	//.text:0040C310 ; public: int __thiscall zCObject::Release(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	int Release(void)
	{
		XCALL(0x0042AC30);
	};

	//.text:005A9CE0 ; public: int __thiscall zCObject::SetObjectName(class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	int SetObjectName(zSTRING & pA)
	{
		XCALL(0x0058A170);
	};

	//.text:00401EE0 ; public: virtual void __thiscall zCObject::Unarchive(class zCArchiver &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Unarchive(zCArchiver & pA)
	{
		XCALL(0x00401DA0);
	};	
};

class zCObjectNVT
{
private:
	//int		_vtbl;
protected:
	int		refCtr;
	int		hashIndex;
	int		hashNext;
	zSTRING objectName;
};
#undef __G2EXT_API_HEADER

#endif //__API_G2_ZCOBJECT_H__