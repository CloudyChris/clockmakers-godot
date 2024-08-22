/* resource_db.cpp */

#include "resource_db.h"

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/variant/dictionary.h"
#include "core/variant/variant.h"

void ResourceDB::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_field_list"), &ResourceDB::get_field_list);
	ClassDB::bind_method(D_METHOD("add_field", "field_name", "field_type", "property_hint", "type_hint", "property_usage"), &ResourceDB::add_field);
	ClassDB::bind_method(D_METHOD("remvoe_field", "field_name"), &ResourceDB::remove_field);
	ClassDB::bind_method(D_METHOD("get_field_property_hint", "field_name"), &ResourceDB::get_field_property_hint);
	ClassDB::bind_method(D_METHOD("set_field_property_hint", "field_name", "property_hint"), &ResourceDB::set_field_property_hint);
	ClassDB::bind_method(D_METHOD("get_field_type_hint", "field_name"), &ResourceDB::get_field_type_hint);
	ClassDB::bind_method(D_METHOD("set_field_type_hint", "field_name", "type_hint"), &ResourceDB::set_field_type_hint);
	ClassDB::bind_method(D_METHOD("get_field_property_usage", "field_name"), &ResourceDB::get_field_property_usage);
	ClassDB::bind_method(D_METHOD("set_field_property_usage", "field_name", "property_usage"), &ResourceDB::set_field_property_usage);
}

ResourceDB::GameResourceFieldSpecification::GameResourceFieldSpecification()
	: name("")
	, type(Variant::Type::NIL)
	, property_hint(PROPERTY_HINT_NONE)
	, type_hint("")
	, property_usage(PROPERTY_USAGE_DEFAULT)
{
}

ResourceDB::GameResourceFieldSpecification::GameResourceFieldSpecification(String p_name, Variant::Type p_type, PropertyHint p_property_hint, String p_type_hint, PropertyUsageFlags p_property_usage)
	: name(p_name)
	, type(p_type)
	, property_hint(p_property_hint)
	, type_hint(p_type_hint)
	, property_usage(p_property_usage)
{
}

