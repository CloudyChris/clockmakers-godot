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

	UUID uuid;

protected:
	static void _bind_methods();

public:
	UUID get_uuid() const;
	void set_uuid(const UUID &p_uuid);

	TrackedResource();
	TrackedResource(const TrackedResource &p_tracked);
};

class FieldData : public Resource
{
	GDCLASS(FieldData, Resource);
	String name;
	Variant::Type type;
	bool has_default_value;
	Variant *default_value;

private:
	static void _bind_methods();

public:
	const String &get_name() const { return name; };
	void set_name(const String &p_name) { name = p_name; };
	const Variant::Type get_type() const { return type; };
	void set_type(Variant::Type p_type) { type = p_type; };
	bool get_has_default_value() const { return has_default_value; };
	void set_has_default_value(bool p_has_default_value) { has_default_value = p_has_default_value; };
	Variant *get_default_value() const { return default_value; };
	void set_default_value(Variant *p_default_value, bool p_set_flag = false)
	{
		default_value = has_default_value ? p_default_value : nullptr;
		has_default_value = p_set_flag ? true : has_default_value;
	};

	FieldData();
	FieldData(const FieldData &p_field_data);
};

class GameResourceInterface : public TrackedResource
{
	GDCLASS(GameResourceInterface, TrackedResource);

	Vector<FieldData> fields;
	// field name, fields index
	HashMap<String, uint32_t> indices;

protected:
	static void _bind_methods();

public:
	bool has_field(const String &p_name) const;
	FieldData get_field(const String &p_name) const;
	void _set_field(const String &p_name, Variant::Type p_type, bool p_has_default, Variant *p_default);
	void set_field(const String &p_name, const FieldData &p_data);

	const TypedArray<String> get_field_names() const;

	Vector<FieldData> get_fields() { return fields; };

	GameResourceInterface();
	GameResourceInterface(const GameResourceInterface &p_interface);
};

class GameResource : public TrackedResource
{
	GDCLASS(GameResource, TrackedResource);

	GameResourceInterface *interface;
	// field name, field value
	HashMap<String, Variant> data;

protected:
	static void _bind_methods();

public:
	Variant get_data(const String &p_field) const;
	void set_data(const String &p_field, const Variant &p_data);

	GameResourceInterface *_get_interface() const;
	GameResourceInterface get_interface() const;
	void set_interface(GameResourceInterface *p_interface);

	GameResource();
	GameResource(GameResourceInterface *p_interface);
	GameResource(const GameResource &p_gres);
};

class ResourceDB : public TrackedResource
{
	GDCLASS(ResourceDB, TrackedResource);

	GameResourceInterface interface;
	// uuid, row
	HashMap<String, GameResource *> resources;

protected:
	static void _bind_methods();

public:
	GameResource get_game_resource(const UUID &p_uuid) const;
	void set_game_resource(GameResource p_gameresource);

	Variant get_field(const UUID &p_uuid, const String &p_field) const;
	void set_field(const UUID &p_uuid, const String &p_field, const Variant &p_value);

	ResourceDB(const GameResourceInterface &p_interface);
	ResourceDB(const ResourceDB &p_resdb);
};

#endif
