/* game_data_table.h */

#ifndef GAME_DATA_TABLE_H
#define GAME_DATA_TABLE_H

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"
#include "game_data_specifications.h"
#include "uuid.h"
#include "vector_hashmap_pair.h"

class GameDataDB;

class GameDataEntry : public Tracked
{
private:
	GameDataTable *parent;

	String path;
	VectorHashMapPair<String, Variant> data;

public:
	GameDataTable *get_parent() const;
	void set_parent(GameDataTable *p_parent);

	String get_path() const;
	void set_path(String p_path);

	Variant get_data(String p_field_name) const;
	void set_data(String p_field_name, Variant p_data);

	GameDataEntry();
	GameDataEntry(const GameDataEntry &p_game_data_entry);
	GameDataEntry(GameDataTable *p_parent);
	~GameDataEntry();
};

class GameDataTable
{
private:
	TableSpecification *table_specification;
	GameDataDB *parent;

	VectorHashMapPair<UUID, GameDataEntry> entries;

public:
	TableSpecification *get_table_specification() const;
	void set_table_specification(const TableSpecification &p_table_specificaiton);

	GameDataDB *get_parent() const;
	void set_parent(GameDataDB *p_parent);

	GameDataEntry get_entry(UUID p_uuid) const;
	void set_entry(UUID p_uuid, const GameDataEntry &p_game_data_entry);

	String get_entry_path(UUID p_uuid) const;
	void set_entry_path(UUID p_uuid, String p_path);

	Variant get_entry_field(UUID p_uuid, String p_field_name) const;
	void set_entry_field(UUID p_uuid, String p_field_name, Variant p_data);

	HashMap<UUID, GameDataEntry> get_entries(Vector<UUID> p_uuids) const;
	void set_entries(HashMap<UUID, GameDataEntry> p_game_data_entries);

	GameDataTable();
	GameDataTable(const GameDataTable &p_game_data_table);
	GameDataTable(GameDataDB *p_parent, TableSpecification *p_table_specification);
	~GameDataTable();
};

#endif // GAME_DATA_TABLE_H
