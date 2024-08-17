/* register_types.cpp */

#include "register_types.h"

#include "core/object/class_db.h"
#include "resource_db.h"

void initialize_resource_manager_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

	GDREGISTER_CLASS(TrackedResource);
	GDREGISTER_CLASS(FieldData);
	GDREGISTER_CLASS(GameResourceInterface);
	GDREGISTER_CLASS(GameResource);
	GDREGISTER_CLASS(ResourceDB);
}

void uninitialize_resource_manager_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}
