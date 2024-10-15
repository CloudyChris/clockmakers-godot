/* game_data_table.cpp */

#include "game_data_table.h"
#include "core/object/object.h"

void FieldSpecification::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_name"), &FieldSpecification::get_name);
	ClassDB::bind_method(D_METHOD("set_name", "p_name"), &FieldSpecification::set_name);
	ClassDB::bind_method(D_METHOD("get_info"), &FieldSpecification::get_info_bind);
	ClassDB::bind_method(D_METHOD("set_info", "p_info"), &FieldSpecification::set_info_bind);

	ADD_GROUP("Field Specification", "FieldSpecificationGroup_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "FieldSpecificationGroup_name", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_name", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "FieldSpecificationGroup_info", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_info", "get_info");
}

FieldSpecification::FieldSpecification()
{
}

FieldSpecification::FieldSpecification(const FieldSpecification &p_field_specification)
	: name(p_field_specification.name)
	, info(p_field_specification.info)
{
}

FieldSpecification::~FieldSpecification()
{
}

String FieldSpecification::get_name() const
{
	return name;
}

void FieldSpecification::set_name(String p_name)
{
	name = p_name;
}

PropertyInfo FieldSpecification::get_info() const
{
	return info;
}

Dictionary FieldSpecification::get_info_bind() const
{
	return info;
}

void FieldSpecification::set_info(const PropertyInfo &p_info)
{
	info = p_info;
}

void FieldSpecification::set_info_bind(Dictionary p_info)
{
	info = PropertyInfo::from_dict(p_info);
}

void TableSpecification::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("has_field", "p_field_name"), &TableSpecification::has_field);
	ClassDB::bind_method(D_METHOD("get_field_specification", "p_field_name", "p_check"), &TableSpecification::get_field_specification);
	ClassDB::bind_method(D_METHOD("set_field_specification", "p_field_name", "p_field_specification", "p_check"), &TableSpecification::set_field_specification);
}

TableSpecification::TableSpecification()
{
}

TableSpecification::TableSpecification(const TableSpecification &p_table_specification)
	: fields(p_table_specification.fields)
	, fields_cache(p_table_specification.fields_cache)
{
}

TableSpecification::~TableSpecification()
{
	fields.clear();
	fields_cache.clear();
}

bool TableSpecification::has_field(String p_field_name) const
{
	return fields_cache.has(p_field_name);
}

FieldSpecification TableSpecification::get_field_specification(String p_field_name) const
{
	if (!fields_cache.has(p_field_name))
	{
		ERR_PRINT_ED("Field does not exist");
		return FieldSpecification();
	}

	uint64_t fields_index = fields_cache.get(p_field_name);

	if (fields_index >= fields.size())
	{
		ERR_PRINT_ED("Field cache index error");
		return FieldSpecification();
	}

	return fields.get(fields_index);
}

FieldSpecification &TableSpecification::get_field_specification_m(String p_field_name)
{
	if (!fields_cache.has(p_field_name))
	{
		ERR_PRINT_ED("Field does not exist");
		return EMPTY_FIELD_SPECIFICATION;
	}

	uint64_t fields_index = fields_cache.get(p_field_name);

	if (fields_index >= fields.size())
	{
		ERR_PRINT_ED("Field cache index error");
		return EMPTY_FIELD_SPECIFICATION;
	}

	return fields.get_m(fields_index);
}

void TableSpecification::set_field_specification(String p_field_name, FieldSpecification p_field_specification)
{
	if (!fields_cache.has(p_field_name))
	{
		int64_t new_index = fields.size();
		fields.push_back(p_field_specification);
		fields_cache.insert(p_field_name, new_index);
		return;
	}

	fields.set(fields_cache.get(p_field_name), p_field_specification);
}

void TableSpecification::copy(const TableSpecification &p_table_specification)
{
	fields = p_table_specification.fields;
	fields_cache = p_table_specification.fields_cache;
}

void GameDataEntry::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_table_specification"), &GameDataEntry::get_table_specification);
	ClassDB::bind_method(D_METHOD("set_table_specification", "p_table_specification"), &GameDataEntry::set_table_specification);
	ClassDB::bind_method(D_METHOD("get_parent"), &GameDataEntry::get_parent);
	ClassDB::bind_method(D_METHOD("set_parent", "p_parent"), &GameDataEntry::set_parent);
	ClassDB::bind_method(D_METHOD("get_data", "p_field_name"), &GameDataEntry::get_data);
	ClassDB::bind_method(D_METHOD("set_data", "p_field_name", "p_data"), &GameDataEntry::set_data);
}

GameDataEntry::GameDataEntry()
	: table_specification(nullptr)
	, parent(nullptr)
{
}

GameDataEntry::GameDataEntry(const GameDataEntry &p_game_data_entry)
	: table_specification(p_game_data_entry.table_specification)
	, parent(p_game_data_entry.parent)
	, data(p_game_data_entry.data)
	, data_cache(p_game_data_entry.data_cache)
{
}

GameDataEntry::GameDataEntry(GameDataTable *p_parent, TableSpecification *p_table_specification)
	: table_specification(p_table_specification)
	, parent(p_parent)
{
}

