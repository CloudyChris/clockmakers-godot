/* game_resource.h */

#ifndef GAME_RESOURCE_H
#define GAME_RESOURCE_H

#include "core/object/object.h"
#include "core/templates/hash_map.h"
#include "core/variant/variant.h"
#include "tracked_resource.h"

using GameResourceFieldIndex = int;

class GameResource : public TrackedResource
{
	GDCLASS(GameResource, TrackedResource);

	struct GameResourceField
	{
		String name;
		int property_hint;
		String type_hint;
		int property_usage;
		Variant data;

		GameResourceField();
		GameResourceField(String p_name, int p_property_hint, String p_type_hint, int p_property_usage, Variant p_data);
	};

	Vector<GameResourceField> fields;
	HashMap<String, GameResourceFieldIndex> field_cache;

protected:
	static void _bind_methods();

public:
	Variant get_field(String p_field_name);
	void set_field(String p_field_name, Variant p_data);

	int get_field_property_hint();
	void set_field_property_hint(int p_property_hint);

	String get_field_type_hint();
	void set_field_type_hint(String p_type_hint);

	int get_field_property_usage();
	void set_field_property_usage(int p_property_usage);

	GameResource();
	~GameResource();
};

#endif
