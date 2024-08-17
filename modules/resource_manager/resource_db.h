/* resource_db.h */

#ifndef RESOURCEDB_H
#define RESOURCEDB_H

#include "core/io/resource.h"
#include "core/templates/hash_map.h"
#include "core/templates/vector.h"
#include "core/variant/variant.h"

#include "modules/uuid/uuid.h"

class TrackedResource : public Resource
{
	GDCLASS(TrackedResource, Resource);

	Ref<UUID> uuid;

protected:
	static void _bind_methods();

public:
	Ref<UUID> get_uuid();
	void set_uuid(Ref<UUID> p_uuid);

	TrackedResource();
	TrackedResource(TrackedResource &p_tracked);
};

class FieldData : public Resource
{
	GDCLASS(FieldData, Resource);

	String name;
	bool has_default_value;
	Variant default_value;

protected:
	static void _bind_methods();

public:
	String get_field_name() { return name; };
	void set_field_name(String p_name) { name = p_name; };
	bool get_field_has_default_value() { return has_default_value; };
	void set_field_has_default_value(bool p_has_default_value) { has_default_value = p_has_default_value; };
	Variant get_field_default_value() { return default_value; };
	void set_field_default_value(Variant p_default_value) { default_value = p_default_value; };

	FieldData();
	FieldData(FieldData &p_field_data);
};

class GameResourceInterface : public TrackedResource
{
	GDCLASS(GameResourceInterface, TrackedResource);

	LocalVector<Ref<FieldData>> fields;
	// field name, fields index
	HashMap<String, uint32_t> indices;

protected:
	static void _bind_methods();

public:
	bool has_field(String p_name);
	Ref<FieldData> get_field(String p_name);
	void _set_field(String p_name, bool p_has_default, Variant p_default);
	void set_field(String p_name, Ref<FieldData> p_data);

	TypedArray<String> get_field_names() const;

	TypedArray<Ref<FieldData>> get_fields();
	void set_fields(TypedArray<Ref<FieldData>> p_fields);

	GameResourceInterface();
	GameResourceInterface(GameResourceInterface &p_interface);
};

class GameResource : public TrackedResource
{
	GDCLASS(GameResource, TrackedResource);

	Ref<GameResourceInterface> interface;
	// field name, field value
	HashMap<String, Variant> data;

protected:
	static void _bind_methods();

public:
	Variant get_data(String p_field);
	void set_data(String p_field, Variant p_data);

	Dictionary get_data_dict();
	void set_data_dict(Dictionary p_data);

	Ref<GameResourceInterface> get_interface() { return interface; };
	void set_interface(Ref<GameResourceInterface> p_interface) { interface = p_interface; };

	GameResource();
	GameResource(GameResourceInterface &p_interface);
	GameResource(GameResource &p_gres);
};

class ResourceDB : public TrackedResource
{
	GDCLASS(ResourceDB, TrackedResource);

	Ref<GameResourceInterface> interface;
	// uuid, row
	HashMap<String, Ref<GameResource>> resources;

protected:
	static void _bind_methods();

public:
	Ref<GameResource> get_game_resource(Ref<UUID> p_uuid);
	void set_game_resource(Ref<GameResource> p_gameresource);

	Variant get_field(Ref<UUID> p_uuid, String p_field);
	void set_field(Ref<UUID> p_uuid, String p_field, Variant p_value);

	ResourceDB();
	ResourceDB(GameResourceInterface &p_interface);
	ResourceDB(ResourceDB &p_resdb);
};

#endif
