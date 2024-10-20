/* game_data_table.cpp */

#include "core/object/object.h"

#include "game_data_db.h"
#include "game_data_manager.h"
#include "game_data_table.h"

GameDataEntry::GameDataEntry()
	: manager(nullptr)
	, parent(nullptr)
	, path("")
{
}

GameDataEntry::GameDataEntry(const GameDataEntry &p_game_data_entry)
	: manager(p_game_data_entry.manager)
	, parent(p_game_data_entry.parent)
	, path(p_game_data_entry.path)
	, data(p_game_data_entry.data)
{
}

GameDataEntry::GameDataEntry(GameDataManager *p_manager, GameDataTable *p_parent)
	: manager(p_manager)
	, parent(p_parent)
	, path("")
{
}

GameDataEntry::~GameDataEntry()
{
	manager = nullptr;
	parent = nullptr;

	data.~VectorHashMapPair();
}

GameDataEntry GameDataEntry::empty()
{
	GameDataEntry r_entry;

	r_entry.set_uuid(UUID::empty());

	return r_entry;
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

GameDataField *GameDataEntry::get_field_const(String p_field_name) const
{
	return data.get_one_const(p_field_name);
}

GameDataField *GameDataEntry::get_field(String p_field_name)
{
	return data.get_one(p_field_name);
}

GameDataField *GameDataEntry::create_field(String p_field_name)
{
	return data.create_one(p_field_name);
}

HashMap<String, GameDataField *> GameDataEntry::get_fields_const(Vector<String> p_field_names) const
{
	return data.get_const(p_field_names);
}

HashMap<String, GameDataField *> GameDataEntry::get_fields(Vector<String> p_field_names)
{
	return data.get(p_field_names);
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

void GameDataTable::set_table_specification(TableSpecification *p_table_specification)
{
	table_specification = p_table_specification;
}

GameDataDB *GameDataTable::get_parent() const
{
	return parent;
}

void GameDataTable::set_parent(GameDataDB *p_parent)
{
	parent = p_parent;
}

GameDataEntry *GameDataTable::get_entry_const(UUID p_uuid) const
{
	return entries.get_one_const(p_uuid);
}

GameDataEntry *GameDataTable::get_entry(UUID p_uuid)
{
	return entries.get_one(p_uuid);
}

GameDataEntry *GameDataTable::create_entry(UUID p_uuid)
{
	return entries.create_one(p_uuid);
}

HashMap<UUID, GameDataEntry *> GameDataTable::get_entries_const(Vector<UUID> p_uuids) const
{
	return entries.get_const(p_uuids);
}

HashMap<UUID, GameDataEntry *> GameDataTable::get_entries(Vector<UUID> p_uuids)
{
	return entries.get(p_uuids);
}
