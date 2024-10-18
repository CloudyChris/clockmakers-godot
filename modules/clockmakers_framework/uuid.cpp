/* uuid.cpp */

#include "uuid.h"
#include "core/object/object.h"

void UUID::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_uuid"), &UUID::get_uuid_bind);
	ClassDB::bind_method(D_METHOD("set_uuid", "p_uuid"), &UUID::set_uuid_bind);
	ClassDB::bind_method(D_METHOD("get_uuid_string"), &UUID::get_uuid_string_bind);
	ClassDB::bind_method(D_METHOD("set_uuid_string", "p_uuid_string"), &UUID::set_uuid_string_bind);

	ADD_GROUP("UUID", "UUIDGroup_");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "UUIDGroup_uuid_string", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_uuid_string", "get_uuid_string");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "UUIDGroup_uuid", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "set_uuid", "get_uuid");
}

UUID::UUID()
	: uuid(nullptr)
	, uuid_string(nullptr)
{
	uuid = (uint8_t *)malloc(uuid_size * sizeof(uint8_t));
	uuid_string = (char *)malloc(uuid_string_size * sizeof(char));

	_generate_uuid();
	_update_uuid_string();
}

UUID::UUID(const UUID &p_uuid)
	: uuid(nullptr)
	, uuid_string(nullptr)
{
	uuid = (uint8_t *)malloc(uuid_size * sizeof(uint8_t));
	uuid_string = (char *)malloc(uuid_string_size * sizeof(char));

	if (p_uuid.uuid)
	{
		memcpy(uuid, p_uuid.uuid, uuid_size * sizeof(uint8_t));
	}
	else
	{
		_generate_uuid();
	}

	_update_uuid_string();
}

UUID::UUID(uint8_t *p_uuid)
	: uuid(nullptr)
	, uuid_string(nullptr)
{
	uuid = (uint8_t *)malloc(uuid_size * sizeof(uint8_t));
	uuid_string = (char *)malloc(uuid_string_size * sizeof(char));

	if (p_uuid)
	{
		memcpy(uuid, p_uuid, uuid_size * sizeof(uint8_t));
	}
	else
	{
		_generate_uuid();
	}

	_update_uuid_string();
}

UUID::UUID(char *p_uuid_string)
	: uuid(nullptr)
	, uuid_string(nullptr)
{
	uuid = (uint8_t *)malloc(uuid_size * sizeof(uint8_t));
	uuid_string = (char *)malloc(uuid_string_size * sizeof(char));

	memcpy(uuid_string, p_uuid_string, uuid_string_size * sizeof(char));
	_update_uuid();
}

UUID::~UUID()
{
	if (uuid)
	{
		free(uuid);
		uuid = nullptr;
	}

	if (uuid_string)
	{
		free(uuid_string);
		uuid_string = nullptr;
	}
}

UUID UUID::empty()
{
	UUID r_uuid;

	uint8_t *uuid_0_fill = (uint8_t *)malloc(uuid_size);

	for (uint8_t i = 0; i < uuid_size; i++)
	{
		uuid_0_fill[i] = 0;
	}

	r_uuid.set_uuid(uuid_0_fill);

	return r_uuid;
}

void UUID::_generate_uuid()
{
	Math::randomize();

	if (!uuid)
	{
		uuid = (uint8_t *)malloc(uuid_size * sizeof(uint8_t));
	}

	for (uint8_t i = 0; i < uuid_size; i++)
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

		uuid[i] = val;
	}
}

void UUID::_update_uuid()
{
	if (uuid_string[8] != '-' ||
		uuid_string[13] != '-' ||
		uuid_string[18] != '-' ||
		uuid_string[23] != '-')
	{
		return;
	}

	uint8_t *uuid_backup = (uint8_t *)malloc(uuid_size * sizeof(uint8_t));

	uint8_t acc = 0, p = 1, uuid_pos = 0;
	for (uint8_t i = 0; i < uuid_string_size; i++)
	{
		switch (uuid_string[i])
		{
			case '0':
				acc += 0;
				break;
			case '1':
				acc += 1;
				break;
			case '2':
				acc += 2;
				break;
			case '3':
				acc += 3;
				break;
			case '4':
				acc += 4;
				break;
			case '5':
				acc += 5;
				break;
			case '6':
				acc += 6;
				break;
			case '7':
				acc += 7;
				break;
			case '8':
				acc += 8;
				break;
			case '9':
				acc += 9;
				break;
			case 'a':
				acc += 10;
				break;
			case 'b':
				acc += 11;
				break;
			case 'c':
				acc += 12;
				break;
			case 'd':
				acc += 13;
				break;
			case 'e':
				acc += 14;
				break;
			case 'f':
				acc += 15;
				break;
			case '-':
				continue;
			default:
				memcpy(uuid, uuid_backup, uuid_size * sizeof(uint8_t));
				free(uuid_backup);
				uuid_backup = nullptr;
				return;
		}

		acc *= (p == 1) ? 16 : 1;

		p--;

		if (p == 255)
		{
			uuid[uuid_pos] = acc;
			p = 1;
			acc = 0;
			uuid_pos++;
		}
	}

	if (uuid_backup)
	{
		free(uuid_backup);
		uuid_backup = nullptr;
	}
}

