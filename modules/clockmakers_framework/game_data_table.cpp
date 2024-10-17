/* game_data_table.cpp */

#include "game_data_table.h"
#include "core/object/object.h"

GameDataEntry::GameDataEntry()
	: parent(nullptr)
{
}

GameDataEntry::GameDataEntry(const GameDataEntry &p_game_data_entry)
	: parent(p_game_data_entry.parent)
	, data(p_game_data_entry.data)
{
}

GameDataEntry::GameDataEntry(GameDataTable *p_parent)
	: parent(p_parent)
{
}

GameDataEntry::~GameDataEntry()
{
	parent = nullptr;

	data.~VectorHashMapPair();
}

GameDataTable *GameDataEntry::get_parent() const
{
	return parent;
}

void GameDataEntry::set_parent(GameDataTable *p_parent)
{
	parent = p_parent;
}

String GameDataEntry::get_path() const
{
	return path;
}

void GameDataEntry::set_path(String p_path)
{
	path = p_path;
}

Variant GameDataEntry::get_data(String p_field_name) const
{
	if (!parent->get_table_specification()->has_field(p_field_name))
	{
		return Variant();
	}

	return data.get_value(p_field_name);
}

void GameDataEntry::set_data(String p_field_name, Variant p_data)
{
	if (!parent->get_table_specification()->has_field(p_field_name))
	{
		return;
	}

	data.set_value(p_field_name, p_data);
}

GameDataTable::GameDataTable()
	: table_specification(nullptr)
	, parent(nullptr)
{
}

GameDataTable::GameDataTable(const GameDataTable &p_game_data_table)
	: table_specification(p_game_data_table.table_specification)
	, parent(p_game_data_table.parent)
	, entries(p_game_data_table.entries)
{
}

GameDataTable::GameDataTable(GameDataDB *p_parent, TableSpecification *p_table_specificaiton)
	: table_specification(p_table_specificaiton)
	, parent(p_parent)
{
}

GameDataTable::~GameDataTable()
{
	table_specification = nullptr;
	parent = nullptr;
	entries.~VectorHashMapPair();
}

TableSpecification *GameDataTable::get_table_specification() const
{
	return table_specification;
}

void GameDataTable::set_table_specification(const TableSpecification &p_table_specification)
{
	table_specification->copy(p_table_specification);
}

GameDataDB *GameDataTable::get_parent() const
{
	return parent;
}

void GameDataTable::set_parent(GameDataDB *p_parent)
{
	parent = p_parent;
}

GameDataEntry GameDataTable::get_entry(UUID p_uuid) const
{
	return entries.get_value(p_uuid);
}

void GameDataTable::set_entry(UUID p_uuid, const GameDataEntry &p_game_data_entry)
{
	entries.set_value(p_uuid, p_game_data_entry);
}

Variant GameDataTable::get_entry_field(UUID p_uuid, String p_field_name) const
{
	if (!table_specification->has_field(p_field_name))
	{
		ERR_PRINT_ED("Field not defined in table specification");
		return Variant();
	}

	return entries.get_value(p_uuid).get_data(p_field_name);
}

void GameDataTable::set_entry_field(UUID p_uuid, String p_field_name, Variant p_data)
{
	if (!table_specification->has_field(p_field_name))
	{
		ERR_PRINT_ED("Field not defined in table specification");
		return;
	}

	entries.get_value_m(p_uuid).set_data(p_field_name, p_data);
}

HashMap<UUID, GameDataEntry> GameDataTable::get_entries(Vector<UUID> p_uuids) const
{
	return entries.get_values(p_uuids);
}

void GameDataTable::set_entries(HashMap<UUID, GameDataEntry> p_game_data_entries)
{
	entries.set_values(p_game_data_entries);
}
