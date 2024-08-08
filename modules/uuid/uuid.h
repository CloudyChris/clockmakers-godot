/* uuid.h */

#ifndef UUID_H
#define UUID_H

#include "core/io/resource.h"
#include "core/object/class_db.h"
#include "core/templates/vector.h"
#include "core/variant/typed_array.h"

class UUID : public Resource {
	GDCLASS(UUID, Resource);

protected:
	static void _bind_methods();

public:
	Vector<uint32_t> uuid;
	String uuid_stringified;

	UUID();

	String get_uuid() const { return uuid_stringified; };
	void set_uuid(const TypedArray<uint32_t> &p_tarr);

	bool operator==(const UUID &p_uuid) const {
		return uuid == p_uuid.uuid;
	};
};

#endif
