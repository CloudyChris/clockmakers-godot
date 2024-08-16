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

	UUID *uuid;

protected:
	static void _bind_methods();

public:
	UUID *get_uuid() const;
	void set_uuid(UUID *p_uuid);

	TrackedResource();
	TrackedResource(TrackedResource *p_tracked);
};

class FieldData : public Resource
{
	GDCLASS(FieldData, Resource);

	String name;
	bool has_default_value;
	Variant default_value;

private:
	static void _bind_methods();

public:
	const String &get_field_name() const { return name; };
	void set_field_name(const String &p_name) { name = p_name; };
	bool get_field_has_default_value() const { return has_default_value; };
	void set_field_has_default_value(bool p_has_default_value) { has_default_value = p_has_default_value; };
	Variant get_field_default_value() const { return default_value; };
	void set_field_default_value(Variant p_default_value) { default_value = p_default_value; };

	FieldData();
	FieldData(FieldData *p_field_data);
};

class GameResourceInterface : public TrackedResource
{
	GDCLASS(GameResourceInterface, TrackedResource);

	Vector<FieldData *> fields;
	// field name, fields index
	HashMap<String, uint32_t> indices;

protected:
	static void _bind_methods();

public:
	bool has_field(const String &p_name) const;
	FieldData *get_field(const String &p_name) const;
	void _set_field(const String &p_name, bool p_has_default, Variant p_default);
	void set_field(const String &p_name, FieldData *p_data);

	TypedArray<String> get_field_names() const;

	Vector<FieldData *> get_fields() const { return fields; };

	GameResourceInterface();
	GameResourceInterface(GameResourceInterface *p_interface);
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
	void set_data(const String &p_field, Variant p_data);

	GameResourceInterface *get_interface() { return interface; };
	void set_interface(GameResourceInterface *p_interface) { interface = p_interface; };

	GameResource();
	GameResource(GameResourceInterface *p_interface);
	GameResource(GameResource *p_gres);
};

class ResourceDB : public TrackedResource
{
	GDCLASS(ResourceDB, TrackedResource);

	GameResourceInterface *interface;
	// uuid, row
	HashMap<String, GameResource *> resources;

protected:
	static void _bind_methods();

public:
	GameResource *get_game_resource(UUID *p_uuid) const;
	void set_game_resource(GameResource *p_gameresource);

	Variant get_field(UUID *p_uuid, const String &p_field) const;
	void set_field(UUID *p_uuid, const String &p_field, Variant p_value);

	ResourceDB();
	ResourceDB(GameResourceInterface *p_interface);
	ResourceDB(ResourceDB *p_resdb);
};

#endif