GameDataEntry::~GameDataEntry()
{
	table_specification = nullptr;
	parent = nullptr;

	data.clear();
	data_cache.clear();
}

TableSpecification &GameDataEntry::get_table_specification() const
{
	return *table_specification;
}

TableSpecification &GameDataEntry::get_table_specification_m()
{
	return *table_specification;
}

void GameDataEntry::set_table_specification(const TableSpecification &p_table_specification)
{
	table_specification->copy(p_table_specification);
}

GameDataTable &GameDataEntry::get_parent() const
{
	return *parent;
}

GameDataTable &GameDataEntry::get_parent_m()
{
	return *parent;
}

Variant GameDataEntry::get_data(String p_field_name) const
{
	if (!table_specification->has_field(p_field_name))
	{
		return Variant();
	}

	if (!data_cache.has(p_field_name))
	{
		return Variant();
	}

	uint64_t data_index = data_cache.get(p_field_name);

	if (data_index >= data.size())
	{
		return Variant();
	}

	return data.get(data_index);
}

void GameDataEntry::set_data(String p_field_name, Variant p_data)
{
	if (!table_specification->has_field(p_field_name))
	{
		return;
	}

	if (!data_cache.has(p_field_name))
	{
		int64_t new_index = data.size();
		data.push_back(p_data);
		data_cache.insert(p_field_name, new_index);
		return;
	}

	data.set(data_cache.get(p_field_name), p_data);
}

void GameDataTable::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_table_specification"), &GameDataTable::get_table_specification);
	ClassDB::bind_method(D_METHOD("set_table_specification", "p_table_specification"), &GameDataTable::set_table_specification);
	ClassDB::bind_method(D_METHOD("get_entry", "p_uuid"), &GameDataTable::get_entry);
	ClassDB::bind_method(D_METHOD("set_entry", "p_uuid", "p_game_data_entry"), &GameDataTable::set_entry);
	ClassDB::bind_method(D_METHOD("get_entry_field", "p_uuid", "p_field_name"), &GameDataTable::get_entry_field);
	ClassDB::bind_method(D_METHOD("set_entry_field", "p_uuid", "p_field_name", "p_data"), &GameDataTable::set_entry_field);
	ClassDB::bind_method(D_METHOD("get_entries", "p_uuids"), &GameDataTable::get_entries);
	ClassDB::bind_method(D_METHOD("set_entries", "p_game_data_entries"), &GameDataTable::set_entries);
}

GameDataTable::GameDataTable()
{
}

GameDataTable::GameDataTable(const GameDataTable &p_game_data_table)
	: table_specification(p_game_data_table.table_specification)
	, entries(p_game_data_table.entries)
	, entries_cache(p_game_data_table.entries_cache)
{
}

GameDataTable::~GameDataTable()
{
	table_specification.~TableSpecification();
	entries.clear();
	entries_cache.clear();
}

TableSpecification GameDataTable::get_table_specification() const
{
	return table_specification;
}

TableSpecification &GameDataTable::get_table_specification_m()
{
	return table_specification;
}

void GameDataTable::set_table_specification(const TableSpecification &p_table_specification)
{
	table_specification.copy(p_table_specification);
}

GameDataEntry GameDataTable::get_entry(UUID p_uuid) const
{
	if (!entries_cache.has(p_uuid))
	{
		ERR_PRINT_ED("Entry does not exist");
		return GameDataEntry();
	}

	uint64_t entries_index = entries_cache.get(p_uuid);

	if (entries_index >= entries.size())
	{
		ERR_PRINT_ED("Entry cache index error");
		return GameDataEntry();
	}

	return entries.get(entries_index);
}

GameDataEntry &GameDataTable::get_entry_m(UUID p_uuid)
{
	if (!entries_cache.has(p_uuid))
	{
		ERR_PRINT_ED("Entry does not exist");
		return EMPTY_GAME_DATA_ENTRY;
	}

	uint64_t entries_index = entries_cache.get(p_uuid);

	if (entries_index >= entries.size())
	{
		ERR_PRINT_ED("Entry cache index error");
		return EMPTY_GAME_DATA_ENTRY;
	}

	return entries.get_m(entries_index);
}

void GameDataTable::set_entry(UUID p_uuid, const GameDataEntry &p_game_data_entry)
{
	if (!entries_cache.has(p_uuid))
	{
		int64_t new_index = entries.size();
		entries.push_back(p_game_data_entry);
		entries_cache.insert(p_uuid, new_index);
		return;
	}

	entries.set(entries_cache.get(p_uuid), p_game_data_entry);
}

Variant GameDataTable::get_entry_field(UUID p_uuid, String p_field_name) const
{
	if (!table_specification.has_field(p_field_name))
	{
		ERR_PRINT_ED("Field not defined in table specification");
		return Variant();
	}

	if (!entries_cache.has(p_uuid))
	{
		ERR_PRINT_ED("Entry does not exist");
		return Variant();
	}

	uint64_t entries_index = entries_cache.get(p_uuid);

	if (entries_index >= entries.size())
	{
		ERR_PRINT_ED("Entry cache index error");
		return Variant();
	}

	return entries.get(entries_index).get_data(p_field_name);
}
