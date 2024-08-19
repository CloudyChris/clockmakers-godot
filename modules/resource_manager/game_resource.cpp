/* game_resource.cpp */

#include "game_resource.h"
#include "core/object/object.h"
#include "core/variant/variant.h"

void GameResource::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_field_list"), &GameResource::get_field_list);
	ClassDB::bind_method(D_METHOD("add_field", "field_name", "property_hint", "type_hint", "property_usage"), &GameResource::add_field);
	ClassDB::bind_method(D_METHOD("remvoe_field", "field_name"), &GameResource::remove_field);
	ClassDB::bind_method(D_METHOD("get_field", "field_name"), &GameResource::get_field);
	ClassDB::bind_method(D_METHOD("set_field", "field_name", "data"), &GameResource::set_field);
	ClassDB::bind_method(D_METHOD("get_field_property_hint", "field_name"), &GameResource::get_field_property_hint);
	ClassDB::bind_method(D_METHOD("set_field_property_hint", "field_name", "property_hint"), &GameResource::set_field_property_hint);
	ClassDB::bind_method(D_METHOD("get_field_type_hint", "field_name"), &GameResource::get_field_type_hint);
	ClassDB::bind_method(D_METHOD("set_field_type_hint", "field_name", "type_hint"), &GameResource::set_field_type_hint);
	ClassDB::bind_method(D_METHOD("get_field_property_usage", "field_name"), &GameResource::get_field_property_usage);
	ClassDB::bind_method(D_METHOD("set_field_property_usage", "field_name", "property_usage"), &GameResource::set_field_property_usage);
}

GameResource::GameResourceField::GameResourceField()
	: name("")
	, type(Variant::OBJECT)
	, property_hint(PROPERTY_HINT_NONE)
	, type_hint("")
	, property_usage(PROPERTY_USAGE_DEFAULT)
{
}

GameResource::GameResourceField::GameResourceField(String p_name, Variant::Type p_type, PropertyHint p_property_hint, String p_type_hint, PropertyUsageFlags p_property_usage)
	: name(p_name)
	, type(p_type)
	, property_hint(p_property_hint)
	, type_hint(p_type_hint)
	, property_usage(p_property_usage)
{
}

GameResource::GameResourceField::GameResourceField(String p_name, Variant::Type p_type, PropertyHint p_property_hint, String p_type_hint, PropertyUsageFlags p_property_usage, Variant p_data)
	: name(p_name)
	, type(p_type)
	, property_hint(p_property_hint)
	, type_hint(p_type_hint)
	, property_usage(p_property_usage)
	, data(p_data)
{
}

GameResource::~GameResource()
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

PackedStringArray GameResource::get_field_list()
{
	PackedStringArray l_field_list;
	l_field_list.resize(fields.size());

	for (GameResourceField field : fields)
	{
		l_field_list.push_back(field.name);
	}

	return l_field_list;
}

bool GameResource::add_field(String p_field_name, Variant::Type p_field_type, PropertyHint p_property_hint, String p_type_hint, PropertyUsageFlags p_property_usage)
{
	if (field_cache.has(p_field_name))
	{
		return false;
	}

	fields.push_back(GameResourceField(p_field_name, p_field_type, p_property_hint, p_type_hint, p_property_usage));
	field_cache.insert(p_field_name, fields.size() - 1);
	return true;
}

bool GameResource::remove_field(String p_field_name)
{
	if (field_cache.has(p_field_name))
	{
		return false;
	}

	fields.remove_at(field_cache[p_field_name]);
	for (int i = 0; i < fields.size(); i++)
	{
		field_cache[fields[i].name] = i;
	}
	return true;
}

Variant GameResource::get_field(String p_field_name)
{
	return fields[field_cache[p_field_name]].data;
}

void GameResource::set_field(String p_field_name, Variant p_data)
{
	fields.get_m(field_cache[p_field_name]).data = p_data;
}

Variant::Type GameResource::get_field_type(String p_field_name)
{
	return fields[field_cache[p_field_name]].type;
}

void GameResource::set_field_type(String p_field_name, Variant::Type p_field_type)
{
	fields.get_m(field_cache[p_field_name]).type = p_field_type;
}

PropertyHint GameResource::get_field_property_hint(String p_field_name)
{
	return fields[field_cache[p_field_name]].property_hint;
}

void GameResource::set_field_property_hint(String p_field_name, PropertyHint p_property_hint)
{
	fields.get_m(field_cache[p_field_name]).property_hint = p_property_hint;
}

String GameResource::get_field_type_hint(String p_field_name)
{
	return fields[field_cache[p_field_name]].type_hint;
}

void GameResource::set_field_type_hint(String p_field_name, String p_type_hint)
{
	fields.get_m(field_cache[p_field_name]).type_hint = p_type_hint;
}

PropertyUsageFlags GameResource::get_field_property_usage(String p_field_name)
{
	return fields[field_cache[p_field_name]].property_usage;
}

void GameResource::set_field_property_usage(String p_field_name, PropertyUsageFlags p_property_usage)
{
	fields.get_m(field_cache[p_field_name]).property_usage = p_property_usage;
}
