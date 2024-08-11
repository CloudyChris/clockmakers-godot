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
	const UUID &get_uuid() const;
	void set_uuid(const UUID &p_uuid);

	TrackedResource();
	TrackedResource(const TrackedResource &p_tracked);
};

class GameResourceInterface : public TrackedResource
{
	GDCLASS(GameResourceInterface, TrackedResource);

	struct FieldData
	{
		String name;
		Variant::Type type;
		bool has_default_value;
		Variant default_value;
	};

	Vector<FieldData> fields;
	// field name, fields index
	HashMap<String, uint32_t> indices;

protected:
	static void _bind_methods();

public:
	const FieldData *get_field(const String &p_name) const;
	void set_field(const String &p_name, const FieldData &p_data);

	GameResourceInterface();
	GameResourceInterface(const GameResourceInterface &p_interface);
};

class GameResource : public TrackedResource
{
	GDCLASS(GameResource, TrackedResource);

	GameResourceInterface interface;
	// field name, field value
	HashMap<String, Variant> data;

protected:
	static void _bind_methods();

public:
	const Variant &get_data(const String &p_field) const;
	void set_data(const String &p_field, const Variant &p_data);

	GameResource();
	GameResource(const GameResourceInterface &p_interface);
	GameResource(const GameResource &p_gres);
};

class ResourceDB : public TrackedResource
{
	GDCLASS(ResourceDB, TrackedResource);

	GameResourceInterface interface;
	// uuid, row
	HashMap<String, GameResource> resources;

public:
	const GameResource *get_game_resource(const String &p_uuid) const { return resources.has(p_uuid) ? &resources.get(p_uuid) : nullptr; };
	const Variant &get_field(const String &p_uuid, const String &p_field) const;

	ResourceDB(const GameResourceInterface &p_interface);
	ResourceDB(const ResourceDB &p_resdb);
};

#endif
