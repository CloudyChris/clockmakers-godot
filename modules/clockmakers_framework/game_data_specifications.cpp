/* game_data_specifications.cpp */

#include "game_data_specifications.h"
#include "core/object/object.h"

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

void FieldSpecification::set_info(const PropertyInfo &p_info)
{
	info = p_info;
}

TableSpecification::TableSpecification()
{
}

TableSpecification::TableSpecification(const TableSpecification &p_table_specification)
	: fields(p_table_specification.fields)
{
}

TableSpecification::~TableSpecification()
{
	fields.~VectorHashMapPair();
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
	return fields.has(p_field_name);
}

FieldSpecification TableSpecification::get_field_specification(String p_field_name) const
{
	return fields.get_value(p_field_name);
}

void TableSpecification::set_field_specification(String p_field_name, FieldSpecification p_field_specification)
{
	fields.set_value(p_field_name, p_field_specification);
}

void TableSpecification::copy(const TableSpecification &p_table_specification)
{
	fields = p_table_specification.fields;
}
