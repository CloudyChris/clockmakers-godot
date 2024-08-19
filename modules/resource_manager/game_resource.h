/* game_resource.h */

#ifndef GAME_RESOURCE_H
#define GAME_RESOURCE_H

#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/templates/vector.h"
#include "core/variant/variant.h"
#include "tracked_resource.h"

using GameResourceFieldIndex = int;

class GameResource : public TrackedResource
{
	GDCLASS(GameResource, TrackedResource);

	struct GameResourceField
	{
		String name;
		Variant::Type type;
		PropertyHint property_hint;
		String type_hint;
		PropertyUsageFlags property_usage;
		Variant data;

		GameResourceField();
		GameResourceField(String p_name, Variant::Type p_type, PropertyHint p_property_hint, String p_type_hint, PropertyUsageFlags p_property_usage);
		GameResourceField(String p_name, Variant::Type p_type, PropertyHint p_property_hint, String p_type_hint, PropertyUsageFlags p_property_usage, Variant p_data);
	};

	mutable Vector<GameResourceField> fields;
	HashMap<String, GameResourceFieldIndex> field_cache;

protected:
	static void _bind_methods();

public:
	PackedStringArray get_field_list();

	bool add_field(String p_field_name, Variant::Type p_field_type, PropertyHint p_property_hint = PROPERTY_HINT_NONE, String p_type_hint = "", PropertyUsageFlags p_property_usage = PROPERTY_USAGE_DEFAULT);

	Variant get_field(String p_field_name);
	void set_field(String p_field_name, Variant p_data);

	Variant::Type get_field_type(String p_field_name);
	void set_field_type(String p_field_name, Variant::Type p_field_type);

	PropertyHint get_field_property_hint(String p_field_name);
	void set_field_property_hint(String p_field_name, PropertyHint p_property_hint);

	String get_field_type_hint(String p_field_name);
	void set_field_type_hint(String p_field_name, String p_type_hint);

	PropertyUsageFlags get_field_property_usage(String p_field_name);
	void set_field_property_usage(String p_field_name, PropertyUsageFlags p_property_usage);

	GameResource(){};
	~GameResource();
};

#endif
