/* register_types.cpp */

#include "register_types.h"

#include "core/object/class_db.h"
#include "game_data_db.h"
#include "game_data_table.h"
#include "uuid.h"

void initialize_clockmakers_framework_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

	GDREGISTER_CLASS(UUID);
	GDREGISTER_CLASS(TrackedObject);

	GDREGISTER_CLASS(FieldSpecification);
	GDREGISTER_CLASS(TableSpecification);
	GDREGISTER_CLASS(GameDataEntry);
	GDREGISTER_CLASS(GameDataTable);
	GDREGISTER_CLASS(GameDataDB);
}

void uninitialize_clockmakers_framework_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}
