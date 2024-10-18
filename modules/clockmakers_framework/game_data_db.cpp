/* game_data_db.cpp */

#include "game_data_db.h"

GameDataDB::GameDataDB()
{
}

GameDataDB::GameDataDB(const GameDataDB &p_game_data_db)
	: table_specifications(p_game_data_db.table_specifications)
	, tables(p_game_data_db.tables)
{
}

GameDataDB::~GameDataDB()
{
	table_specifications.clear();
	tables.~VectorHashMapPair();
}

bool GameDataDB::has_table(String p_table_name) const
{
	return table_specifications.has(p_table_name);
}

TableSpecification *GameDataDB::get_table_specification(String p_table_name) const
{
	if (!table_specifications.has(p_table_name))
	{
		ERR_PRINT_ED("Table specification does not exist");
		return nullptr;
	}

	return table_specifications.get(p_table_name);
}

void GameDataDB::set_table_specification(String p_table_name, TableSpecification *p_table_specification)
{
	if (!table_specifications.has(p_table_name))
	{
		return;
	}

	table_specifications.get(p_table_name) = p_table_specification;
}

HashMap<String, TableSpecification *> GameDataDB::get_table_specifications(Vector<String> p_table_names) const
{
	HashMap<String, TableSpecification *> r_table_specifications;

	if (!p_table_names.is_empty())
	{
		for (String table_name : p_table_names)
		{
			TableSpecification *l_ts_ptr;
			if (!table_specifications.has(table_name))
			{
				l_ts_ptr = nullptr;
			}
			else
			{
				l_ts_ptr = table_specifications.get(table_name);
			}

			r_table_specifications.insert(table_name, l_ts_ptr);
		}

		return r_table_specifications;
	}

	return table_specifications;
}

void GameDataDB::set_table_specifications(HashMap<String, TableSpecification *> p_table_specifications)
{
	for (KeyValue<String, TableSpecification *> kv : p_table_specifications)
	{
		table_specifications.insert(kv.key, kv.value);
	}
}

GameDataTable *GameDataDB::get_table_const(String p_table_name) const
{
	return tables.get_pointer_const(p_table_name);
}

GameDataTable *GameDataDB::get_table(String p_table_name)
{
	return tables.get_pointer(p_table_name);
}

HashMap<String, GameDataTable *> GameDataDB::get_tables_const(Vector<String> p_table_names) const
{
	return tables.get_pointers_const(p_table_names);
}

HashMap<String, GameDataTable *> GameDataDB::get_tables(Vector<String> p_table_names)
{
	return tables.get_pointers(p_table_names);
}
