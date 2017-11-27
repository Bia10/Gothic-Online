#ifndef CSCRIPT_H
#define CSCRIPT_H

#define MAX_SCRIPT_SIZE 65535
#define scr CScript::GetInstance()

class CScript
{
private:
	HSQUIRRELVM vm;
	SScript* scriptVars;
	SKey* scriptKeys;
	bool isScriptLoaded;

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
	inline SScript* GetScriptVars() const { return this->scriptVars; };
	inline SKey* GetScriptKeys()	const { return this->scriptKeys; };
	inline bool IsScriptLoaded()	const { return this->isScriptLoaded; };

	static void PrintFunction(HSQUIRRELVM vm, const SQChar *s, ...);
	static void PrintErrors(HSQUIRRELVM vm, const SQChar *s, ...);
	static SQInteger RuntimeErrors(HSQUIRRELVM vm);
	static void CompileErrors(HSQUIRRELVM vm, const SQChar* description, const SQChar* file, SQInteger line, SQInteger column);

	bool StartScript(const char* fileName);
	void OnRender();
};

#endif //CSCRIPT_H