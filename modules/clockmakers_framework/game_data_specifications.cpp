/* game_data_specifications.cpp */

#include "game_data_specifications.h"
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

String TableSpecification::get_name() const
{
	return name;
}

void TableSpecification::set_name(String p_name)
{
	name = p_name;
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
