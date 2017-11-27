#ifndef _SQMACRO_H_
#define _SQMACRO_H_

// Get params, with checking value
#define SQ_CHECK_PARAM_COUNT(vm, count) \
	int stack_size = sq_gettop(vm); \
if (stack_size <= count) \
{ \
	sq_error(vm, "(%s) wrong number of parameters, expecting %d params", __FUNCTION__, count); \
	return SQ_ERROR; \
} \

#define SQ_CHECK_PARAM_INT(vm, ref, index) \
	int ref; \
if (sq_gettype(vm, -stack_size + index + 1) == OT_INTEGER || sq_gettype(vm, -stack_size + index + 1) == OT_FLOAT) \
	sq_getinteger(vm, -stack_size + index + 1, &ref); \
else \
{ \
	sq_error(vm, "Error runtime: (%s) invalid argument at index %d, expecting 'int'", __FUNCTION__, index); \
	return SQ_ERROR; \
} \

#define SQ_CHECK_PARAM_BOOL(vm, ref, index) \
	SQBool ref; \
if (sq_gettype(vm, -stack_size + index + 1) == OT_BOOL || sq_gettype(vm, -stack_size + index + 1) == OT_INTEGER) \
	sq_getbool(vm, -stack_size + index + 1, &ref); \
else \
{ \
	sq_error(vm, "Error runtime: (%s) invalid argument at index %d, expecting 'bool'", __FUNCTION__, index); \
	return SQ_ERROR; \
} \

#define SQ_CHECK_PARAM_FLOAT(vm, ref, index) \
	float ref; \
if (sq_gettype(vm, -stack_size + index + 1) == OT_FLOAT || sq_gettype(vm, -stack_size + index + 1) == OT_INTEGER) \
	sq_getfloat(vm, -stack_size + index + 1, &ref); \
else \
{ \
	sq_error(vm, "Error runtime: (%s) invalid argument at index %d, expecting 'float'", __FUNCTION__, index); \
	return SQ_ERROR; \
} \

#define SQ_CHECK_PARAM_STRING(vm, ref, index) \
	const SQChar *ref; \
if (sq_gettype(vm, -stack_size + index + 1) == OT_STRING) \
	sq_getstring(vm, -stack_size + index + 1, &ref); \
else \
{ \
	sq_error(vm, "Error runtime: (%s) invalid argument at index %d, expecting 'string'", __FUNCTION__, index); \
	return SQ_ERROR; \
} \

#define SQ_CHECK_PARAM_TABLE(vm, ref, index) \
	HSQOBJECT ref; \
	sq_resetobject(&ref); \
if (sq_gettype(vm, -stack_size + index + 1) == OT_TABLE) \
{ \
	sq_getstackobj(vm, -stack_size + index + 1, &ref); \
	sq_addref(vm, &ref); \
} \
else \
{ \
	sq_error(vm, "Error runtime: (%s) invalid argument at index %d, expecting 'table'", __FUNCTION__, index); \
	return SQ_ERROR; \
} \

#define SQ_CHECK_PARAM_FUNC(vm, ref, index) \
	HSQOBJECT ref; \
	sq_resetobject(&ref); \
if (sq_gettype(vm, -stack_size + index + 1) == OT_CLOSURE) \
{ \
	sq_getstackobj(vm, -stack_size + index + 1, &ref); \
	sq_addref(vm, &ref); \
} \
else \
{ \
	sq_error(vm, "Error runtime: (%s) invalid argument at index %d, expecting 'function'", __FUNCTION__, index); \
	return SQ_ERROR; \
} \

// Get params, with default value
#define SQ_PARAM_INT(vm, ref, value, index) \
	int ref = value; \
if (sq_gettype(vm, -stack_size + index + 1) == OT_INTEGER) \
	sq_getinteger(vm, -stack_size + index + 1, &ref); \
	
#define SQ_PARAM_BOOL(vm, ref, value, index) \
	SQBool ref = value; \
if (sq_gettype(vm, -stack_size + index + 1) == OT_BOOL || sq_gettype(vm, -stack_size + index + 1) == OT_INTEGER) \
	sq_getbool(vm, -stack_size + index + 1, &ref); \

#define SQ_PARAM_FLOAT(vm, ref, value, index) \
	float ref = value; \
if (sq_gettype(vm, -stack_size + index + 1) == OT_FLOAT) \
	sq_getfloat(vm, -stack_size + index + 1, &ref); \

