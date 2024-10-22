/* game_data_specifications.h */

#ifndef GAME_DATA_SPECIFICATIONS_H
#define GAME_DATA_SPECIFICATIONS_H

#pragma region godot_includes
#include "core/io/json.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/typedefs.h"
#include "core/variant/typed_array.h"
#pragma endregion godot_includes

#pragma region cm_includes
#include "../cm_enums.h"
#include "../vector_hashmap_pair.h"
#pragma endregion cm_includes

class GameDataTable;

// FieldSpecification serialization
// JSON
//---------------------------------
// {
// 	name : <String>,
// 	is_reference: <bool>,
// 	ref_table_name: <String>,
// 	ref_channel: <CM_DataChannel> (enum),
// 	property_info: PropertyInfo
// }
//---------------------------------
struct FieldSpecification
{
	String name = "";
	bool is_reference = false;
	String ref_table_name = "";
	cm_enums::CM_DataChannel ref_channel = cm_enums::CM_DataChannel::CM_DATA_CHANNEL_NONE;
	PropertyInfo info = PropertyInfo();

	Dictionary to_dict() const;
	void from_dict(Dictionary p_dict);

	String to_json(uint8_t p_indent) const;
	void from_json(JSON p_json);

	FieldSpecification();
	~FieldSpecification();
};

// TableSpecification serialization
// JSON
//---------------------------------
// {
// 	name: <String>,
// 	path: <String>,
// 	channel: <(String)cm_enums::CM_DataChannel>
// 	fields: [
// 		FieldSpecification,
// 		.
// 		.
// 	]
// }
//---------------------------------
struct TableSpecification
{
	String name = "";
	String path = "";
	cm_enums::CM_DataChannel channel = cm_enums::CM_DataChannel::CM_DATA_CHANNEL_NONE;

	VectorHashMapPair<String, FieldSpecification> fields;

	Dictionary to_dict() const;
	void from_dict(Dictionary p_dict);

	String to_json(uint8_t p_indent) const;
	void from_json();

	TableSpecification();
	~TableSpecification();
};
#endif // GAME_DATA_SPECIFICATIONS_H
