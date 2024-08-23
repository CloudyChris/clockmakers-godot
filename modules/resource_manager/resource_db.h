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

	struct FieldSpecification
	{
		PropertyInfo info;
		bool has_default_value = false;
		Variant default_value;

		FieldSpecification();
		FieldSpecification(const FieldSpecification &p_field_specification);
		FieldSpecification(PropertyInfo p_info, bool p_has_default_value, Variant *p_default_value);
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
		GameResource(const GameResource &p_game_resource);
		~GameResource();
	};

	mutable Vector<FieldSpecification> fields;
	HashMap<String, int> field_cache;

	mutable Vector<GameResource> resources;
	HashMap<String, int> resource_cache;

protected:
	static void _bind_methods();

public:
	PackedStringArray get_field_list() const;
	bool has_field(String p_field_name) const;
	bool add_field(PropertyInfo p_info, bool p_has_default_value = false, Variant *p_default_value = nullptr);
	bool _add_field_bind(Dictionary p_field_specification);
	bool remove_field(String p_field_name);

	const ResourceDB::FieldSpecification &get_field(String p_field_name) const;
	Dictionary _get_field_bind(String p_field_name);
	void set_field(PropertyInfo p_info, bool p_has_default_value = false, Variant *p_default_value = nullptr);
	void _set_field_bind(Dictionary p_field_specification);

	bool add_resource(GameResource p_game_resource); // TODO: implement
	bool _add_resource_bind(Dictionary p_game_resource_dictionary); // TODO: implement
	GameResource get_resource(String p_uuid); // TODO: implement
	Dictionary _get_resource_bind(String p_uuid); // TODO: implement
	void set_resource(GameResource p_game_resource); // TODO: implement
	void _set_resource_bind(Dictionary p_game_resource_dictionary); // TODO: implement
	bool remove_resource(String p_uuid); // TODO: implement
	bool has_resource_field(String p_uuid, String p_field_name) const;
	Variant get_resource_field(String p_uuid, String p_field_name);
	void set_resource_field(String p_uuid, String p_field_name, Variant p_data);
	bool remove_resource_field(String p_uuid, String p_field_name);

	ResourceDB(){};
	~ResourceDB();
};

#endif // RESOURCE_DB_H