void UUID::_update_uuid_string()
{
	uint8_t uuid_string_pos = 0;
	for (uint8_t i = 0; i < uuid_size; i++)
	{
		uuid_string[uuid_string_pos] = uuid[i] / 16 + (uuid[i] / 16 > 9 ? 87 : 48);
		uuid_string_pos++;
		uuid_string[uuid_string_pos] = uuid[i] % 16 + (uuid[i] % 16 > 9 ? 87 : 48);
		uuid_string_pos++;

		if (i == 3 || i == 5 || i == 7 || i == 9)
		{
			uuid_string[uuid_string_pos] = '-';
			uuid_string_pos++;
		}
	}
}

char *UUID::get_uuid_string()
{
	return uuid_string;
}

char *UUID::get_uuid_string_const() const
{
	return uuid_string;
}

void UUID::set_uuid_string(char *p_uuid_string)
{
	uuid_string = p_uuid_string;
	_update_uuid();
}

String UUID::get_uuid_string_bind()
{
	String l_uuid_string;

	l_uuid_string.resize(uuid_string_size);
	l_uuid_string = uuid_string;

	return l_uuid_string;
}

void UUID::set_uuid_string_bind(String p_uuid_string)
{
	CharString l_string_compat = p_uuid_string.to_lower().ascii(true);
	memcpy(uuid_string, l_string_compat.ptrw(), uuid_string_size);
	_update_uuid();
}

uint8_t *UUID::get_uuid()
{
	return uuid;
}

PackedByteArray UUID::get_uuid_bind()
{
	PackedByteArray l_uuid;
	l_uuid.resize(uuid_size * sizeof(uint8_t));
	memcpy(l_uuid.ptrw(), uuid, uuid_size * sizeof(uint8_t));
	return l_uuid;
}

void UUID::set_uuid_bind(PackedByteArray p_uuid)
{
	if (!uuid)
	{
		uuid = (uint8_t *)malloc(uuid_size * sizeof(uint8_t));
	}

	memcpy(uuid, p_uuid.ptrw(), uuid_size * sizeof(uint8_t));

	_update_uuid_string();
}

Tracked::Tracked()
	: uuid(UUID())
{
}

Tracked::Tracked(const Tracked &p_tracked)
	: uuid(p_tracked.uuid)
{
}

Tracked::~Tracked()
{
	uuid.~UUID();
}

Tracked Tracked::empty()
{
	Tracked r_tracked;

	r_tracked.set_uuid(UUID::empty());

	return r_tracked;
}

UUID Tracked::get_uuid() const
{
	return uuid;
}

UUID &Tracked::get_uuid_m()
{
	return uuid;
}

void Tracked::set_uuid(const UUID &p_uuid)
{
	uuid.set_uuid(p_uuid.get_uuid_const());
}

void TrackedObject::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_uuid"), &TrackedObject::get_uuid);
	ClassDB::bind_method(D_METHOD("set_uuid"), &TrackedObject::set_uuid);

	ADD_GROUP("Tracked Object", "TrackedObjectGroup_");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "TrackedObjectGroup_uuid", PROPERTY_HINT_OBJECT_ID, "UUID", PROPERTY_USAGE_DEFAULT), "set_uuid", "get_uuid");
}

TrackedObject::TrackedObject()
	: uuid(UUID())
{
}

TrackedObject::TrackedObject(const TrackedObject &p_tracked_object)
	: uuid(p_tracked_object.uuid)
{
}

TrackedObject::~TrackedObject()
{
	uuid.~UUID();
}

TrackedObject TrackedObject::empty()
{
	TrackedObject r_tracked;

	r_tracked.set_uuid(UUID::empty());

	return r_tracked;
}

UUID TrackedObject::get_uuid() const
{
	return uuid;
}

UUID &TrackedObject::get_uuid_m()
{
	return uuid;
}

void TrackedObject::set_uuid(const UUID &p_uuid)
{
	uuid.set_uuid(p_uuid.get_uuid_const());
}
