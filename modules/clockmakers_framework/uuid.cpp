/* uuid.cpp */

#include "uuid.h"

void UUID::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_uuid"), &UUID::get_uuid);
	ClassDB::bind_method(D_METHOD("set_uuid", "uuid"), &UUID::set_uuid);
	ClassDB::bind_method(D_METHOD("get_uuid_string"), &UUID::get_uuid_string);
	ClassDB::bind_method(D_METHOD("set_uuid_string", "uuid_string"), &UUID::set_uuid_string);

	ADD_GROUP("UUID", "uuidgroup_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "uuidgroup_uuid_string", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_uuid_string", "get_uuid_string");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "uuidgroup_uuid"), "set_uuid", "get_uuid");
}

UUID::UUID()
{
	_generate_uuid();
	_update_uuid_string();
}

UUID::UUID(const UUID &p_uuid)
	: uuid(p_uuid.uuid)
{
	_update_uuid_string();
}

UUID::UUID(const PackedByteArray &p_uuid)
	: uuid(p_uuid)
{
	_update_uuid_string();
}

UUID::~UUID()
{
	if (!uuid.is_empty())
	{
		uuid.clear();
	}
}

void UUID::_generate_uuid()
{
	Math::randomize();

	if (!uuid.is_empty())
	{
		uuid.clear();
	}

	for (uint8_t i = 0; i < 16; i++)
	{
		uint8_t val = Math::rand() & 255;

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

void UUID::_update_uuid()
{
	if (uuid_string.size() != 36)
	{
		return;
	}

	if (uuid_string[8] != '-' ||
		uuid_string[13] != '-' ||
		uuid_string[18] != '-' ||
		uuid_string[23] != '-')
	{
		return;
	}

	PackedByteArray uuid_backup = uuid;

	uint8_t acc, p = 0, i = 0;
	for (int c = 0; c < uuid_string.size(); c++)
	{
		if (static_cast<int>(uuid_string[c]) == static_cast<int>('-'))
		{
			continue;
		}

		uint8_t c16 = static_cast<int>(uuid_string[c]);

		if (c16 >= 97 && c16 <= 102)
		{
			c16 -= 87;
		}
		else if (c16 >= 48 && c16 <= 57)
		{
			c16 -= 48;
		}
		else
		{
			uuid = uuid_backup;
			return;
		}

		if (p % 2 == 0)
		{
			c16 *= 16;
		}

		acc += c16;

		p++;

		if (p >= 2)
		{
			uuid.get_m(i) = acc;
			acc = 0;
			p = 0;
			i++;
		}
	}
}

void UUID::_update_uuid_string()
{
	uuid_string = vformat("%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
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

String UUID::get_uuid_string()
{
	return uuid_string;
}

String UUID::get_uuid_string_const() const
{
	return uuid_string;
}

void UUID::set_uuid_string(String p_uuid_string)
{
	uuid_string = p_uuid_string;
	_update_uuid();
}

PackedByteArray UUID::get_uuid()
{
	return uuid;
}

PackedByteArray UUID::get_uuid_const() const
{
	return uuid;
}

void UUID::set_uuid(PackedByteArray p_uuid)
{
	// TODO consider marking this dirty and updating the uuid string on get instead
	uuid = p_uuid;
	_update_uuid_string();
}