#define SQ_PARAM_STRING(vm, ref, value, index) \
	const SQChar *ref = value; \
if (sq_gettype(vm, -stack_size + index + 1) == OT_STRING) \
	sq_getstring(vm, -stack_size + index + 1, &ref); \

#define SQ_PARAM_ANY(vm, ref, index) \
	HSQOBJECT ref; \
	sq_resetobject(&ref);  \
	sq_getstackobj(vm, -stack_size + index + 1, &ref); \
	sq_addref(vm, &ref); \

// Register globals
#define SQ_REGISTER_GLOBAL_FUNC(vm, name, func) \
{ \
	sq_pushroottable(vm); \
	sq_pushstring(vm, name, -1); \
	sq_newclosure(vm, func, NULL); \
	sq_newslot(vm, -3, SQTrue); \
	sq_pop(vm, 1); \
} \

#define SQ_REGISTER_GLOBAL_CONST_INT(vm, name, value) \
{ \
	sq_pushconsttable(vm); \
	sq_pushstring(vm, name, -1); \
	sq_pushinteger(vm, value); \
	sq_newslot(vm, -3, SQTrue); \
	sq_pop(vm, 1); \
} \

#define SQ_REGISTER_GLOBAL_CONST_BOOL(vm, name, value) \
{ \
	sq_pushconsttable(vm); \
	sq_pushstring(vm, name, -1); \
	sq_pushbool(vm, value); \
	sq_newslot(vm, -3, SQTrue); \
	sq_pop(vm, 1); \
} \

#define SQ_REGISTER_GLOBAL_CONST_FLOAT(vm, name, value) \
{ \
	sq_pushconsttable(vm); \
	sq_pushstring(vm, name, -1); \
	sq_pushfloat(vm, value); \
	sq_newslot(vm, -3, SQTrue); \
	sq_pop(vm, 1); \
} \

#define SQ_REGISTER_GLOBAL_CONST_STRING(vm, name, value) \
{ \
	sq_pushconsttable(vm); \
	sq_pushstring(vm, name, -1); \
	sq_pushstring(vm, value, -1); \
	sq_newslot(vm, -3, SQTrue); \
	sq_pop(vm, 1); \
} \

// Register callback
#define SQ_FUNCTION_BEGIN(vm, name) \
	SQInteger topStackSize = sq_gettop(vm); \
	sq_pushroottable(vm); \
	sq_pushstring(vm, _SC(name), -1); \
if (SQ_SUCCEEDED(sq_get(vm, -2))) \
	sq_pushroottable(vm); \

#define SQ_FUNCTION_END(vm) \
sq_settop(vm, topStackSize); \

#define SQ_FUNCTION_CALL(vm, arg_count) sq_call(vm, arg_count + 1, SQFalse, SQTrue);
#define SQ_FUNCTION_CALL_RETURN_INT(vm, arg_count, returnVar) \
if (SQ_SUCCEEDED(sq_call(vm, arg_count + 1, SQTrue, SQTrue))) \
	if (SQ_FAILED(sq_getinteger(vm, -1, &returnVar))) \
		returnVar = 0; \

// Register table
#define SQ_TABLE_SET_INT(vm, index, value) \
{ \
	sq_pushstring(vm, index, -1); \
	sq_pushinteger(vm, value); \
	sq_newslot(vm, -3, SQFalse); \
} \

#define SQ_TABLE_SET_FLOAT(vm, index, value) \
{ \
	sq_pushstring(vm, index, -1); \
	sq_pushfloat(vm, value); \
	sq_newslot(vm, -3, SQFalse); \
} \

#define SQ_TABLE_SET_STRING(vm, index, value) \
{ \
	sq_pushstring(vm, index, -1); \
	sq_pushstring(vm, value, -1); \
	sq_newslot(vm, -3, SQFalse); \
} \

// Register array
#define SQ_ARRAY_INT(vm, value) \
{ \
	sq_pushinteger(vm, value); \
	sq_arrayappend(vm, -2); \
} \

#define SQ_ARRAY_FLOAT(vm, value) \
{ \
	sq_pushfloat(vm, value); \
	sq_arrayappend(vm, -2); \
} \

#define SQ_ARRAY_STRING(vm, value) \
{ \
	sq_pushstring(vm, value, -1); \
	sq_arrayappend(vm, -2); \
} \

#endif //_SQMACRO_H_
