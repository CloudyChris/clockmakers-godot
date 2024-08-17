/* resource_db.cpp */

#include "resource_db.h"

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/variant/dictionary.h"

TrackedResource::TrackedResource()
{
}

Ref<UUID> TrackedResource::get_uuid()
{
	return &uuid;
};

void TrackedResource::set_uuid(Ref<UUID> p_uuid)
{
	uuid = *p_uuid.ptr();
}

void TrackedResource::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_uuid"), &TrackedResource::get_uuid);
	ClassDB::bind_method(D_METHOD("set_uuid", "uuid"), &TrackedResource::set_uuid);

	ADD_GROUP("Tracked Resource", "tracked_resource_");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tracked_resource_uuid", PROPERTY_HINT_RESOURCE_TYPE, "UUID", PROPERTY_USAGE_READ_ONLY), "set_uuid", "get_uuid");
}

FieldData::FieldData()
	: name("")
	, has_default_value(false)
{
}

FieldData::FieldData(FieldData &p_field_data)
	: name(p_field_data.name)
	, has_default_value(p_field_data.has_default_value)
	, default_value(p_field_data.default_value)
{
}

void FieldData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_field_name"), &FieldData::get_field_name);
	ClassDB::bind_method(D_METHOD("set_field_name", "name"), &FieldData::set_field_name);
	ClassDB::bind_method(D_METHOD("get_field_has_default_value"), &FieldData::get_field_has_default_value);
	ClassDB::bind_method(D_METHOD("set_field_has_default_value", "has_default_value"), &FieldData::set_field_has_default_value);
	ClassDB::bind_method(D_METHOD("get_field_default_value"), &FieldData::get_field_default_value);
	ClassDB::bind_method(D_METHOD("set_field_default_value", "default_value"), &FieldData::set_field_default_value);

	ADD_GROUP("Field Data", "field_data_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "field_data_field_name"), "set_name", "get_field_name");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "field_data_field_has_default_value"), "set_field_has_default_value", "get_field_has_default_value");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "field_data_field_default_value"), "set_field_default_value", "get_field_default_value");
}

GameResourceInterface::GameResourceInterface()
{
}

GameResourceInterface::GameResourceInterface(GameResourceInterface &p_interface)
	: fields(p_interface.fields)
{
}

bool GameResourceInterface::has_field(String p_name)
{
	return indices.has(p_name);
}

Ref<FieldData> GameResourceInterface::get_field(String p_name)
{
	return fields[indices.get(p_name)];
}

void GameResourceInterface::_set_field(String p_name, bool p_has_default_value, Variant p_default_value)
{
	if (indices.has(p_name))
	{
		Ref<FieldData> l_field = fields[indices.get(p_name)];
		l_field->set_field_has_default_value(p_has_default_value);
		l_field->set_field_default_value(p_default_value);
	}
}

void GameResourceInterface::set_field(String p_name, Ref<FieldData> p_data)
{
	_set_field(p_name, p_data->get_field_has_default_value(), p_data->get_field_default_value());
}

TypedArray<String> GameResourceInterface::get_field_names()
{
	TypedArray<String> l_data;
	for (int i = 0; i < fields.size(); i++)
	{
		Ref<FieldData> l_field = fields[i];
		l_data.push_back(l_field->get_field_name());
	}

	return l_data;
}

TypedArray<FieldData> GameResourceInterface::get_fields()
{
	TypedArray<FieldData> l_arr;
	for (int i = 0; i < fields.size(); i++)
	{
		l_arr.push_back(fields[i]);
	}

	return l_arr;
}

void GameResourceInterface::set_fields(TypedArray<FieldData> p_fields)
{
	fields.clear();
	indices.clear();
	for (int i = 0; i < p_fields.size(); i++)
	{
		fields.push_back(p_fields[i]);
		indices[Ref<FieldData>(p_fields[i])->get_field_name()] = fields.size() - 1;
	}
}

