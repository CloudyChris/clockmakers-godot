/* register_types.cpp */

#include "register_types.h"

#include "uuid.h"

#include "core/error/error_macros.h"

void initialize_uuid_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
	GDREGISTER_CLASS(UUID);
}

void uninitialize_uuid_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}