Variant::Type ResourceDB::GameResourceFieldSpecification::typestring_to_enum(String p_typestring)
{
	if (p_typestring == "BOOL")
	{
		return Variant::Type::BOOL;
	}
	else if (p_typestring == "INT")
	{
		return Variant::Type::INT;
	}
	else if (p_typestring == "FLOAT")
	{
		return Variant::Type::FLOAT;
	}
	else if (p_typestring == "STRING")
	{
		return Variant::Type::STRING;
	}
	else if (p_typestring == "VECTOR2")
	{
		return Variant::Type::VECTOR2;
	}
	else if (p_typestring == "VECTOR2I")
	{
		return Variant::Type::VECTOR2I;
	}
	else if (p_typestring == "RECT2")
	{
		return Variant::Type::RECT2;
	}
	else if (p_typestring == "RECT2I")
	{
		return Variant::Type::RECT2I;
	}
	else if (p_typestring == "VECTOR3")
	{
		return Variant::Type::VECTOR3;
	}
	else if (p_typestring == "VECTOR3I")
	{
		return Variant::Type::VECTOR3I;
	}
	else if (p_typestring == "TRANSFORM2D")
	{
		return Variant::Type::TRANSFORM2D;
	}
	else if (p_typestring == "VECTOR4")
	{
		return Variant::Type::VECTOR4;
	}
	else if (p_typestring == "VECTOR4I")
	{
		return Variant::Type::VECTOR4I;
	}
	else if (p_typestring == "PLANE")
	{
		return Variant::Type::PLANE;
	}
	else if (p_typestring == "QUATERNION")
	{
		return Variant::Type::QUATERNION;
	}
	else if (p_typestring == "AABB")
	{
		return Variant::Type::AABB;
	}
	else if (p_typestring == "BASIS")
	{
		return Variant::Type::BASIS;
	}
	else if (p_typestring == "TRANSFORM3D")
	{
		return Variant::Type::TRANSFORM3D;
	}
	else if (p_typestring == "PROJECTION")
	{
		return Variant::Type::PROJECTION;
	}
	else if (p_typestring == "COLOR")
	{
		return Variant::Type::COLOR;
	}
	else if (p_typestring == "STRING_NAME")
	{
		return Variant::Type::STRING_NAME;
	}
	else if (p_typestring == "NODE_PATH")
	{
		return Variant::Type::NODE_PATH;
	}
	else if (p_typestring == "RID")
	{
		return Variant::Type::RID;
	}
	else if (p_typestring == "OBJECT")
	{
		return Variant::Type::OBJECT;
	}
	else if (p_typestring == "CALLABLE")
	{
		return Variant::Type::CALLABLE;
	}
	else if (p_typestring == "SIGNAL")
	{
		return Variant::Type::SIGNAL;
	}
	else if (p_typestring == "DICTIONARY")
	{
		return Variant::Type::DICTIONARY;
	}
	else if (p_typestring == "ARRAY")
	{
		return Variant::Type::ARRAY;
	}
	else if (p_typestring == "PACKED_BYTE_ARRAY")
	{
		return Variant::Type::PACKED_BYTE_ARRAY;
	}
	else if (p_typestring == "PACKED_INT32_ARRAY")
	{
		return Variant::Type::PACKED_INT32_ARRAY;
	}
	else if (p_typestring == "PACKED_INT64_ARRAY")
	{
		return Variant::Type::PACKED_INT64_ARRAY;
	}
	else if (p_typestring == "PACKED_FLOAT32_ARRAY")
	{
		return Variant::Type::PACKED_FLOAT32_ARRAY;
	}
	else if (p_typestring == "PACKED_FLOAT64_ARRAY")
	{
		return Variant::Type::PACKED_FLOAT64_ARRAY;
	}
	else if (p_typestring == "PACKED_STRING_ARRAY")
	{
		return Variant::Type::PACKED_STRING_ARRAY;
	}
	else if (p_typestring == "PACKED_VECTOR2_ARRAY")
	{
		return Variant::Type::PACKED_VECTOR2_ARRAY;
	}
	else if (p_typestring == "PACKED_VECTOR3_ARRAY")
	{
		return Variant::Type::PACKED_VECTOR3_ARRAY;
	}
	else if (p_typestring == "PACKED_COLOR_ARRAY")
	{
		return Variant::Type::PACKED_COLOR_ARRAY;
	}
	else if (p_typestring == "VARIANT_MAX")
	{
		return Variant::Type::VARIANT_MAX;
	}

	return Variant::Type::NIL;
}

