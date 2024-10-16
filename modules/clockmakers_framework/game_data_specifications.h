/* game_data_specifications.h */

#ifndef GAME_DATA_SPECIFICATIONS_H
#define GAME_DATA_SPECIFICATIONS_H

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"

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

#endif // GAME_DATA_SPECIFICATIONS_H
