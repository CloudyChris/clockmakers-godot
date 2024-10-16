/* game_data_manager.h */

#ifndef GAME_DATA_MANAGER_H
#define GAME_DATA_MANAGER_H

#include "core/error/error_list.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"
#include "game_data_db.h"
#include "game_data_specifications.h"
#include "game_data_table.h"
#include "uuid.h"

class GameDataManager
{
public:
	enum DataType
	{
		CM_DATA_TYPE_CORE,
		CM_DATA_TYPE_USER,
		CM_DATA_TYPE_TOOLS
	};

private:
	static PackedStringArray core_data_dir_path;
	static PackedStringArray core_data_registry_path;
	static PackedStringArray user_data_dir_path;
	static PackedStringArray user_data_registry_path;
	static PackedStringArray tools_data_dir_path;
	static PackedStringArray tools_data_registry_path;

	static GameDataDB core_game_data_db;
	static GameDataDB user_game_data_db;
	static GameDataDB tools_game_data_db;

private:
	static Error _load_data_registry(DataType p_data_type);
	static Error _save_data_registry(DataType p_data_type);
	static Error _load_data_table(String p_table_name, GameDataManager::DataType p_data_type);
	static Error _save_data_table(String p_table_name, DataType p_data_type);

public:
	static Error load_core_data_registry();
	static Error load_user_data_registry();
	static Error load_tools_data_registry();

	static Error save_core_data_registry();
	static Error save_user_data_registry();
	static Error save_tools_data_registry();

	static Error load_core_data_table(String p_table_name);
	static Error load_user_data_table(String p_table_name);
	static Error load_tools_data_table(String p_table_name);

	static Error save_core_data_table(String p_table_name);
	static Error save_user_data_table(String p_table_name);
	static Error save_tools_data_table(String p_table_name);
};

#endif // GAME_DATA_MANAGER_H
