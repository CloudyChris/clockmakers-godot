/* game_data_db.cpp */

#include "game_data_db.h"

GameDataDB::GameDataDB()
{
}

GameDataDB::GameDataDB(const GameDataDB &p_game_data_db)
	: table_names(p_game_data_db.table_names)
	, tables(p_game_data_db.tables)
{
}

GameDataDB::~GameDataDB()
{
	table_names.clear();
	tables.~VectorHashMapPair();
}

bool GameDataDB::has_table(String p_table_name) const
{
	return (table_names.find(p_table_name) >= 0);
}

bool GameDataDB::register_table(String p_table_name)
{
	if (table_names.find(p_table_name) >= 0)
	{
		return false;
	}

	table_names.push_back(p_table_name);
	return true;
}

bool GameDataDB::unregister_table(String p_table_name)
{
	if (int index = table_names.find(p_table_name) >= 0)
	{
		table_names.remove_at(index);
		return true;
	}

	return false;
}

GameDataTable *GameDataDB::get_table_const(String p_table_name) const
{
	return tables.get_one_const(p_table_name);
}

GameDataTable *GameDataDB::get_table(String p_table_name)
{
	return tables.get_one(p_table_name);
}

bool GameDataDB::delete_table(String p_table_name)
{
	return tables.delete_one(p_table_name);
}

HashMap<String, GameDataTable *> GameDataDB::get_tables_const(Vector<String> p_table_names) const
{
	return tables.get_const(p_table_names);
}

HashMap<String, GameDataTable *> GameDataDB::get_tables(Vector<String> p_table_names)
{
	return tables.get(p_table_names);
}