String ResourceDB::GameResourceFieldSpecification::enum_to_typestring(Variant::Type p_type)
{
	if (p_type == Variant::Type::BOOL)
	{
		return "BOOL";
	}
	else if (p_type == Variant::Type::INT)
	{
		return "INT";
	}
	else if (p_type == Variant::Type::FLOAT)
	{
		return "FLOAT";
	}
	else if (p_type == Variant::Type::STRING)
	{
		return "STRING";
	}
	else if (p_type == Variant::Type::VECTOR2)
	{
		return "VECTOR2";
	}
	else if (p_type == Variant::Type::VECTOR2I)
	{
		return "VECTOR2I";
	}
	else if (p_type == Variant::Type::RECT2)
	{
		return "RECT2";
	}
	else if (p_type == Variant::Type::RECT2I)
	{
		return "RECT2I";
	}
	else if (p_type == Variant::Type::VECTOR3)
	{
		return "VECTOR3";
	}
	else if (p_type == Variant::Type::VECTOR3I)
	{
		return "VECTOR3I";
	}
	else if (p_type == Variant::Type::TRANSFORM2D)
	{
		return "TRANSFORM2D";
	}
	else if (p_type == Variant::Type::VECTOR4)
	{
		return "VECTOR4";
	}
	else if (p_type == Variant::Type::VECTOR4I)
	{
		return "VECTOR4I";
	}
	else if (p_type == Variant::Type::PLANE)
	{
		return "PLANE";
	}
	else if (p_type == Variant::Type::QUATERNION)
	{
		return "QUATERNION";
	}
	else if (p_type == Variant::Type::AABB)
	{
		return "AABB";
	}
	else if (p_type == Variant::Type::BASIS)
	{
		return "BASIS";
	}
	else if (p_type == Variant::Type::TRANSFORM3D)
	{
		return "TRANSFORM3D";
	}
	else if (p_type == Variant::Type::PROJECTION)
	{
		return "PROJECTION";
	}
	else if (p_type == Variant::Type::COLOR)
	{
		return "COLOR";
	}
	else if (p_type == Variant::Type::STRING_NAME)
	{
		return "STRING_NAME";
	}
	else if (p_type == Variant::Type::NODE_PATH)
	{
		return "NODE_PATH";
	}
	else if (p_type == Variant::Type::RID)
	{
		return "RID";
	}
	else if (p_type == Variant::Type::OBJECT)
	{
		return "OBJECT";
	}
	else if (p_type == Variant::Type::CALLABLE)
	{
		return "CALLABLE";
	}
	else if (p_type == Variant::Type::SIGNAL)
	{
		return "SIGNAL";
	}
	else if (p_type == Variant::Type::DICTIONARY)
	{
		return "DICTIONARY";
	}
	else if (p_type == Variant::Type::ARRAY)
	{
		return "ARRAY";
	}
	else if (p_type == Variant::Type::PACKED_BYTE_ARRAY)
	{
		return "PACKED_BYTE_ARRAY";
	}
	else if (p_type == Variant::Type::PACKED_INT32_ARRAY)
	{
		return "PACKED_INT32_ARRAY";
	}
	else if (p_type == Variant::Type::PACKED_INT64_ARRAY)
	{
		return "PACKED_INT64_ARRAY";
	}
	else if (p_type == Variant::Type::PACKED_FLOAT32_ARRAY)
	{
		return "PACKED_FLOAT32_ARRAY";
	}
	else if (p_type == Variant::Type::PACKED_FLOAT64_ARRAY)
	{
		return "PACKED_FLOAT64_ARRAY";
	}
	else if (p_type == Variant::Type::PACKED_STRING_ARRAY)
	{
		return "PACKED_STRING_ARRAY";
	}
	else if (p_type == Variant::Type::PACKED_VECTOR2_ARRAY)
	{
		return "PACKED_VECTOR2_ARRAY";
	}
	else if (p_type == Variant::Type::PACKED_VECTOR3_ARRAY)
	{
		return "PACKED_VECTOR3_ARRAY";
	}
	else if (p_type == Variant::Type::PACKED_COLOR_ARRAY)
	{
		return "PACKED_COLOR_ARRAY";
	}
	else if (p_type == Variant::Type::VARIANT_MAX)
	{
		return "VARIANT_MAX";
	}

	return "NIL";
}

ResourceDB::GameResource::~GameResource()
{
	if (!fields.is_empty())
	{
		fields.clear();
	}

	if (!field_cache.is_empty())
	{
		field_cache.clear();
	}
}

bool ResourceDB::GameResource::has_field(String p_field_name) const
{
	return field_cache.has(p_field_name);
}

Variant ResourceDB::GameResource::get_field(String p_field_name)
{
	return fields[field_cache[p_field_name]];
}

void ResourceDB::GameResource::set_field(String p_field_name, Variant p_data)
{
	if (field_cache.has(p_field_name))
	{
		fields.get_m(field_cache[p_field_name]) = p_data;
		return;
	}

	fields.push_back(p_data);
	field_cache.insert(p_field_name, fields.size() - 1);
}

