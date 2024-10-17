/* game_data_specifications.h */

#ifndef GAME_DATA_SPECIFICATIONS_H
#define GAME_DATA_SPECIFICATIONS_H

#include "core/io/json.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"
#include "vector_hashmap_pair.h"

class GameDataTable;

// FieldSpecification serialization
// JSON
//---------------------------------
// {
// 	name : <String>,
// 	property_info : PropertyInfo
// }
//---------------------------------
//
// BINARY
//---------------------------------
// WIP
//---------------------------------
class FieldSpecification
{
private:
	String name;
	PropertyInfo info;

public:
	String get_name() const;
	void set_name(String p_name);

	PropertyInfo get_info() const;
	void set_info(const PropertyInfo &p_info);

	Dictionary to_dict();
	void from_dict(Dictionary p_dict);

	JSON to_json();
	void from_json();

	FieldSpecification();
	FieldSpecification(const FieldSpecification &p_field_specification);
	~FieldSpecification();
};

// TableSpecification serialization
// JSON
//---------------------------------
// {
// 	name: <String>,
// 	fields: [
// 		FieldSpecification,
// 		.
// 		.
// 	]
// }
//---------------------------------
//
// BINARY
//---------------------------------
// WIP
//---------------------------------
class TableSpecification

{
private:
	String name;

	VectorHashMapPair<String, FieldSpecification> fields;

public:
	String get_name() const;
	void set_name(String p_name);

	bool has_field(String p_field_name) const;
	FieldSpecification get_field_specification(String p_field_name) const;
	void set_field_specification(String p_field_name, FieldSpecification p_field_specification);

	void copy(const TableSpecification &p_table_specification);

	Dictionary to_dict();
	void from_dict(Dictionary p_dict);

	JSON to_json();
	void from_json();

	TableSpecification();
	TableSpecification(const TableSpecification &p_game_data_table);
	~TableSpecification();
};

// GameDataRegistry serialization
// JSON
//---------------------------------
// {
// 	table_name : {
// 		table_specification: TableSpecification,
// 		data_type : CM_DataType
// 		entries : {
// 			uuid : path <String>,
// 			.
// 			.
// 		}
// 	},
// 	.
// 	.
// }
//---------------------------------

// This will own all table specifications, which will now also need info on where they come from
//  as per the structure defined above
//  This is loaded first and then tables are created in databases and table specification pointers give to the DB
//

class GameDataRegistry
{
};

#endif // GAME_DATA_SPECIFICATIONS_H
