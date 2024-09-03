/* resource_db.cpp */

#include "resource_db.h"

#include "core/error/error_macros.h"
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

	ClassDB::bind_method(D_METHOD("has_resource", "uuid"), &ResourceDB::has_resource);
	ClassDB::bind_method(D_METHOD("add_resource", "game_resource"), &ResourceDB::_add_resource_bind);
	ClassDB::bind_method(D_METHOD("get_resource", "uuid"), &ResourceDB::_get_resource_bind);
	ClassDB::bind_method(D_METHOD("set_resource", "game_resource"), &ResourceDB::_set_resource_bind);
	ClassDB::bind_method(D_METHOD("remove_resource", "uuid"), &ResourceDB::remove_resource);

	ClassDB::bind_method(D_METHOD("has_resource_field", "uuid", "field_name"), &ResourceDB::has_resource_field);
	ClassDB::bind_method(D_METHOD("add_resource_field", "uuid", "field_name", "data"), &ResourceDB::add_resource_field);
	ClassDB::bind_method(D_METHOD("get_resource_field", "uuid", "field_name"), &ResourceDB::get_resource_field);
	ClassDB::bind_method(D_METHOD("set_resource_field", "uuid", "field_name", "data"), &ResourceDB::set_resource_field);
	ClassDB::bind_method(D_METHOD("remvoe_resource_field", "uuid", "field_name"), &ResourceDB::remove_resource_field);
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

ResourceDB::FieldSpecification ResourceDB::FieldSpecification::from_dict(Dictionary p_field_specification)
{
	FieldSpecification l_field_specification;

	if (!p_field_specification.has("info"))
	{
		return FieldSpecification();
	}

	l_field_specification.info = PropertyInfo::from_dict(p_field_specification["info"]);

	if (l_field_specification.info.name == "")
	{
		return FieldSpecification();
	}

	if (l_field_specification.info.type == Variant::NIL || l_field_specification.info.type == Variant::VARIANT_MAX)
	{
		return FieldSpecification();
	}

	l_field_specification.has_default_value = p_field_specification.has("has_default_value") ? bool(p_field_specification["has_default_value"]) : false;

	if (p_field_specification.has("default_value"))
	{
		l_field_specification.default_value = p_field_specification["default_value"];
	}

	return l_field_specification;
}

