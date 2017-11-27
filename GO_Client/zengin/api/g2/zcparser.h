/* Gothic Online ZenGin research (based on g2ext) */


#ifndef __API_G2_ZCPARSER_H__
#define __API_G2_ZCPARSER_H__

#ifndef __G2EXT_API_HEADER
#define __G2EXT_API_HEADER
#endif  //__G2EXT_API_HEADER

#ifdef _G2EXT_COMPILE_SPACER
#error Cannot use gothic headers on spacer dll (_G2EXT_COMPILE_SPACER defined)
#endif

#include "api/g2/ztypes.h"
#include "api/g2/macros.h"

#include "api/g2/zcpar_symbol.h"

#pragma warning(disable:4731) // -- suppress C4731:"frame pointer register 'ebp' modified by inline assembly code"

class zCPar_File;
class zCPar_TreeNode;
class zCViewProgressBar;
class zCView;

/** Insert description */
typedef struct 
{
	zCPar_Symbol*	preAllocatedSymbols;
	int				nextPreAllocated;
} zCPar_SymbolTable;

/** Insert description. */
typedef enum  
{
	zCPVOID, 
	zCPFLOAT, 
	zCPINT, 
	zCPSTRING, 
	zCPCLASS, 
	zCPFUNC,
	zCPPROTOTYPE, 
	zCPINSTANCE
} zCParser_CallType;

#define zMAX_SYM_DATASTACK 2048

/** ZenGin Daedalus script parser. */
class zCParser
{
private:
	void (__cdecl * msgfunc)( zSTRING );

	zCArray<zCPar_File*>	file;
	zCPar_SymbolTable		symtab;
	zCArray<zCPar_Symbol*>  table;
	zCArraySort<int>		tablesort;

	zCPar_Symbol*			lastsym;
	zCPar_Symbol*			firstsym; 

	//zCPar_StringTable stringtab;
	zCArray<zSTRING*>		stringtab;

	//zCPar_Stack               stack;
	int stack_stack;                            //0x0048 zBYTE*  // Stackbegin
	int stack_stackptr;                         //0x004C zBYTE* or zWORD* or int*
	int stack_stacklast;                        //0x0050 zBYTE* or zWORD* or int*
	int stack_stacksize;                        //0x0054 int //Stack size in Bytes

	//zCPar_DataStack           datastack;
	int stack[zMAX_SYM_DATASTACK];				//0x0058
	int sptr;                                   //0x085C int

	zCPar_Symbol* _self;

	zSTRING fname;
	zSTRING mainfile;
	int compiled;          
	int treesave;               
	int datsave;              
	int parse_changed;
	int treeload;
	int mergemode;             
	int linkingnr;
	int linec;
	int line_start;
	int ext_parse;
	char* pc_start;
	char* pc;
	char* oldpc;
	char* pc_stop;
	char* oldpc_stop;
	int params;
	int in_funcnr;
	int in_classnr;
	int stringcount;
	zCPar_Symbol* in_func;
	zCPar_Symbol* in_class;
	int error;
	int stop_on_error;
	int errorline;
	char* prevword_index[16];
	int prevline_index[16];
	int prevword_nr;
	zSTRING  aword;     
	int _instance;           
	int instance_help;
	zCViewProgressBar* progressBar;
	zCPar_TreeNode* tree;
	zCPar_TreeNode* treenode;
	zCView* win_code;
	int debugmode;
	int curfuncnr;
	int labelcount;
	int* labelpos;

	//zCList <zSTRING>*     add_funclist;
	zCList<zSTRING*> add_funclist;
	int add_funclist_data;							//zString*
	int add_funclist_next;							//zCList<zSTRING>*

	zSTRING add_filename;                            //zSTRING                          
	int add_created;                                //zBOOL
public:
	//.text:0078DED0 ; public: __thiscall zCParser::zCParser(int)
	/** Constructor.
	* @param  Unknown
	* @usable Ingame only
	*/
	zCParser(int pA = 100)
	{
		XCALL(0x006E4CA0);
	};

	//.text:007900E0 ; public: void __thiscall zCParser::CreatePCode(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void CreatePCode(void)
	{
		XCALL(0x006E6EB0);
	};

