/* register_types.cpp */

#include "register_types.h"

#include "cm_singleton_interfaces.h"
#include "core/config/engine.h"
#include "core/object/class_db.h"
#include "game_data_db.h"
#include "game_data_specifications.h"
#include "game_data_table.h"
#include "uuid.h"

void initialize_clockmakers_framework_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

	/* TRACKING */
	GDREGISTER_CLASS(UUID);
	GDREGISTER_CLASS(TrackedObject);

	/* GAME DATA SPECIFICATIONS */
	GDREGISTER_CLASS(FieldSpecification);
	GDREGISTER_CLASS(TableSpecification);

	/* GAME DATA CONTAINERS */
	GDREGISTER_CLASS(GameDataEntry);
	GDREGISTER_CLASS(GameDataTable);
	GDREGISTER_CLASS(GameDataDB);

	/* SINGLETONS CLASS REGISTRATION */
	GDREGISTER_CLASS(cm_singleton_interfaces::GameDataManager);

	/* SINGLETONS ENGINE REGISTRATION */
	Engine::get_singleton()->add_singleton(Engine::Singleton("GameDataManager", cm_singleton_interfaces::GameDataManager::get_singleton()));
}

void uninitialize_clockmakers_framework_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}