bool ResourceDB::GameResource::remove_field(String p_field_name)
{
	if (!field_cache.has(p_field_name))
	{
		return false;
	}

	fields.remove_at(field_cache[p_field_name]);

	int l_deleted_index = field_cache[p_field_name];
	field_cache.erase(p_field_name);

	for (KeyValue<String, int> entry : field_cache)
	{
		if (entry.value > l_deleted_index)
		{
			field_cache[entry.key] = entry.value - 1;
		}
	}

	return true;
}
PackedStringArray ResourceDB::get_field_list() const
{
	PackedStringArray l_field_list;
	l_field_list.resize(fields.size());

	for (GameResourceFieldSpecification field : fields)
	{
		l_field_list.push_back(field.name);
	}

	return l_field_list;
}

bool ResourceDB::has_field(String p_field_name) const
{
	return field_cache.has(p_field_name);
}

bool ResourceDB::add_field(String p_field_name, String p_field_typestring, PropertyHint p_property_hint, String p_type_hint, PropertyUsageFlags p_property_usage)
{
	if (field_cache.has(p_field_name))
	{
		return false;
	}

	fields.push_back(GameResourceFieldSpecification(p_field_name, GameResourceFieldSpecification::typestring_to_enum(p_field_typestring), p_property_hint, p_type_hint, p_property_usage));
	field_cache.insert(p_field_name, fields.size() - 1);
	return true;
}

bool ResourceDB::remove_field(String p_field_name)
{
	if (!field_cache.has(p_field_name))
	{
		return false;
	}

	fields.remove_at(field_cache[p_field_name]);
	field_cache.erase(p_field_name);

	for (int i = 0; i < fields.size(); i++)
	{
		field_cache[fields[i].name] = i;
	}

	return true;
}

String ResourceDB::get_field_typestring(String p_field_name)
{
	return GameResourceFieldSpecification::enum_to_typestring(fields[field_cache[p_field_name]].type);
}

void ResourceDB::set_field_typestring(String p_field_name, String p_field_typestring)
{
	fields.get_m(field_cache[p_field_name]).type = GameResourceFieldSpecification::typestring_to_enum(p_field_typestring);
}

PropertyHint ResourceDB::get_field_property_hint(String p_field_name)
{
	return fields[field_cache[p_field_name]].property_hint;
}

void ResourceDB::set_field_property_hint(String p_field_name, PropertyHint p_property_hint)
{
	fields.get_m(field_cache[p_field_name]).property_hint = p_property_hint;
}

String ResourceDB::get_field_type_hint(String p_field_name)
{
	return fields[field_cache[p_field_name]].type_hint;
}

void ResourceDB::set_field_type_hint(String p_field_name, String p_type_hint)
{
	fields.get_m(field_cache[p_field_name]).type_hint = p_type_hint;
}

PropertyUsageFlags ResourceDB::get_field_property_usage(String p_field_name)
{
	return fields[field_cache[p_field_name]].property_usage;
}

void ResourceDB::set_field_property_usage(String p_field_name, PropertyUsageFlags p_property_usage)
{
	fields.get_m(field_cache[p_field_name]).property_usage = p_property_usage;
}

bool ResourceDB::has_resource_field(String p_uuid, String p_field_name) const
{
	return resources[resource_cache[p_uuid]].has_field(p_field_name);
}

Variant ResourceDB::get_resource_field(String p_uuid, String p_field_name)
{
	return resources.get_m(resource_cache[p_uuid]).get_field(p_field_name);
}

void ResourceDB::set_resource_field(String p_uuid, String p_field_name, Variant p_data)
{
	resources.get_m(resource_cache[p_uuid]).set_field(p_field_name, p_data);
}

bool ResourceDB::remove_resource_field(String p_uuid, String p_field_name)
{
	return resources.get_m(resource_cache[p_uuid]).remove_field(p_field_name);
}
