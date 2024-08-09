/* resource_db.h */

#include "core/io/resource.h"
#include "core/templates/hash_map.h"
#include "core/templates/vector.h"
#include "core/variant/variant.h"

#include "modules/uuid/uuid.h"

class TrackedResource : public Resource {
	GDCLASS(TrackedResource, Resource);

	UUID uuid;

protected:
	static void _bind_methods();

public:
	const UUID &get_uuid() const { return uuid; };
	void set_uuid(const UUID &p_uuid) { uuid.set_uuid(p_uuid.uuid); };

	TrackedResource();
};

class FieldData : public RefCounted {
	GDCLASS(FieldData, RefCounted);

	String name;
	Variant::Type type;
	bool has_default_value;
	Variant default_value;
	// TODO: if we store stuff in separate files, a file pattern would be useful
protected:
	static void _bind_methods();

public:
	String get_name() const { return name; };
	void set_name(const String &p_name) { name = p_name; };

	Variant::Type get_type() const { return type; };
	void set_type(Variant::Type p_type) { type = p_type; };

	bool get_has_default_value() const { return has_default_value; };
	void set_has_default_value(bool p_has_default) { has_default_value = p_has_default; };

	Variant get_default_value() const { return default_value; };
	void set_default_value(const Variant &p_default) { default_value = p_default; };

	FieldData make_field_data(const String &p_name, Variant::Type p_type, bool p_has_default, const Variant &p_default = NULL) const;

	FieldData();
};

class GameResourceInterface : public TrackedResource {
	GDCLASS(GameResourceInterface, TrackedResource);

	// these will only have one field named "data"
	Vector<FieldData> fields;
	// field name, fields index
	HashMap<String, uint32_t> indices;

protected:
	static void _bind_methods();

public:
	Variant get_field(const String &p_name) const;
	void set_field(const String &p_name, const FieldData &p_data);

	GameResourceInterface();
};

class GameResource : public TrackedResource {
	GDCLASS(GameResource, TrackedResource);

	// field name, field value
	HashMap<String, Variant> data;

protected:
	static void _bind_methods();

public:
	Variant get_data(const String &p_field) const;
	void set_data(const String &p_field, const Variant &p_data);

	GameResource();
};

class ResourceDB : public TrackedResource {
	GDCLASS(ResourceDB, TrackedResource);

	struct ResourceDBRow {
		// uuid, is loaded
		HashMap<String, bool> loaded;
		// uuid, value
		HashMap<String, Variant> row;
	};

	GameResourceInterface interface;
	// uuid, row
	HashMap<String, ResourceDBRow> resources;

public:
	ResourceDB(const GameResourceInterface &p_interface);
};

/* We'll need another structure to hold a content_pack data
 * Said structure will have a list or map of ResourceDB (check what you already did for reference (in CarefulWithTheMatches))
 *
 *
 *
 */
