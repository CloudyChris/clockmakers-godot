/* game_data_manager.h */

#ifndef GAME_DATA_MANAGER_H
#define GAME_DATA_MANAGER_H

#pragma region godot_includes
#include "core/error/error_list.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"
#pragma endregion godot_includes

#pragma region cm_includes
#include "cm_enums.h"
#include "game_data_db.h"
#include "game_data_specifications.h"
#include "game_data_table.h"
#include "uuid.h"
#pragma endregion cm_includes

class GameDataManager
{
public:
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

public:
	// Load & Save Data
	static Error load_data_registry(cm_enums::CM_DataType p_data_type);
	static Error save_data_registry(cm_enums::CM_DataType p_data_type);
	static Error load_data_table(String p_table_name, cm_enums::CM_DataType p_data_type);
	static Error save_data_table(String p_table_name, cm_enums::CM_DataType p_data_type);
	static Error load_data(UUID p_uuid, String p_table_name, cm_enums::CM_DataType p_data_type);
	static Error save_data(UUID p_uuid, String p_table_name, cm_enums::CM_DataType p_data_type);
	static Error load_data_from_path(String p_path, String p_table_name, cm_enums::CM_DataType p_data_type);
	static Error save_data_to_path(String p_path, String p_table_name, cm_enums::CM_DataType p_data_type);

	// Data getters and setters
	// TODO

	/* NOTE ON THE FLOW OF DATA:
	 * 1) Any request will be issued to the GameDataManager (requiring parity with all its subdivisions (DB, Table, Entry) for its functionality)
	 * 2) Any request for data will be issued with the uuid and the name of the table, in addition to the CM_DataType
	 */
	// Registry serialization
	// JSON
	//---------------------------------
	// {
	// 	tables : {
	// 		table_name : {
	// 			table_specification: TableSpecification,
	// 			entries : {
	// 				uuid : path <String>,
	// 				.
	// 				.
	// 			}
	// 		},
	// 		.
	// 		.
	// 	},
	// 	uuids : {
	// 		uuid : {
	// 			data_type,
	// 			table_name,
	// 			path
	// 		},
	// 		.
	// 		.
	// 	}
	// }
	//---------------------------------
};

#endif // GAME_DATA_MANAGER_H
