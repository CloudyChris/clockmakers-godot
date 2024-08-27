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

		static FieldSpecification from_dict(Dictionary p_field_specification);
		static Dictionary to_dict(FieldSpecification p_field_specification);

		FieldSpecification();
		FieldSpecification(const FieldSpecification &p_field_specification);
		FieldSpecification(PropertyInfo p_info, bool p_has_default_value, Variant *p_default_value);
	};

	struct GameResource : public TrackedResource
	{
		String resource_type;
		mutable Vector<Variant> fields;
		HashMap<String, int> field_cache;

		bool has_field(String p_field_name) const;
		bool add_field(String p_field_name, Variant p_data);
		Variant get_field(String p_field_name);
		void set_field(String p_field_name, Variant p_data);
		bool remove_field(String p_field_name);

		static GameResource from_dict(Dictionary p_game_resource_dictionary); // TODO: implement
		static Dictionary to_dict(const GameResource &p_game_resource); // TODO: implement

		GameResource(){};
		GameResource(const GameResource &p_game_resource);
		~GameResource();
	};

	mutable Vector<FieldSpecification> fields; // do we really need both a vector and a hashmap?
	HashMap<String, int> field_cache;

	mutable LocalVector<GameResource *> resources; // ARCTODO: change to just HashMap<GameResource *> and if you really need it a LocalVector<GameResource *> like node::Data::children
	HashMap<String, int> resource_cache;

protected:
	static void _bind_methods();

public:
	PackedStringArray get_field_list() const;
	bool has_field(String p_field_name) const;
	bool add_field(PropertyInfo p_info, bool p_has_default_value = false, Variant *p_default_value = nullptr);
	bool add_field(const FieldSpecification &p_field_specification);
	bool _add_field_bind(Dictionary p_field_specification);
	const ResourceDB::FieldSpecification &get_field(String p_field_name) const;
	Dictionary _get_field_bind(String p_field_name);
	void set_field(PropertyInfo p_info, bool p_has_default_value = false, Variant *p_default_value = nullptr);
	void set_field(const FieldSpecification &p_field_specification);
	void _set_field_bind(Dictionary p_field_specification);
	bool remove_field(String p_field_name);

	bool has_resource(String p_uuid) const;
	bool add_resource(GameResource p_game_resource);
	bool _add_resource_bind(Dictionary p_game_resource_dictionary);
	const GameResource &get_resource(String p_uuid) const;
	GameResource &get_resource_m(String p_uuid);
	Dictionary _get_resource_bind(String p_uuid);
	void set_resource(GameResource p_game_resource);
	void _set_resource_bind(Dictionary p_game_resource_dictionary);
	bool remove_resource(String p_uuid);

	bool has_resource_field(String p_uuid, String p_field_name) const;
	bool add_resource_field(String p_uuid, String p_field_name, Variant p_data);
	Variant get_resource_field(String p_uuid, String p_field_name);
	void set_resource_field(String p_uuid, String p_field_name, Variant p_data);
	bool remove_resource_field(String p_uuid, String p_field_name);

	ResourceDB(){};
	~ResourceDB();
};

#endif // RESOURCE_DB_H