void GameResourceInterface::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("has_field", "field_name"), &GameResourceInterface::has_field);
	ClassDB::bind_method(D_METHOD("get_field", "field_name"), &GameResourceInterface::get_field);
	ClassDB::bind_method(D_METHOD("set_field", "field"), &GameResourceInterface::set_field);
	ClassDB::bind_method(D_METHOD("get_field_names"), &GameResourceInterface::get_field_names);
	ClassDB::bind_method(D_METHOD("get_fields"), &GameResourceInterface::get_fields);
	ClassDB::bind_method(D_METHOD("set_fields"), &GameResourceInterface::set_fields);

	ADD_GROUP("Game Resource Interface", "gr_interface_");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "gr_interface_fields", PROPERTY_HINT_ARRAY_TYPE, "FieldData"), "set_fields", "get_fields");
}

GameResource::GameResource()
	: interface(nullptr)
{
	data.clear();
}

GameResource::GameResource(GameResourceInterface &p_interface)
	: interface(Ref<GameResourceInterface>(&p_interface))
{
}

Variant GameResource::get_data(String p_field)
{
	return data.get(p_field);
}

void GameResource::set_data(String p_field, Variant p_data)
{
	data[p_field] = p_data;
}

Dictionary GameResource::get_data_dict()
{
	Dictionary l_dict;

	for (KeyValue<String, Variant> entry : data)
	{
		l_dict[entry.key] = entry.value;
	}

	return l_dict;
}

void GameResource::set_data_dict(Dictionary p_data)
{
	data.clear();
	List<Variant> l_key_list = List<Variant>();
	p_data.get_key_list(&l_key_list);
	for (String entry : l_key_list)
	{
		data.insert(entry, p_data[entry]);
	}
}

void GameResource::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_data", "field"), &GameResource::get_data);
	ClassDB::bind_method(D_METHOD("set_data", "field", "data"), &GameResource::set_data);
	ClassDB::bind_method(D_METHOD("get_interface"), &GameResource::get_interface);
	ClassDB::bind_method(D_METHOD("set_interface", "interface"), &GameResource::set_interface);
	ClassDB::bind_method(D_METHOD("get_data_dict"), &GameResource::get_data_dict);
	ClassDB::bind_method(D_METHOD("set_data_dict", "dict"), &GameResource::set_data_dict);

	ADD_GROUP("Game Resource", "game_resource_");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "game_resource_interface", PROPERTY_HINT_RESOURCE_TYPE, "GameResourceInterface"), "set_interface", "get_interface");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "game_resource_data"), "set_data_dict", "get_data_dict");
}

ResourceDB::ResourceDB()
	: interface(nullptr)
{
}

ResourceDB::ResourceDB(GameResourceInterface &p_interface)
	: interface(Ref<GameResourceInterface>(&p_interface))
{
}

Ref<GameResource> ResourceDB::get_game_resource(Ref<UUID> p_uuid)
{
	return resources.get(p_uuid->get_uuid());
}

void ResourceDB::set_game_resource(Ref<GameResource> p_gameresource)
{
	resources[p_gameresource->get_uuid()->get_uuid()] = p_gameresource;
}

Variant ResourceDB::get_field(Ref<UUID> p_uuid, const String p_field)
{
	return resources.get(p_uuid->get_uuid())->get_data(p_field);
}

void ResourceDB::set_field(Ref<UUID> p_uuid, String p_field, Variant p_value)
{
	resources.get(p_uuid->get_uuid())->set_data(p_field, p_value);
}

void ResourceDB::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_game_resource", "uuid"), &ResourceDB::get_game_resource);
	ClassDB::bind_method(D_METHOD("set_game_resource", "game_resource"), &ResourceDB::set_game_resource);
	ClassDB::bind_method(D_METHOD("get_field", "uuid"), &ResourceDB::get_field);
	ClassDB::bind_method(D_METHOD("set_field", "uuid", "field", "value"), &ResourceDB::set_field);
}
