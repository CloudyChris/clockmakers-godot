/* resource_db.cpp */

#include "resource_db.h"

#include "core/object/class_db.h"
#include "core/object/object.h"

TrackedResource::TrackedResource()
	: uuid(nullptr)
{
}

TrackedResource::TrackedResource(TrackedResource *p_tracked)
	: uuid(p_tracked->get_uuid())
{
	uuid->_set_uuid(*p_tracked->get_uuid());
}

UUID *TrackedResource::get_uuid() const
{
	return uuid;
};

void TrackedResource::set_uuid(UUID *p_uuid)
{
	uuid->set_uuid(p_uuid->_get_uuid());
}

void TrackedResource::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_uuid"), &TrackedResource::get_uuid);
	ClassDB::bind_method(D_METHOD("set_uuid", "uuid"), &TrackedResource::set_uuid);

	ADD_GROUP("Tracked Resource", "tracked_resource_");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tracked_resource_uuid"), "set_uuid", "get_uuid");
}

FieldData::FieldData()
	: name("")
	, has_default_value(false)
{
}

FieldData::FieldData(FieldData *p_field_data)
	: name(p_field_data->name)
	, has_default_value(p_field_data->has_default_value)
	, default_value(p_field_data->default_value)
{
}

void FieldData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_field_name"), &FieldData::get_field_name);
	ClassDB::bind_method(D_METHOD("set_field_name", "name"), &FieldData::set_field_name);
	ClassDB::bind_method(D_METHOD("get_field_has_default_value"), &FieldData::get_field_has_default_value);
	ClassDB::bind_method(D_METHOD("set_field_has_default_value", "has_default_value"), &FieldData::set_field_has_default_value);
	ClassDB::bind_method(D_METHOD("get_field_default_value"), &FieldData::get_field_default_value);
	ClassDB::bind_method(D_METHOD("set_field_default_value", "default_value", "set_flag"), &FieldData::set_field_default_value);

	ADD_GROUP("Field Data", "field_data_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "field_data_field_name"), "set_name", "get_field_name");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "field_data_field_has_default_value"), "set_field_has_default_value", "get_field_has_default_value");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "field_data_field_default_value"), "set_field_default_value", "get_field_default_value");
}

GameResourceInterface::GameResourceInterface()
{
}

GameResourceInterface::GameResourceInterface(GameResourceInterface *p_interface)
{
	fields.append_array(p_interface->fields);
	indices = p_interface->indices;
}

bool GameResourceInterface::has_field(const String &p_name) const
{
	return indices.has(p_name);
}

FieldData *GameResourceInterface::get_field(const String &p_name) const
{
	return fields.get(indices.get(p_name));
}

void GameResourceInterface::_set_field(const String &p_name, bool p_has_default_value, Variant p_default_value)
{
	const uint l_size = fields.size();

	FieldData l_data;
	l_data.set_name(p_name);
	l_data.set_field_default_value(p_default_value, p_has_default_value);

	if (indices.has(p_name))
	{
		fields.set(indices.get(p_name), &l_data);
		return;
	}

	fields.insert(l_size, &l_data);
	indices[p_name] = l_size;
	return;
}

void GameResourceInterface::set_field(const String &p_name, FieldData *p_data)
{
	_set_field(p_name, p_data->get_field_has_default_value(), p_data->get_field_default_value());
}

TypedArray<String> GameResourceInterface::get_field_names() const
{
	TypedArray<String> l_data;
	for (FieldData *field : fields)
	{
		l_data.push_back(field->get_name());
	}

	return l_data;
}

void GameResourceInterface::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("has_field", "field_name"), &GameResourceInterface::has_field);
	ClassDB::bind_method(D_METHOD("get_field", "field_name"), &GameResourceInterface::get_field);
	ClassDB::bind_method(D_METHOD("set_field", "field"), &GameResourceInterface::set_field);
	ClassDB::bind_method(D_METHOD("get_field_names"), &GameResourceInterface::get_field_names);
}

GameResource::GameResource()
	: interface(nullptr)
{
	data.clear();
}

GameResource::GameResource(GameResourceInterface *p_interface)
	: interface(p_interface)
{
}

GameResource::GameResource(GameResource *p_gres)
	: interface(p_gres->get_interface())
	, data(p_gres->data)
{
}

Variant GameResource::get_data(const String &p_field) const
{
	return data.get(p_field);
}

void GameResource::set_data(const String &p_field, Variant p_data)
{
	data[p_field] = p_data;
}

void GameResource::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_data", "field"), &GameResource::get_data);
	ClassDB::bind_method(D_METHOD("set_data", "field", "data"), &GameResource::set_data);
	ClassDB::bind_method(D_METHOD("get_interface"), &GameResource::get_interface);
	ClassDB::bind_method(D_METHOD("set_interface", "interface"), &GameResource::set_interface);
}

ResourceDB::ResourceDB()
	: interface(nullptr)
{
}

ResourceDB::ResourceDB(GameResourceInterface *p_interface)
	: interface(p_interface)
{
}

ResourceDB::ResourceDB(ResourceDB *p_resdb)
	: interface(p_resdb->interface)
	, resources(p_resdb->resources)
{
}

GameResource *ResourceDB::get_game_resource(UUID *p_uuid) const
{
	return resources.get(p_uuid->get_uuid());
}

void ResourceDB::set_game_resource(GameResource *p_gameresource)
{
	resources[p_gameresource->get_uuid()->get_uuid()] = p_gameresource;
}

Variant ResourceDB::get_field(UUID *p_uuid, const String &p_field) const
{
	return resources.get(p_uuid->get_uuid())->get_data(p_field);
}

void ResourceDB::set_field(UUID *p_uuid, const String &p_field, Variant p_value)
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
