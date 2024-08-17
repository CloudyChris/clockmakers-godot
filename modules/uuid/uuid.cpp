/* uuid.cpp */

#include "uuid.h"

#include "core/object/class_db.h"
#include "core/object/object.h"

#include <math.h>

UUID::UUID()
{
	generate_uuid();
	update_uuid_string();
}

UUID::UUID(UUID &p_uuid)
{
	uuid = p_uuid._get_uuid();
	update_uuid_string();
}

void UUID::generate_uuid()
{
	Math::randomize();

	uuid.clear();

	for (int i = 0; i < 16; i++)
	{
		uint32_t val = Math::rand() & 255;

		switch (i)
		{
			case 6:
				val = (val & 0x0f) | 0x40;
				break;
			case 8:
				val = (val & 0x3f) | 0x80;
				break;
		}

		uuid.insert(i, val);
	}
}

void UUID::update_uuid_string()
{
	uuid_stringified = vformat("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
							   // low
							   uuid[0], uuid[1], uuid[2], uuid[3],

							   // mid
							   uuid[4], uuid[5],

							   // hi
							   uuid[6], uuid[7],

							   // clock
							   uuid[8], uuid[9],

							   // node
							   uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
}

void UUID::_set_uuid(TypedArray<uint32_t> p_tarr)
{
	uuid.assign(p_tarr);
	update_uuid_string();
}

void UUID::set_uuid(String p_string)
{
}

void UUID::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_uuid"), &UUID::get_uuid);
	ClassDB::bind_method(D_METHOD("set_uuid", "array"), &UUID::set_uuid);

	ADD_GROUP("UUID", "uuid_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "uuid_uuid"), "set_uuid", "get_uuid");
}