	//.text:007929F0 ; int __cdecl zCParser__CallFunc(int, ...)
	/** Insert description. 
	* @usable Ingame only
	* @return	A *pointer* to the returnvalue (int/float)
	*/
	void* CallFunc(int pA, ...)
	{
		XCALL(0x006E9690);
	};

	//.text:007929D0 ; public: void * __thiscall zCParser::CallFunc(class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	* @return	A *pointer* to the returnvalue (int/float)
	*/
	void* CallFunc(const zSTRING & pA)
	{
		XCALL(0x006E9670);
	};

	//.text:00794470 ; public: int __thiscall zCParser::CheckClassSize(int, int)
	/** Insert description. 
	* @usable Ingame only
	*/
	int CheckClassSize(int pA, int pB)
	{
		XCALL(0x006EB010);
	};

	//.text:00794450 ; public: int __thiscall zCParser::CheckClassSize(class zSTRING &, int)
	/** Insert description. 
	* @usable Ingame only
	*/
	int CheckClassSize(zSTRING & pA, int pB)
	{
		XCALL(0x006EAFF0);
	};

	//.text:00792FA0 ; public: int __thiscall zCParser::CreateInstance(int, void *)
	/** Insert description. 
	* @usable Ingame only
	*/
	int CreateInstance(int pA, void * pB)
	{
		XCALL(0x006E9BE0);
	};

	//.text:00792F20 ; public: int __thiscall zCParser::CreateInstance(class zSTRING &, void *)
	/** Insert description. 
	* @usable Ingame only
	*/
	int CreateInstance(zSTRING & pA, void * pB)
	{
		XCALL(0x006E9B60);
	};

	//.text:007A0190 ; public: void __cdecl zCParser::DefineExternal(class zSTRING const &, int (__cdecl *)(void), int, int, ...)
	/** Insert description. 
	* @usable Ingame only
	*/
	int DefineExternal(const zSTRING & a_SymbolName, zBOOL(__cdecl*a_ExternalProc)(), int a_ReturnType, int a_ParameterType, ...)
	{
		XCALL(0x006F6840);			
	};

	//.text:0078E730 ; public: int __thiscall zCParser::Error(void)		
	/** Insert description. 
	* @usable Ingame only
	*/
	zBOOL Error(void)
	{
		XCALL(0x006E54B0);
	};

	//.text:00793610 ; public: int __thiscall zCParser::GetBaseClass(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	int GetBaseClass(int instance)
	{
		XCALL(0x006EA260);
	};

	/** Insert description. 
	* @usable Ingame only
	*/
	void GetParameter(float & pA)
	{
		XCALL(0x006F6E00);
	};

	//.text:007A0760 ; public: void __thiscall zCParser::GetParameter(int &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void GetParameter(int & pA)
	{
		XCALL(0x006F6DF0);
	};

	//.text:00793470 ; public: int __thiscall zCParser::GetIndex(class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void GetParameter(const zSTRING & pA)
	{
		XCALL(0x006F6E40);
	};

	//.text:00793730 ; public: int __thiscall zCParser::GetInstance(int, int)
	/** Gets an instance from Daedalus.
	* @usable In an external only
	* @param ClassId	return value of GetIndex(zSTRING& class)
	* @param Index		instance number (index of array only containing instances of this class)
	* @return			Daedalus instance index (you get this one when you pass an Instance as an Integer parameter)
	*/
	int GetInstance(int ClassId, int Index)
	{
		XCALL(0x006EA380);
	};

	//.text:007A08F0 ; public: void * __thiscall zCParser::GetInstance(void)
	/** Gets an instance from the Daedalus stack.
	 * @usable In an external only
	 * @return	A pointer to the object instance.
	 */
	void* GetInstance(void)
	{
		XCALL(0x006F6F80);
	};

	//.text:00793FD0 ; public: class zSTRING __thiscall zCParser::GetInstanceValue(int, int, void *, int)
	/** Insert description. 
	* @usable Ingame only
	*/
	zSTRING GetInstanceValue(int pA, int pB, void * pC, int pD)
	{
		XCALL(0x006EAC20);
	};

