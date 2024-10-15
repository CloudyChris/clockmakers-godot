/* game_data_table.h */

#ifndef GAME_DATA_TABLE_H
#define GAME_DATA_TABLE_H

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"
#include "uuid.h"

class GameDataTable;

class FieldSpecification : public Object
{
	GDCLASS(FieldSpecification, Object);

private:
	String name;
	PropertyInfo info;

protected:
	static void _bind_methods();

public:
	String get_name() const;
	void set_name(String p_name);

	PropertyInfo get_info() const;
	Dictionary get_info_bind() const;
	void set_info(const PropertyInfo &p_info);
	void set_info_bind(Dictionary p_info);

	FieldSpecification();
	FieldSpecification(const FieldSpecification &p_field_specification);
	~FieldSpecification();
};

class TableSpecification : public Object
{
	GDCLASS(TableSpecification, Object);

private:
	String name;
	Vector<FieldSpecification> fields;
	HashMap<String, uint64_t> fields_cache;

protected:
	static void _bind_methods();

public:
	String get_name() const;
	void set_name(String p_name);

	bool has_field(String p_field_name) const;
	FieldSpecification get_field_specification(String p_field_name) const;
	void set_field_specification(String p_field_name, FieldSpecification p_field_specification);

	void copy(const TableSpecification &p_table_specification);

	TableSpecification();
	TableSpecification(const TableSpecification &p_game_data_table);
	~TableSpecification();
};

class GameDataEntry : public TrackedObject
{
	GDCLASS(GameDataEntry, TrackedObject);

private:
	TableSpecification *table_specification;
	GameDataTable *parent;
	Vector<Variant> data;
	HashMap<String, int> data_cache;

protected:
	static void _bind_methods();

public:
	TableSpecification *get_table_specification() const;
	void set_table_specification(const TableSpecification &p_table_specification);

	GameDataTable &get_parent() const;
	void set_parent(const GameDataTable &p_parent);

	Variant get_data(String p_field_name) const;
	void set_data(String p_field_name, Variant p_data);

	GameDataEntry();
	GameDataEntry(const GameDataEntry &p_game_data_entry);
	GameDataEntry(GameDataTable *p_parent, TableSpecification *p_table_specificaiton);
	~GameDataEntry();
};

class GameDataTable : public TrackedObject
{
	GDCLASS(GameDataTable, TrackedObject);

private:
	TableSpecification *table_specification;

	Vector<GameDataEntry> entries;
	HashMap<UUID, int> entries_cache;

protected:
	static void _bind_methods();

public:
	TableSpecification get_table_specification() const;
	void set_table_specification(const TableSpecification &p_table_specificaiton);

	GameDataEntry get_entry(UUID p_uuid) const;
	void set_entry(UUID p_uuid, const GameDataEntry &p_game_data_entry);

	Variant get_entry_field(UUID p_uuid, String p_field_name) const;
	void set_entry_field(UUID p_uuid, String p_field_name, Variant p_data);

	HashMap<UUID, GameDataEntry> get_entries(Vector<UUID> p_uuids) const;
	void set_entries(HashMap<UUID, GameDataEntry> p_game_data_entries);

	GameDataTable();
	GameDataTable(const GameDataTable &p_game_data_table);
	~GameDataTable();
};
#endif
