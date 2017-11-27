#include "..\\stdafx.h"

CScript::CScript()
{
	DLOG("CScript::CScript()");

	scriptVars = new SScript();
	scriptKeys = new SKey();
};

CScript::~CScript()
{
	DLOG("CScript::~CScript()");
	isScriptLoaded = false;
	
	delete scriptVars;
	delete scriptKeys;
};

void CScript::PrintFunction(HSQUIRRELVM vm, const SQChar *s, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, s);
	vsprintf(buffer, s, args);
	va_end(args);

	core.GetChat()->AddLine(RakString(buffer), zCOLOR(255, 0, 0));
	LOG(buffer);
};

void CScript::PrintErrors(HSQUIRRELVM vm, const SQChar *s, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, s);
	vsprintf(buffer, s, args);
	va_end(args);

	core.GetChat()->AddLine(RakString(buffer), zCOLOR(255, 0, 0));
	LOG(buffer);
};

SQInteger CScript::RuntimeErrors(HSQUIRRELVM vm)
{
	const SQChar *errorMessage = NULL;
	if (sq_gettop(vm) >= 1)
	{
		if (SQ_SUCCEEDED(sq_getstring(vm, 2, &errorMessage)))
		{
			core.GetChat()->AddLine(RakString("(Squirrel) Error runtime: %s", errorMessage), zCOLOR(255, 0, 0));
			LOG("(Squirrel) Error runtime: %s", errorMessage);
		}
			
		SQStackInfos stackInfo;
		SQInteger stackDepth = 1;

		core.GetChat()->AddLine(RakString("(Squirrel) Stack Dump:"), zCOLOR(255, 0, 0));
		LOG("(Squirrel) Stack Dump:");
		while (SQ_SUCCEEDED(sq_stackinfos(vm, stackDepth, &stackInfo)))
		{
			const SQChar *func_name = (stackInfo.funcname) ?
				stackInfo.funcname : "unknown_function";
			const SQChar *source_file = (stackInfo.source) ?
				stackInfo.source : "unknown_source_file";

			core.GetChat()->AddLine(RakString("(%d): In function '%s()' %s line (%d)",
				stackDepth, func_name, source_file, stackInfo.line), zCOLOR(255, 0, 0));
			LOG("(%d): In function '%s()' %s line (%d)", stackDepth, func_name, source_file, stackInfo.line);

			++stackDepth;
		}
	}

	return 0;
};

void CScript::CompileErrors(HSQUIRRELVM vm, const SQChar* description, const SQChar* file, SQInteger line, SQInteger column)
{
	core.GetChat()->AddLine(RakString("(Squirrel) Error syntax: '%s' (Ln: %d Col: %d): %s", file, line, column, description), zCOLOR(255, 0, 0));
	LOG("(Squirrel) Error syntax: '%s' (Ln: %d Col: %d): %s", file, line, column, description);
};

bool CScript::StartScript(const char* fileName)
{
	vm = sq_open(1024);
	if (vm)
	{
		sq_pushroottable(vm);
		sq_setprintfunc(vm, CScript::PrintFunction, CScript::PrintErrors);
		sq_setcompilererrorhandler(vm, CScript::CompileErrors);
		sq_newclosure(vm, CScript::RuntimeErrors, 0);
		sq_seterrorhandler(vm);

		// Register global varaiables
		SVaraiable::bindGOVaraiable(vm);

		// Register global function
		SFunction::bindGOFunctions(vm);

		sqstd_register_iolib(vm);
		sqstd_register_mathlib(vm);
		sqstd_register_stringlib(vm);
		sqstd_register_systemlib(vm);
		sqrat_register_importlib(vm);
		sqstd_register_bloblib(vm);

		if (!SQ_SUCCEEDED(sqstd_dofile(vm, _SC(RakString("Multiplayer/Script/%s", fileName).C_String()), SQFalse, SQTrue)))
		//if (!SQ_SUCCEEDED(sqratbase_importPath(vm, _SC(RakString("Multiplayer/Script/%s", fileName).C_String()))))
		{
			core.GetChat()->AddLine(RakString("(Squirrel) No such file in directory or compile error in '%s'", fileName), zCOLOR(255, 0, 0, 255));
			isScriptLoaded = false;
		}
		else
			isScriptLoaded = true;

		sq_pop(vm, 1);

		OnRender();

		return isScriptLoaded;
	}
	else
		core.GetChat()->AddLine(RakString("(Squirrel) Cannot create virtual machine"), zCOLOR(255, 0, 0, 255));

	return false;
};

void CScript::OnRender()
{
	scriptVars->OnRender();
};