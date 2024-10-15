/* game_data_db.cpp */

#include "game_data_db.h"

void GameDataDB::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_table_specification", "p_table_name"), &GameDataDB::get_table_specification);
	ClassDB::bind_method(D_METHOD("set_table_specification", "p_table_name", "p_table_specification"), &GameDataDB::set_table_specification);
	ClassDB::bind_method(D_METHOD("get_table_specifications", "p_table_names"), &GameDataDB::get_table_specifications);
	ClassDB::bind_method(D_METHOD("set_table_specifications", "p_table_specifications"), &GameDataDB::set_table_specifications);
	ClassDB::bind_method(D_METHOD("get_table", "p_table_name"), &GameDataDB::get_table);
	ClassDB::bind_method(D_METHOD("set_table", "p_table_name", "p_table"), &GameDataDB::set_table);
	ClassDB::bind_method(D_METHOD("get_tables", "p_table_names"), &GameDataDB::get_tables);
	ClassDB::bind_method(D_METHOD("set_tables", "p_tables"), &GameDataDB::set_tables);
}

GameDataDB::GameDataDB()
{
}

GameDataDB::GameDataDB(const GameDataDB &p_game_data_db)
	: table_specifications(p_game_data_db.table_specifications)
	, table_specifications_cache(p_game_data_db.table_specifications_cache)
	, tables(p_game_data_db.tables)
	, tables_cache(p_game_data_db.tables_cache)
{
}

GameDataDB::~GameDataDB()
{
	table_specifications.clear();
	table_specifications_cache.clear();
	tables.clear();
	tables_cache.clear();
}

TableSpecification GameDataDB::get_table_specification(String p_table_name) const
{
	if (!table_specifications_cache.has(p_table_name))
	{
		ERR_PRINT_ED("Table specification does not exist");
		return TableSpecification();
	}

	uint64_t table_specifications_index = table_specifications_cache.get(p_table_name);

	if (table_specifications_index >= table_specifications.size())
	{
		ERR_PRINT_ED("Table specification cache index error");
		return TableSpecification();
	}

	return table_specifications.get(table_specifications_index);
}

void GameDataDB::set_table_specification(String p_table_name, const TableSpecification &p_table_specification)
{
	if (!table_specifications_cache.has(p_table_name))
	{
		int64_t new_index = table_specifications.size();
		table_specifications.push_back(p_table_specification);
		table_specifications_cache.insert(p_table_name, new_index);
		return;
	}

	table_specifications.set(table_specifications_cache.get(p_table_name), p_table_specification);
}

HashMap<String, TableSpecification> GameDataDB::get_table_specifications(Vector<String> p_table_names) const
{
	HashMap<String, TableSpecification> r_table_specifications;
	if (!p_table_names.is_empty())
	{
		for (String table_name : p_table_names)
		{
			if (!table_specifications_cache.has(table_name))
			{
				ERR_PRINT_ED("Table specification does not exist");
			}

			r_table_specifications.insert(table_name, get_table_specification(table_name));
		}
	}
	else
	{
		for (TableSpecification table_specification : table_specifications)
		{
			r_table_specifications.insert(table_specification.get_name(), table_specification);
		}
	}

	return r_table_specifications;
}

void GameDataDB::set_table_specifications(HashMap<String, TableSpecification> p_table_specifications)
{
	for (KeyValue<String, TableSpecification> kv : p_table_specifications)
	{
		set_table_specification(kv.key, kv.value);
	}
}

GameDataTable GameDataDB::get_table(String p_table_name) const
{
	if (!tables_cache.has(p_table_name))
	{
		ERR_PRINT_ED("Table does not exist");
		return GameDataTable();
	}

	uint64_t tables_index = tables_cache.get(p_table_name);

	if (tables_index >= tables.size())
	{
		ERR_PRINT_ED("Tables cache index error");
		return GameDataTable();
	}

	return tables.get(tables_index);
}

void GameDataDB::set_table(String p_table_name, const GameDataTable &p_table)
{
	if (!tables_cache.has(p_table_name))
	{
		int64_t new_index = tables.size();
		tables.push_back(p_table);
		tables_cache.insert(p_table_name, new_index);
		return;
	}

	tables.set(tables_cache.get(p_table_name), p_table);
}

HashMap<String, GameDataTable> GameDataDB::get_tables(Vector<String> p_table_names) const
{
	HashMap<String, GameDataTable> r_tables;
	if (!p_table_names.is_empty())
	{
		for (String table_name : p_table_names)
		{
			if (!tables_cache.has(table_name))
			{
				ERR_PRINT_ED("Table does not exist");
			}

			r_tables.insert(table_name, get_table(table_name));
		}
	}
	else
	{
		for (GameDataTable table : tables)
		{
			r_tables.insert(table.get_table_specification().get_name(), table);
		}
	}

	return r_tables;
}

void GameDataDB::set_tables(HashMap<String, GameDataTable> p_tables)
{
	for (KeyValue<String, GameDataTable> kv : p_tables)
	{
		set_table(kv.key, kv.value);
	}
}
