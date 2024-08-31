/* resource_db.h */

#ifndef RESOURCE_DB_H
#define RESOURCE_DB_H

#include "core/io/packed_data_container.h"
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

		operator Dictionary() const;

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

		static GameResource from_dict(Dictionary p_game_resource_dictionary);

		operator Dictionary() const;

		GameResource(){};
		GameResource(const GameResource &p_game_resource);
		~GameResource();
	};

	mutable Vector<FieldSpecification> fields;
	HashMap<String, int> field_cache;

	mutable LocalVector<GameResource *> resources;
	HashMap<String, int> resource_cache;

protected:
	static void _bind_methods();

public:
	/*------------------ FIELDS --------------*/
	bool has_field(String p_field_name) const;

	bool add_field(PropertyInfo p_info, bool p_has_default_value = false, Variant *p_default_value = nullptr);
	bool add_field(const FieldSpecification &p_field_specification);
	bool _add_field_bind(Dictionary p_field_specification);
	bool add_fields(Vector<FieldSpecification> p_fields); // TODO
	bool _add_fields_bild(Array p_fields); // TODO

	ResourceDB::FieldSpecification &get_field(String p_field_name);
	const ResourceDB::FieldSpecification &get_field(String p_field_name) const;
	Dictionary _get_field_bind(String p_field_name);
	PackedStringArray get_field_list() const;
	Vector<ResourceDB::FieldSpecification> get_fields();
	Array _get_fields_bind();

	void set_field(PropertyInfo p_info, bool p_has_default_value = false, Variant *p_default_value = nullptr);
	void set_field(const FieldSpecification &p_field_specification);
	void _set_field_bind(Dictionary p_field_specification);
	void set_fields(Vector<FieldSpecification> p_fields);
	void _set_fields_bind(Array p_fields);

	bool remove_field(String p_field_name);
	bool remove_fields(PackedStringArray p_fields); // TODO

	/*----------------- GAME RESOURCES --------------*/
	bool has_resource(String p_uuid) const;

	bool add_resource(GameResource p_game_resource);
	bool _add_resource_bind(Dictionary p_game_resource_dictionary);
	bool add_resources(HashMap<String, GameResource *> p_game_resources); // TODO
	bool _add_resources_bind(Dictionary p_game_resources); // TODO

	const GameResource &get_resource(String p_uuid) const;
	GameResource &get_resource_m(String p_uuid);
	Dictionary _get_resource_bind(String p_uuid);
	PackedStringArray get_resource_list() const; // TODO
	HashMap<String, GameResource *> get_resources(); // TODO
	Dictionary _get_resources_bind(); // TODO

	void set_resource(GameResource p_game_resource);
	void _set_resource_bind(Dictionary p_game_resource_dictionary);
	void set_resources(HashMap<String, GameResource *> p_game_resources); // TODO
	void _set_resources_bind(Dictionary p_game_resources); // TODO

	bool remove_resource(String p_uuid);
	bool remove_resources(PackedStringArray p_uuid_arrays); // TODO

	/*------------------ GAME RESOURCE FIELDS ------------------*/
	bool has_resource_field(String p_uuid, String p_field_name) const;

	bool add_resource_field(String p_uuid, String p_field_name, Variant p_data);
	bool add_resource_fields(String p_uuid, Dictionary p_fields); // TODO

	Variant get_resource_field(String p_uuid, String p_field_name);
	Dictionary get_resource_fields(String p_uuid); // TODO

	void set_resource_field(String p_uuid, String p_field_name, Variant p_data);
	void set_resource_fields(String p_uuid, Dictionary p_fields); // TODO

	bool remove_resource_field(String p_uuid, String p_field_name);
	bool remove_resource_fields(String p_uuid, PackedStringArray p_field_names); // TODO

	ResourceDB(){};
	~ResourceDB();
};

#endif // RESOURCE_DB_H
