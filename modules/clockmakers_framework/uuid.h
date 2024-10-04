/* uuid.h */

#ifndef UUID_H
#define UUID_H

#include "core/object/class_db.h"
#include "core/variant/typed_array.h"

class UUID : public Object
{
	GDCLASS(UUID, Object);

	void _generate_uuid();
	void _update_uuid();
	void _update_uuid_string();

protected:
	PackedByteArray uuid;
	String uuid_string;

	static void _bind_methods();

public:
	String get_uuid_string();
	String get_uuid_string_const() const;
	void set_uuid_string(String p_uuid_string);

	PackedByteArray get_uuid();
	PackedByteArray get_uuid_const() const;
	void set_uuid(PackedByteArray p_uuid);

	UUID();
	UUID(const UUID &p_uuid);
	UUID(const PackedByteArray &p_uuid);
	~UUID();
};

#endif
