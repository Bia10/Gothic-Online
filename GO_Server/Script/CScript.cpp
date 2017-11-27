#include "../stdafx.h"

CScript::CScript()
{

};

CScript::~CScript()
{

};

void CScript::PrintFunction(HSQUIRRELVM vm, const SQChar *s, ...)
{
	va_list vl;
	va_start(vl, s);
	vfprintf(stdout, s, vl);
	printf("\n");
	va_end(vl);
};

void CScript::PrintErrors(HSQUIRRELVM vm, const SQChar *s, ...)
{
	va_list vl;
	va_start(vl, s);
	vfprintf(stderr, s, vl);
	printf("\n");
	va_end(vl);
};

SQInteger CScript::RuntimeErrors(HSQUIRRELVM vm)
{
	const SQChar *errorMessage = NULL;
	if (sq_gettop(vm) >= 1)
	{
		if (SQ_SUCCEEDED(sq_getstring(vm, 2, &errorMessage)))
			printf("[Squirrel] Error runtime: %s\n", errorMessage);

		SQStackInfos stackInfo;
		SQInteger stackDepth = 1;

		printf("[Squirrel] Stack Dump:\n");
		while (SQ_SUCCEEDED(sq_stackinfos(vm, stackDepth, &stackInfo)))
		{
			const SQChar *func_name = (stackInfo.funcname) ?
				stackInfo.funcname : "unknown_function";
			const SQChar *source_file = (stackInfo.source) ?
				stackInfo.source : "unknown_source_file";

			printf("[%d]: In function '%s()' %s line [%d]\n", stackDepth, func_name, source_file, stackInfo.line);
			++stackDepth;
		}
	}

	return 0;
};

void CScript::CompileErrors(HSQUIRRELVM vm, const SQChar* description, const SQChar* file, SQInteger line, SQInteger column)
{
	printf("[Squirrel] Error syntax: '%s' (Ln: %d Col: %d): %s\n", file, line, column, description);
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

		// Register global function
		SVaraiable::bindGOVaraiable(vm);
		SFunction::bindGOFunctions(vm);

		sqstd_register_iolib(vm);
		sqstd_register_mathlib(vm);
		sqstd_register_stringlib(vm);
		sqstd_register_systemlib(vm);
		sqrat_register_importlib(vm);
		sqstd_register_bloblib(vm);

		if (SQ_SUCCEEDED(sqstd_dofile(vm, _SC(RakString("server-scripts/%s", fileName).C_String()), SQFalse, SQTrue)))
		{
			sq_pop(vm, 1);
			SCallback::onInit();

			return true;
		}
		else
		{
			sq_pop(vm, 1);
			printf("[Squirrel] Cannot load scripts. File '%s' not found.\n", fileName);

			return false;
		}
	}
	else
		printf("[Squirrel] Cannot create virtual machine.\n");

	return false;
};

void CScript::OnTick()
{
	//Execute callback
	SCallback::onTick();
	// Timers
	timer.Pulse();
};