/* game_data_db.h */

#ifndef GAME_DATA_DB_H
#define GAME_DATA_DB_H

#pragma region godot_includes
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"
#pragma endregion godot_includes

#pragma region cm_includes
#include "../uuid.h"
#include "../vector_hashmap_pair.h"
#include "game_data_table.h"
#pragma endregion cm_includes

class GameDataDB
{
private:
	Vector<String> table_names;
	VectorHashMapPair<String, GameDataTable> tables;

public:
	bool has_table(String p_table_name) const;

	bool register_table(String p_table_name);
	bool unregister_table(String p_table_name);

	GameDataTable *get_table_const(String p_table_name) const;
	GameDataTable *get_table(String p_table_name);
	GameDataTable *create_table(String p_table_name);
	bool delete_table(String p_table_name);

	HashMap<String, GameDataTable *> get_tables_const(Vector<String> p_table_names) const;
	HashMap<String, GameDataTable *> get_tables(Vector<String> p_table_names);

	GameDataDB();
	GameDataDB(const GameDataDB &p_game_data_db);
	~GameDataDB();
};

#endif // GAME_DATA_DB_H
