/* tracked_resource.cpp */

#include "tracked_resource.h"
#include "core/object/object.h"
#include "core/variant/typed_array.h"
#include "core/variant/variant.h"

void TrackedResource::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_uuid"), &TrackedResource::get_uuid);
	ClassDB::bind_method(D_METHOD("set_uuid", "uuid"), &TrackedResource::set_uuid);
	ClassDB::bind_method(D_METHOD("get_human_readable_uuid"), &TrackedResource::get_human_readable_uuid);
	ClassDB::bind_method(D_METHOD("set_human_readable_uuid", "uuid_string"), &TrackedResource::set_human_readable_uuid);

	ADD_GROUP("Tracked Resource", "trackedresource_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "trackedresource_uuid_string", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_human_readable_uuid", "get_human_readable_uuid");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "trackedresource_uuid"), "set_uuid", "get_uuid");
}

TrackedResource::UUID &TrackedResource::UUID::operator=(const UUID &p_uuid)
{
	uuid = p_uuid.uuid;
	_update_uuid_string();

	return *this;
}

TrackedResource::UUID::UUID()
{
	_generate_uuid();
	_update_uuid_string();
}

TrackedResource::UUID::UUID(const UUID &p_uuid)
	: uuid(p_uuid.uuid)
{
	_update_uuid_string();
}

TrackedResource::UUID::UUID(const PackedByteArray &p_uuid)
	: uuid(p_uuid)
{
	_update_uuid_string();
}

TrackedResource::UUID::~UUID()
{
	if (!uuid.is_empty())
	{
		uuid.clear();
	}
}

void TrackedResource::UUID::_generate_uuid()
{
	Math::randomize();

	if (!uuid.is_empty())
	{
		uuid.clear();
	}

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

void TrackedResource::UUID::_update_uuid_string()
{
	human_readable = vformat("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
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

String TrackedResource::get_human_readable_uuid()
{
	return uuid.human_readable;
}

String TrackedResource::get_human_readable_uuid_const() const
{
	return uuid.human_readable;
}

void TrackedResource::set_human_readable_uuid(String p_uuid_string)
{
	uuid.human_readable = p_uuid_string;
	uuid._update_uuid_string();
}

PackedByteArray TrackedResource::get_uuid()
{
	return uuid.uuid;
}

PackedByteArray TrackedResource::get_uuid_const() const
{
	return uuid.uuid;
}

void TrackedResource::set_uuid(PackedByteArray p_uuid)
{
	// TODO consider marking this dirty and updating the uuid string on get instead
	uuid.uuid = p_uuid;
	uuid._update_uuid_string();
}