ResourceDB::FieldSpecification::operator Dictionary() const
{
	Dictionary l_field_specification_dictionary;

	l_field_specification_dictionary["info"] = static_cast<Dictionary>(info);
	l_field_specification_dictionary["has_default_value"] = has_default_value;
	l_field_specification_dictionary["default_value"] = default_value;

	return l_field_specification_dictionary;
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

ResourceDB::GameResource ResourceDB::GameResource::from_dict(Dictionary p_game_resource_dictionary)
{
	GameResource l_game_resource;
	ERR_FAIL_COND_V_MSG(p_game_resource_dictionary.has("uuid"), GameResource(), "GameResource dictionary uuid missing");
	ERR_FAIL_COND_V_MSG(p_game_resource_dictionary.has("resource_path"), GameResource(), "GameResource dictionary uuid missing");
	ERR_FAIL_COND_V_MSG(p_game_resource_dictionary.has("resource_type"), GameResource(), "GameResource dictionary resource_type missing");
	l_game_resource.uuid = UUID(PackedByteArray(p_game_resource_dictionary["uuid"]));
	l_game_resource.set_path(p_game_resource_dictionary["resource_path"]);
	l_game_resource.resource_type = p_game_resource_dictionary["resource_type"];

	Dictionary l_game_resource_fields_dictionary = p_game_resource_dictionary["fields"];

	for (int i = 0; i < l_game_resource_fields_dictionary.size(); i++)
	{
		l_game_resource.fields.push_back(l_game_resource_fields_dictionary.values()[i]);
		l_game_resource.field_cache.insert(l_game_resource_fields_dictionary.keys()[i], i);
	}

	return l_game_resource;
}

bool ResourceDB::GameResource::has_field(String p_field_name) const
{
	return field_cache.has(p_field_name);
}

bool ResourceDB::GameResource::add_field(String p_field_name, Variant p_data)
{
	if (field_cache.has(p_field_name))
	{
		return false;
	}

	fields.push_back(p_data);
	field_cache.insert(p_field_name, fields.size() - 1);

	return true;
}

Variant ResourceDB::GameResource::get_field(String p_field_name)
{
	return fields[field_cache[p_field_name]];
}

void ResourceDB::GameResource::set_field(String p_field_name, Variant p_data)
{
	fields.get_m(field_cache[p_field_name]) = p_data;
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

bool ResourceDB::GameResource::validate_fields(const ResourceDB &p_parent) const
{
	for (KeyValue<String, int> entry : field_cache)
	{
		if (entry.key.is_empty())
		{
			return false;
		}

		if (!has_field(entry.key))
		{
			return false;
		}

		if (fields[entry.value].get_type() != p_parent.get_field(entry.key).info.type)
		{
			return false;
		}
	}

	return true;
}

ResourceDB::GameResource::operator Dictionary() const
{
	Dictionary l_game_resource_dictionary, l_game_resource_fields_dictionary;

	for (KeyValue<String, int> entry : field_cache)
	{
		l_game_resource_fields_dictionary[entry.key] = fields[entry.value];
	}

	l_game_resource_dictionary["uuid"] = uuid.uuid;
	l_game_resource_dictionary["resource_path"] = get_path();
	l_game_resource_dictionary["resource_type"] = resource_type;
	l_game_resource_dictionary["fields"] = l_game_resource_fields_dictionary;

	return l_game_resource_dictionary;
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

bool ResourceDB::has_field(String p_field_name) const
{
	return field_cache.has(p_field_name);
}

bool ResourceDB::validate_field(const ResourceDB::FieldSpecification &p_field_specification, bool p_is_add) const
{
	if (p_field_specification.info.name == "" || p_field_specification.info.type == Variant::Type::NIL)
	{
		return false;
	}

	if (p_is_add)
	{
		if (field_cache.has(p_field_specification.info.name))
		{
			return false;
		}
	}

	if (p_field_specification.default_value && p_field_specification.default_value.get_type() != p_field_specification.info.type)
	{
		return false;
	}

	return true;
}

bool ResourceDB::add_field(PropertyInfo p_info, bool p_has_default_value, Variant *p_default_value, bool p_check)
{
	return add_field(FieldSpecification(p_info, p_has_default_value, p_default_value), p_check);
}

bool ResourceDB::add_field(const FieldSpecification &p_field_specification, bool p_check)
{
	if (p_check)
	{
		if (!validate_field(p_field_specification, true))
		{
			return false;
		}
	}

	fields.push_back(p_field_specification);
	field_cache.insert(p_field_specification.info.name, fields.size() - 1);
	return true;
}

bool ResourceDB::_add_field_bind(Dictionary p_field_specification, bool p_check)
{
	return add_field(FieldSpecification::from_dict(p_field_specification), p_check);
}

bool ResourceDB::add_fields(Vector<ResourceDB::FieldSpecification> p_fields, bool p_check)
{
	if (p_check)
	{
		for (FieldSpecification field : p_fields)
		{
			if (!validate_field(field, true))
			{
				return false;
			}
		}
	}

	for (FieldSpecification field : p_fields)
	{
		fields.push_back(field);
		field_cache.insert(field.info.name, fields.size() - 1);
	}

	return true;
}

bool ResourceDB::_add_fields_bild(Array p_fields, bool p_check)
{
	Vector<FieldSpecification> l_fields;
	for (Dictionary dict : p_fields)
	{
		l_fields.push_back(FieldSpecification::from_dict(dict));
	}

	return add_fields(l_fields, p_check);
}

ResourceDB::FieldSpecification &ResourceDB::get_field(String p_field_name)
{
	return fields.get_m(field_cache[p_field_name]);
}

const ResourceDB::FieldSpecification &ResourceDB::get_field(String p_field_name) const
{
	return fields[field_cache[p_field_name]];
}

Dictionary ResourceDB::_get_field_bind(String p_field_name)
{
	FieldSpecification l_field = fields[field_cache[p_field_name]];

	Dictionary l_dict = l_field;

	return l_dict;
}

PackedStringArray ResourceDB::get_field_list() const
{
	PackedStringArray l_field_list;
	l_field_list.resize(fields.size());

	for (int i = 0; i < fields.size(); i++)
	{
		l_field_list.set(i, fields[i].info.name);
	}

	return l_field_list;
}

Vector<ResourceDB::FieldSpecification> ResourceDB::get_fields()
{
	return fields;
}

Array ResourceDB::_get_fields_bind()
{
	Array l_array;
	l_array.resize(fields.size());

	for (int i = 0; i < fields.size(); i++)
	{
		l_array.set(i, _get_field_bind(fields[i].info.name));
	}

	return l_array;
}

void ResourceDB::set_field(PropertyInfo p_info, bool p_has_default_value, Variant *p_default_value, bool p_check)
{
	set_field(FieldSpecification(p_info, p_has_default_value, p_default_value), p_check);
}

void ResourceDB::set_field(const FieldSpecification &p_field_specification, bool p_check)
{
	FieldSpecification &l_field_ref = fields.get_m(field_cache[p_field_specification.info.name]);

	if (p_check)
	{
		if (!validate_field(p_field_specification))
		{
			return;
		}
	}

	l_field_ref = p_field_specification;
}

void ResourceDB::_set_field_bind(Dictionary p_field_specification, bool p_check)
{
	FieldSpecification l_field = FieldSpecification::from_dict(p_field_specification);

	set_field(l_field, p_check);
}
void ResourceDB::set_fields(Vector<ResourceDB::FieldSpecification> p_fields, bool p_check)
{
	if (p_check)
	{
		for (FieldSpecification field : p_fields)
		{
			if (!validate_field(field))
			{
				return;
			}
		}
	}

	fields = p_fields;
}

void ResourceDB::_set_fields_bind(Array p_fields, bool p_check)
{
	Vector<ResourceDB::FieldSpecification> l_fields;

	l_fields.resize(p_fields.size());

	if (p_check)
	{
		for (Dictionary dict : p_fields)
		{
			if (!dict.has("info"))
			{
				return;
			}

			if (!Dictionary(dict["info"]).has("name") && !String(Dictionary(dict["info"])["name"]).is_empty())
			{
				return;
			}

			if (!Dictionary(dict["info"]).has("type") && !(int(Dictionary(dict["info"])["type"]) == Variant::Type::NIL))
			{
				return;
			}
		}
	}

	for (int i = 0; i < p_fields.size(); i++)
	{
		l_fields.set(i, FieldSpecification::from_dict(p_fields[i]));
	}
}

bool ResourceDB::remove_field(String p_field_name, bool p_check)
{
	if (p_check)
	{
		if (!field_cache.has(p_field_name))
		{
			return false;
		}
	}

	fields.remove_at(field_cache[p_field_name]);
	field_cache.erase(p_field_name);

	for (int i = 0; i < fields.size(); i++)
	{
		field_cache[fields[i].info.name] = i;
	}

	return true;
}

bool ResourceDB::remove_fields(PackedStringArray p_fields, bool p_check)
{
	if (p_check)
	{
		for (String field : p_fields)
		{
			if (!field_cache.has(field))
			{
				return false;
			}
		}
	}

	for (String field : p_fields)
	{
		remove_field(field, !p_check);
	}

	return true;
}

bool ResourceDB::has_resource(String p_uuid) const
{
	return resource_cache.has(p_uuid);
}

bool ResourceDB::validate_resource(const ResourceDB::GameResource &p_game_resource, bool p_is_add) const
{
	if (p_game_resource.get_uuid_const().is_empty() || p_game_resource.resource_type.is_empty())
	{
		return false;
	}

	if (p_is_add)
	{
		if (resource_cache.has(p_game_resource.get_human_readable_uuid_const()))
		{
			return false;
		}
	}

	if (!p_game_resource.validate_fields(*this))
	{
		return false;
	}

	return true;
}

bool ResourceDB::add_resource(GameResource p_game_resource, bool p_check)
{
	if (p_check)
	{
		if (!validate_resource(p_game_resource, true))
		{
			return false;
		}
	}

	resources.push_back(&p_game_resource);
	resource_cache.insert(p_game_resource.get_human_readable_uuid(), resources.size() - 1);

	return true;
}

bool ResourceDB::_add_resource_bind(Dictionary p_game_resource_dictionary, bool p_check)
{
	GameResource l_game_resource = GameResource::from_dict(p_game_resource_dictionary);

	return add_resource(l_game_resource, p_check);
}

bool ResourceDB::add_resources(HashMap<String, ResourceDB::GameResource *> p_game_resources, bool p_check)
{
	if (p_check)
	{
		for (KeyValue<String, GameResource *> entry : p_game_resources)
		{
			if (!validate_resource(*entry.value, true))
			{
				return false;
			}
		}
	}

	for (KeyValue<String, GameResource *> entry : p_game_resources)
	{
		add_resource(*entry.value, !p_check);
	}

	return true;
}

bool ResourceDB::_add_resources_bind(Dictionary p_game_resources, bool p_check)
{
	HashMap<String, GameResource *> l_game_resources;

	for (String key : p_game_resources.keys())
	{
		GameResource *l_gr = new GameResource(GameResource::from_dict(p_game_resources[key]));
		l_game_resources.insert(key, l_gr);
	}

	return add_resources(l_game_resources, p_check);
}

const ResourceDB::GameResource &ResourceDB::get_resource(String p_uuid) const
{
	return *resources[resource_cache[p_uuid]];
}

ResourceDB::GameResource &ResourceDB::get_resource_m(String p_uuid)
{
	return *resources[resource_cache[p_uuid]];
}

Dictionary ResourceDB::_get_resource_bind(String p_uuid)
{
	return *resources[resource_cache[p_uuid]];
}

PackedStringArray ResourceDB::get_resource_list() const
{
	PackedStringArray l_game_resource_uuid_list;

	for (GameResource *entry : resources)
	{
		l_game_resource_uuid_list.push_back(entry->get_human_readable_uuid());
	}

	return l_game_resource_uuid_list;
}

HashMap<String, ResourceDB::GameResource *> ResourceDB::get_resources()
{
	HashMap<String, GameResource *> l_game_resources;

	for (GameResource *entry : resources)
	{
		l_game_resources.insert(entry->get_human_readable_uuid(), entry);
	}

	return l_game_resources;
}

Dictionary ResourceDB::_get_resources_bind()
{
	Dictionary l_game_resources;

	for (GameResource *entry : resources)
	{
		l_game_resources[entry->get_human_readable_uuid()] = static_cast<Dictionary>(*entry);
	}

	return l_game_resources;
}

void ResourceDB::set_resource(GameResource p_game_resource, bool p_check)
{
	if (p_check)
	{
		if (!validate_resource(p_game_resource))
		{
			return;
		}
	}

	GameResource &l_game_resource = *resources[resource_cache[p_game_resource.get_human_readable_uuid()]];
	l_game_resource.fields = p_game_resource.fields;
	l_game_resource.field_cache = p_game_resource.field_cache;
}

void ResourceDB::_set_resource_bind(Dictionary p_game_resource_dictionary, bool p_check)
{
	set_resource(GameResource::from_dict(p_game_resource_dictionary), p_check);
}

void ResourceDB::set_resources(HashMap<String, ResourceDB::GameResource *> p_game_resources, bool p_check)
{
	if (p_check)
	{
		for (KeyValue<String, GameResource *> entry : p_game_resources)
		{
			if (!validate_resource(*entry.value))
			{
				return;
			}
		}
	}

	for (KeyValue<String, GameResource *> entry : p_game_resources)
	{
		set_resource(*entry.value, !p_check);
	}
}

void ResourceDB::_set_resources_bind(Dictionary p_game_resources, bool p_check)
{
	HashMap<String, ResourceDB::GameResource *> l_game_resources;

	for (String key : p_game_resources.keys())
	{
		GameResource *l_gr = new GameResource(GameResource::from_dict(p_game_resources[key]));
		l_game_resources.insert(key, l_gr);
	}

	set_resources(l_game_resources, p_check);
}

bool ResourceDB::remove_resource(String p_uuid, bool p_check)
{
	if (!resource_cache.has(p_uuid))
	{
		return false;
	}

	resources.remove_at(resource_cache[p_uuid]);

	int l_deleted_index = resource_cache[p_uuid];
	resource_cache.erase(p_uuid);

	for (KeyValue<String, int> entry : resource_cache)
	{
		if (entry.value > l_deleted_index)
		{
			resource_cache[entry.key] = entry.value - 1;
		}
	}

	return true;
}

bool ResourceDB::remove_resources(PackedStringArray p_uuid_array, bool p_check)
{
	if (p_check)
	{
		for (String entry : p_uuid_array)
		{
			if (!resource_cache.has(entry))
			{
				return false;
			}
		}
	}

	for (String entry : p_uuid_array)
	{
		remove_resource(entry, !p_check);
	}

	return true;
}

bool ResourceDB::has_resource_field(String p_uuid, String p_field_name) const
{
	return resources[resource_cache[p_uuid]]->has_field(p_field_name);
}

bool ResourceDB::validate_resource_field(String p_uuid, String p_field_name, Variant p_data, bool p_is_add)
{
	if (p_field_name.is_empty() || !field_cache.has(p_field_name))
	{
		return false;
	}

	if (p_is_add)
	{
		if (has_resource_field(p_uuid, p_field_name))
		{
			return false;
		}
	}

	if (p_data.get_type() != get_field(p_field_name).info.type)
	{
		return false;
	}

	return true;
}

bool ResourceDB::add_resource_field(String p_uuid, String p_field_name, Variant p_data, bool p_check)
{
	if (p_check)
	{
		if (p_uuid.is_empty() || !resource_cache.has(p_uuid))
		{
			return false;
		}

		if (!validate_resource_field(p_uuid, p_field_name, p_data, true))
		{
			return false;
		}
	}
	return resources[resource_cache[p_uuid]]->add_field(p_field_name, p_data);
}

bool ResourceDB::add_resource_fields(String p_uuid, HashMap<String, Variant> p_fields, bool p_check)
{
	if (p_check)
	{
		if (p_uuid.is_empty() || !resource_cache.has(p_uuid))
		{
			return false;
		}

		for (KeyValue<String, Variant> entry : p_fields)
		{
			if (!validate_resource_field(p_uuid, entry.key, entry.value, true))
			{
				return false;
			}
		}
	}

	for (KeyValue<String, Variant> entry : p_fields)
	{
		add_resource_field(p_uuid, entry.key, entry.value, !p_check);
	}

	return true;
}

bool ResourceDB::_add_resource_fields_bind(String p_uuid, Dictionary p_fields, bool p_check)
{
	HashMap<String, Variant> l_fields;

	for (String key : p_fields.keys())
	{
		l_fields.insert(key, p_fields[key]);
	}

	return add_resource_fields(p_uuid, l_fields, p_check);
}

Variant ResourceDB::get_resource_field(String p_uuid, String p_field_name)
{
	return resources[resource_cache[p_uuid]]->get_field(p_field_name);
}

Dictionary ResourceDB::get_resource_fields(String p_uuid)
{
	Dictionary l_game_resource_dictionary;
	if (!resource_cache.has(p_uuid))
	{
		return Dictionary();
	}

	l_game_resource_dictionary = _get_resource_bind(p_uuid);

	if (!l_game_resource_dictionary.has("fields"))
	{
		return Dictionary();
	}

	return l_game_resource_dictionary["fields"];
}

void ResourceDB::set_resource_field(String p_uuid, String p_field_name, Variant p_data, bool p_check)
{
	if (p_check)
	{
		if (p_uuid.is_empty() || !resource_cache.has(p_uuid))
		{
			return;
		}

		if (!validate_resource_field(p_uuid, p_field_name, p_data))
		{
			return;
		}
	}

	if (!has_resource_field(p_uuid, p_field_name))
	{
		resources[resource_cache[p_uuid]]->add_field(p_field_name, p_data);
	}
	else
	{
		resources[resource_cache[p_uuid]]->set_field(p_field_name, p_data);
	}
}

void ResourceDB::set_resource_fields(String p_uuid, HashMap<String, Variant> p_fields, bool p_check)
{
	if (p_check)
	{
		if (p_uuid.is_empty() || !resource_cache.has(p_uuid))
		{
			return;
		}

		for (KeyValue<String, Variant> entry : p_fields)
		{
			if (!validate_resource_field(p_uuid, entry.key, entry.value))
			{
				return;
			}
		}
	}

	for (KeyValue<String, Variant> entry : p_fields)
	{
		set_resource_field(p_uuid, entry.key, entry.value, !p_check);
	}
}

void ResourceDB::_set_resource_fields_bind(String p_uuid, Dictionary p_fields, bool p_check)
{
	HashMap<String, Variant> l_fields;

	for (String key : p_fields.keys())
	{
		l_fields.insert(key, p_fields[key]);
	}

	set_resource_fields(p_uuid, l_fields, p_check);
}

bool ResourceDB::remove_resource_field(String p_uuid, String p_field_name, bool p_check)
{
	if (p_check)
	{
		if (p_uuid.is_empty() || !resource_cache.has(p_uuid))
		{
			return false;
		}

		if (p_field_name.is_empty() || !field_cache.has(p_field_name))
		{
			return false;
		}

		if (!has_resource_field(p_uuid, p_field_name))
		{
			return false;
		}
	}

	return resources[resource_cache[p_uuid]]->remove_field(p_field_name);
}

bool ResourceDB::remove_resource_fields(String p_uuid, PackedStringArray p_field_names, bool p_check)
{
	if (p_check)
	{
		if (p_uuid.is_empty() || !resource_cache.has(p_uuid))
		{
			return false;
		}

		for (String entry : p_field_names)
		{
			if (entry.is_empty() || !field_cache.has(entry))
			{
				return false;
			}

			if (!has_resource_field(p_uuid, entry))
			{
				return false;
			}
		}
	}

	for (String entry : p_field_names)
	{
		remove_resource_field(p_uuid, entry, !p_check);
	}

	return true;
}
