/* register_types.cpp */

#include "register_types.h"

#include "core/object/class_db.h"
#include "uuid.h"

void initialize_clockmakers_framework_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

	GDREGISTER_CLASS(UUID);
}

void uninitialize_clockmakers_framework_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}