	//.text:00793470 ; public: int __thiscall zCParser::GetIndex(class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	int GetIndex(class zSTRING const & pA)
	{
		XCALL(0x006EA0C0);
	};

	//.text:007938D0 ; public: class zCPar_Symbol * __thiscall zCParser::GetSymbol(class zSTRING const &)
	/** Insert description. 
	* @usable Ingame only
	*/
	zCPar_Symbol* GetSymbol(const zSTRING& pA)
	{
		XCALL(0x006EA520);
	};

	//.text:007938C0 ; public: class zCPar_Symbol * __thiscall zCParser::GetSymbol(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	zCPar_Symbol* GetSymbol(int pA)
	{
		XCALL(0x006EA510);
	};

	//.text:0078D010 ; public: static unsigned char __cdecl zCParser::GetVersion(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	static zBYTE GetVersion(void)
	{
		XCALL(0x006E3DB0);
	};

	//.text:0078E900 ; public: int __thiscall zCParser::LoadDat(class zSTRING &)
	/** Loads a compiled *.dat file
	* @param  File name
	* @usable Ingame only
	*/
	int LoadDat(zSTRING & zsFileName)
	{
		XCALL(0x006E5680);
	};

	//.text:00791650 ; public: int __thiscall zCParser::MergeFile(class zSTRING &)
	/** Insert description. 
	* @usable Ingame only
	*/
	int MergeFile(zSTRING & zsFileName)
	{
		XCALL(0x006E82F0);
	};

	//.text:0078EBA0 ; public: int __thiscall zCParser::Parse(class zSTRING)
	/** Parses a *.d or a *.src file
	* @param  File name
	* @usable Ingame only
	*/
	int Parse(zSTRING zsFileName)
	{
		XCALL(0x006E5920);
	};

	//.text:0078F660 ; public: int __thiscall zCParser::ParseFile(class zSTRING &)
	/** Parses a *.d file
	* @param  File name
	* @usable Ingame only
	*/
	int ParseFile(zSTRING & zsFileName)
	{
		XCALL(0x006E63E0);
	};

	//.text:0078EE20 ; public: int __thiscall zCParser::ParseSource(class zSTRING &)
	/** Parses a *.src file
	* @param  File name
	* @usable Ingame only
	*/
	int ParseSource(zSTRING & zsFileName)
	{
		XCALL(0x006E5BA0);
	};
	
	//.text:00793100 ; public: void __thiscall zCParser::Reset(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void Reset(void)
	{
		XCALL(0x006E9D40);
	};

	//.text:007969C0 ; public: int __thiscall zCParser::ResetGlobalVars(void)
	/** Insert description. 
	* @usable Ingame only
	*/
	void ResetGlobalVars(void)
	{
		XCALL(0x006ED340);
	};

	//.text:0078E740 ; public: int __thiscall zCParser::SaveDat(class zSTRING &)
	/** Saves a compiled *.dat file
	* @param  File name
	* @usable Ingame only
	*/
	int SaveDat(zSTRING & zsFileName)
	{
		XCALL(0x006E54C0);
	};

	//.text:007A0980 ; public: void __thiscall zCParser::SetReturn(float)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetReturn(float pA)
	{
		XCALL(0x006F6FD0);
	};

	//.text:007A0960 ; public: void __thiscall zCParser::SetReturn(int)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetReturn(int pA)
	{
		XCALL(0x006F6FB0);
	};

	//.text:007A09A0 ; public: void __thiscall zCParser::SetReturn(void *)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetReturn(void * pA)
	{
		XCALL(0x006F6FF0);
	};

	//.text:007A09D0 ; public: void __thiscall zCParser::SetReturn(class zSTRING &)
	/** Insert description. 
	* @usable Ingame only
	*/
	void SetReturn(zSTRING & pA)
	{
		XCALL(0x006F7020);
	};

	/** This method returns the current zCParser instance
	* @usable Ingame only
	*/
	static zCParser* GetParser()
	{
		return (zCParser*)0x008DCE08;
	};
};

#undef __G2EXT_API_HEADER

#endif // __API_G2_ZCPARSER_H__

