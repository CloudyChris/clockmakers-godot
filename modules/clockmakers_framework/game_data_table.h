/* game_data_table.h */

#ifndef GAME_DATA_TABLE_H
#define GAME_DATA_TABLE_H

#pragma region godot_includes
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"
#pragma endregion godot_includes

#pragma region cm_includes
#include "cm_enums.h"
#include "game_data_specifications.h"
#include "uuid.h"
#include "vector_hashmap_pair.h"
#pragma endregion cm_includes

class GameDataDB;
class GameDataEntry;
class GameDataTable;
class GameDataManager;

struct GameDataField
{
	bool is_reference;
	UUID ref_uuid;
	String ref_table_name;
	cm_enums::CM_DataType ref_type;

	String path;

	Variant data;
};

class GameDataEntry : public Tracked
{
private:
	GameDataManager *manager;
	GameDataTable *parent;

	String path;
	VectorHashMapPair<String, GameDataField> data;

public:
	static GameDataEntry empty();

	GameDataManager *get_manager() const;
	void set_manager(GameDataManager *p_manager);

	GameDataTable *get_parent() const;
	void set_parent(GameDataTable *p_parent);

	String get_path() const;
	void set_path(String p_path);

	GameDataField *get_field_const(String p_field_name) const;
	GameDataField *get_field(String p_field_name);
	GameDataField *create_field(String p_field_name);

	HashMap<String, GameDataField *> get_fields_const(Vector<String> p_field_names) const;
	HashMap<String, GameDataField *> get_fields(Vector<String> p_field_names);

	GameDataEntry();
	GameDataEntry(const GameDataEntry &p_game_data_entry);
	GameDataEntry(GameDataManager *p_manager, GameDataTable *p_parent);
	~GameDataEntry();
};

class GameDataTable
{
private:
	TableSpecification *table_specification;
	GameDataManager *manager;
	GameDataDB *parent;

	VectorHashMapPair<UUID, GameDataEntry> entries;

public:
	TableSpecification *get_table_specification() const;
	void set_table_specification(const TableSpecification &p_table_specificaiton);

	GameDataManager *get_manager() const;
	void set_manager(GameDataManager *p_manager);

	GameDataDB *get_parent() const;
	void set_parent(GameDataDB *p_parent);

	GameDataEntry *get_entry_const(UUID p_uuid) const;
	GameDataEntry *get_entry(UUID p_uuid);
	GameDataEntry *create_entry(UUID p_uuid);

	HashMap<UUID, GameDataEntry *> get_entries_const(Vector<UUID> p_uuids) const;
	HashMap<UUID, GameDataEntry *> get_entries(Vector<UUID> p_uuids);

	GameDataTable();
	GameDataTable(const GameDataTable &p_game_data_table);
	GameDataTable(GameDataDB *p_parent, TableSpecification *p_table_specification);
	~GameDataTable();
};

#endif // GAME_DATA_TABLE_H
