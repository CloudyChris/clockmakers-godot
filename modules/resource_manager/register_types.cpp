/* register_types.cpp */

#include "register_types.h"

#include "core/object/class_db.h"
#include "game_resource.h"
#include "tracked_resource.h"

void initialize_resource_manager_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

	GDREGISTER_CLASS(TrackedResource);
	GDREGISTER_CLASS(GameResource);
}

void uninitialize_resource_manager_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}
