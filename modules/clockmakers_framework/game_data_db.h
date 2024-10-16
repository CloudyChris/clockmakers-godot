/* game_data_db.h */

#ifndef GAME_DATA_DB_H
#define GAME_DATA_DB_H

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"
#include "game_data_table.h"
#include "uuid.h"

class GameDataDB : public Object
{
	GDCLASS(GameDataDB, Object);

private:
	Vector<TableSpecification> table_specifications;
	HashMap<String, uint64_t> table_specifications_cache;

	Vector<GameDataTable> tables;
	HashMap<String, uint64_t> tables_cache;

protected:
	static void _bind_methods();

public:
	TableSpecification get_table_specification(String p_table_name) const;
	void set_table_specification(String p_table_name, const TableSpecification &p_table_specification);

	HashMap<String, TableSpecification> get_table_specifications(Vector<String> p_table_names) const;
	void set_table_specifications(HashMap<String, TableSpecification> p_table_specifications);

	GameDataTable get_table(String p_table_name) const;
	void set_table(String p_table_name, const GameDataTable &p_table);

	HashMap<String, GameDataTable> get_tables(Vector<String> p_table_names) const;
	void set_tables(HashMap<String, GameDataTable> p_tables);

	GameDataDB();
	GameDataDB(const GameDataDB &p_game_data_db);
	~GameDataDB();
};

#endif // GAME_DATA_DB_H
