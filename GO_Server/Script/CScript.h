#ifndef CSCRIPT_H
#define CSCRIPT_H

#define MAX_SCRIPT_SIZE 65535
#define scr CScript::GetInstance()

class CScript
{
private:
	HSQUIRRELVM vm;

	CScript();
	CScript( const CScript & ) {};
	~CScript();

public:
	static CScript & GetInstance()
	{
		static CScript script;
		return script;
	}

	
	inline HSQUIRRELVM& GetVM()			  { return this->vm; };

	static void PrintFunction(HSQUIRRELVM vm, const SQChar *s, ...);
	static void PrintErrors(HSQUIRRELVM vm, const SQChar *s, ...);
	static SQInteger RuntimeErrors(HSQUIRRELVM vm);
	static void CompileErrors(HSQUIRRELVM vm, const SQChar* description, const SQChar* file, SQInteger line, SQInteger column);

	bool StartScript(const char* fileName);
	void OnTick();
};

#endif //CSCRIPT_H