/* resource_db.h */

#ifndef RESOURCE_DB_H
#define RESOURCE_DB_H

#include "core/io/resource.h"
#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/templates/vector.h"
#include "core/variant/variant.h"

#include "tracked_resource.h"

class ResourceDB : public TrackedResource
{
	GDCLASS(ResourceDB, TrackedResource);

	struct GameResourceFieldSpecification
	{
		String name;
		Variant::Type type;
		PropertyHint property_hint;
		String type_hint;
		PropertyUsageFlags property_usage;

		static Variant::Type typestring_to_enum(String p_typestring);
		static String enum_to_typestring(Variant::Type p_type);

		GameResourceFieldSpecification();
		GameResourceFieldSpecification(String p_name, Variant::Type p_type, PropertyHint p_property_hint, String p_type_hint, PropertyUsageFlags p_property_usage);
	};

	struct GameResource
	{
		mutable Vector<Variant> fields;
		HashMap<String, int> field_cache;

		bool has_field(String p_field_name) const;
		Variant get_field(String p_field_name);
		void set_field(String p_field_name, Variant p_data);
		bool remove_field(String p_field_name);

		GameResource(){};
		~GameResource();
	};

	mutable Vector<GameResourceFieldSpecification> fields;
	HashMap<String, int> field_cache;

	mutable Vector<GameResource> resources;
	HashMap<String, int> resource_cache;

protected:
	static void _bind_methods();

public:
	PackedStringArray get_field_list() const;

	bool has_field(String p_field_name) const;
	bool add_field(String p_field_name, String p_field_typestring = "NIL", PropertyHint p_property_hint = PROPERTY_HINT_NONE, String p_type_hint = "", PropertyUsageFlags p_property_usage = PROPERTY_USAGE_DEFAULT);
	bool remove_field(String p_field_name);

	String get_field_typestring(String p_field_name);
	void set_field_typestring(String p_field_name, String p_field_typestring);

	PropertyHint get_field_property_hint(String p_field_name);
	void set_field_property_hint(String p_field_name, PropertyHint p_property_hint);

	String get_field_type_hint(String p_field_name);
	void set_field_type_hint(String p_field_name, String p_type_hint);

	PropertyUsageFlags get_field_property_usage(String p_field_name);
	void set_field_property_usage(String p_field_name, PropertyUsageFlags p_property_usage);

	bool has_resource_field(String p_uuid, String p_field_name) const;
	Variant get_resource_field(String p_uuid, String p_field_name);
	void set_resource_field(String p_uuid, String p_field_name, Variant p_data);
	bool remove_resource_field(String p_uuid, String p_field_name);

	ResourceDB();
	~ResourceDB();
};

#endif // RESOURCE_DB_H
