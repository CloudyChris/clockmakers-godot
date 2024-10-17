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
	table_specifications.~VectorHashMapPair();
	tables.~VectorHashMapPair();
}

bool GameDataDB::has_table(String p_table_name) const
{
	return table_specifications.has(p_table_name);
}

TableSpecification *GameDataDB::get_table_specification(String p_table_name) const
{
	return table_specifications.get_value(p_table_name);
}

void GameDataDB::set_table_specification(String p_table_name, TableSpecification *p_table_specification)
{
	table_specifications.set_value(p_table_name, p_table_specification);
}

HashMap<String, TableSpecification *> GameDataDB::get_table_specifications(Vector<String> p_table_names) const
{
	return table_specifications.get_values(p_table_names);
}

void GameDataDB::set_table_specifications(HashMap<String, TableSpecification *> p_table_specifications)
{
	table_specifications.set_values(p_table_specifications);
}

GameDataTable GameDataDB::get_table(String p_table_name) const
{
	return tables.get_value(p_table_name);
}

void GameDataDB::set_table(String p_table_name, const GameDataTable &p_table)
{
	tables.set_value(p_table_name, p_table);
}

HashMap<String, GameDataTable> GameDataDB::get_tables(Vector<String> p_table_names) const
{
	return tables.get_values(p_table_names);
}

void GameDataDB::set_tables(HashMap<String, GameDataTable> p_tables)
{
	tables.set_values(p_tables);
}
