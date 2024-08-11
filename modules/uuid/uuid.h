/* uuid.h */

#ifndef UUID_H
#define UUID_H

#include "core/io/resource.h"
#include "core/object/class_db.h"
#include "core/templates/vector.h"
#include "core/variant/typed_array.h"

class UUID : public Resource
{
	GDCLASS(UUID, Resource);

	TypedArray<uint32_t> uuid;
	String uuid_stringified;

protected:
	static void _bind_methods();

public:
	String get_uuid() const { return uuid_stringified; };
	void set_uuid(const TypedArray<uint32_t> &p_tarr);

	const TypedArray<uint32_t> &_get_uuid() const { return uuid; };
	void _set_uuid(const UUID &p_uuid);

	void update_uuid_string();
	void generate_uuid();

	_FORCE_INLINE_ bool operator==(const UUID &p_uuid) const { return uuid == p_uuid._get_uuid(); };

	UUID();
	UUID(const UUID &p_uuid);
};

#endif
