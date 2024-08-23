/* resource_db.cpp */

#include "resource_db.h"

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/variant/dictionary.h"
#include "core/variant/variant.h"

void ResourceDB::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_field_list"), &ResourceDB::get_field_list);
	ClassDB::bind_method(D_METHOD("add_field", "field_specification"), &ResourceDB::_add_field_bind);
	ClassDB::bind_method(D_METHOD("get_field", "field_name"), &ResourceDB::_get_field_bind);
	ClassDB::bind_method(D_METHOD("set_field", "field_specification"), &ResourceDB::_set_field_bind);
	ClassDB::bind_method(D_METHOD("remvoe_field", "field_name"), &ResourceDB::remove_field);
	ClassDB::bind_method(D_METHOD("has_resource_field", "uuid", "field_name"), &ResourceDB::has_resource_field);
	ClassDB::bind_method(D_METHOD("get_resource_field", "uuid", "field_name"), &ResourceDB::get_resource_field);
	ClassDB::bind_method(D_METHOD("set_resource_field", "uuid", "field_name", "data"), &ResourceDB::set_resource_field);
	ClassDB::bind_method(D_METHOD("remvoe_resource_field", "uuid", "field_name"), &ResourceDB::remove_resource_field);
}

ResourceDB::FieldSpecification::FieldSpecification()
{
}
ResourceDB::FieldSpecification::FieldSpecification(const FieldSpecification &p_field_specification)
	: info(p_field_specification.info)
	, has_default_value(p_field_specification.has_default_value)
	, default_value(p_field_specification.default_value)
{
}

ResourceDB::FieldSpecification::FieldSpecification(PropertyInfo p_info, bool p_has_default_value, Variant *p_default_value)
	: info(p_info)
	, has_default_value(p_has_default_value)
	, default_value(*p_default_value)
{
}

ResourceDB::GameResource::GameResource(const GameResource &p_game_resource)
{
	fields.resize(p_game_resource.field_cache.size());
	for (KeyValue<String, int> entry : p_game_resource.field_cache)
	{
		fields.get_m(entry.value) = p_game_resource.fields[entry.value];
		field_cache[entry.key] = entry.value;
	}
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

ResourceDB::~ResourceDB()
{
	if (!fields.is_empty())
	{
		fields.clear();
	}

	if (!field_cache.is_empty())
	{
		field_cache.clear();
	}

	if (!resources.is_empty())
	{
		resources.clear();
	}

	if (!resource_cache.is_empty())
	{
		resource_cache.clear();
	}
}

PackedStringArray ResourceDB::get_field_list() const
{
	PackedStringArray l_field_list;
	l_field_list.resize(fields.size());

	for (FieldSpecification field : fields)
	{
		l_field_list.push_back(field.info.name);
	}

	return l_field_list;
}

bool ResourceDB::has_field(String p_field_name) const
{
	return field_cache.has(p_field_name);
}

bool ResourceDB::add_field(PropertyInfo p_info, bool p_has_default_value, Variant *p_default_value)
{
	if (field_cache.has(p_info.name))
	{
		return false;
	}

	fields.push_back(FieldSpecification(p_info, p_has_default_value, p_default_value));
	field_cache.insert(p_info.name, fields.size() - 1);
	return true;
}

bool ResourceDB::_add_field_bind(Dictionary p_field_specification)
{
	Dictionary l_pi_dict;
	PropertyInfo l_pi;
	bool l_has_default;
	Variant *l_default;
	if (p_field_specification.has("name"))
	{
		if (field_cache.has(p_field_specification["name"]))
		{
			return false;
		}
		l_pi_dict["name"] = p_field_specification["name"];
	}
	else
	{
		return false;
	}

	if (p_field_specification.has("type"))
	{
		l_pi_dict["type"] = p_field_specification["type"];
	}
	else
	{
		return false;
	}

	if (p_field_specification.has("class_name"))
	{
		l_pi_dict["class_name"] = p_field_specification["class_name"];
	}

	if (p_field_specification.has("hint"))
	{
		l_pi_dict["hint"] = p_field_specification["hint"];
	}

	if (p_field_specification.has("hint_string"))
	{
		l_pi_dict["hint_string"] = p_field_specification["hint_string"];
	}

	if (p_field_specification.has("usage"))
	{
		l_pi_dict["usage"] = p_field_specification["usage"];
	}

	l_pi = PropertyInfo::from_dict(l_pi_dict);

	l_has_default = p_field_specification.has("has_default_value") ? bool(p_field_specification["has_default_value"]) : false;

	l_default = p_field_specification.has("default_value") ? &p_field_specification["default_value"] : nullptr;

	add_field(l_pi, l_has_default, l_default);

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
		field_cache[fields[i].info.name] = i;
	}

	return true;
}

const ResourceDB::FieldSpecification &ResourceDB::get_field(String p_field_name) const
{
	return fields[field_cache[p_field_name]];
}

Dictionary ResourceDB::_get_field_bind(String p_field_name)
{
	FieldSpecification l_field = fields[field_cache[p_field_name]];

	Dictionary l_dict;

	l_dict.merge(Dictionary(l_field.info));

	l_dict["has_default_value"] = l_field.default_value;

	l_dict["default_value"] = l_field.default_value;

	return l_dict;
}

void ResourceDB::set_field(PropertyInfo p_info, bool p_has_default_value, Variant *p_default_value)
{
	FieldSpecification &l_field = fields.get_m(field_cache[p_info.name]);

	l_field.info = p_info;
	l_field.has_default_value = p_has_default_value;
	if (p_default_value)
	{
		l_field.default_value = *p_default_value;
	}
}

void ResourceDB::_set_field_bind(Dictionary p_field_specification)
{
	Dictionary l_pi_dict;
	PropertyInfo l_pi;
	bool l_has_default;
	Variant *l_default;
	if (p_field_specification.has("name"))
	{
		l_pi_dict["name"] = p_field_specification["name"];
	}
	else
	{
		return;
	}

	FieldSpecification &l_field = fields.get_m(field_cache[p_field_specification["name"]]);

	if (p_field_specification.has("type"))
	{
		l_pi_dict["type"] = p_field_specification["type"];
	}
	else
	{
		return;
	}

	if (p_field_specification.has("class_name"))
	{
		l_pi_dict["class_name"] = p_field_specification["class_name"];
	}

	if (p_field_specification.has("hint"))
	{
		l_pi_dict["hint"] = p_field_specification["hint"];
	}

	if (p_field_specification.has("hint_string"))
	{
		l_pi_dict["hint_string"] = p_field_specification["hint_string"];
	}

	if (p_field_specification.has("usage"))
	{
		l_pi_dict["usage"] = p_field_specification["usage"];
	}

	l_pi = PropertyInfo::from_dict(l_pi_dict);

	l_has_default = p_field_specification.has("has_default_value") ? bool(p_field_specification["has_default_value"]) : l_field.has_default_value;

	l_default = p_field_specification.has("default_value") ? &p_field_specification["default_value"] : nullptr;

	l_field.info = l_pi;
	l_field.has_default_value = l_has_default;

	if (l_default)
	{
		l_field.default_value = *l_default;
	}
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
