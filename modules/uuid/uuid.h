/* uuid.h */

#ifndef UUID_H
#define UUID_H

#include "core/io/resource.h"
#include "core/object/class_db.h"
#include "core/templates/vector.h"
#include "core/variant/typed_array.h"

class TrackedResource;

class UUID : public Resource
{
	GDCLASS(UUID, Resource);

	Vector<uint32_t> uuid;
	String uuid_stringified;

	friend TrackedResource;

protected:
	static void _bind_methods();

public:
	String get_uuid() { return uuid_stringified; };
	void set_uuid(String p_string);

	void _update_uuid_string();
	void _generate_uuid();

	_FORCE_INLINE_ bool operator==(Ref<UUID> p_uuid) { return uuid == p_uuid->uuid; };

	UUID();
	UUID(UUID &p_uuid);
};

#endif
